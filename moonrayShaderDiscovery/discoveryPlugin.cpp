// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#include "discoveryPlugin.h"

#include "pxr/base/tf/diagnostic.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/base/tf/envSetting.h"
#include "pxr/base/tf/pathUtils.h"

#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/resolverScopedCache.h"

#include "pxr/usd/sdr/debugCodes.h"

PXR_NAMESPACE_OPEN_SCOPE

TfToken moonrayNodeType("moonrayClass");

namespace {

bool examineFiles(SdrShaderNodeDiscoveryResultVec* foundNodes,
                  SdrStringSet* foundNames,
                  const SdrDiscoveryPluginContext* context,
                  const std::string& dirPath,
                  const SdrStringVec& dirFileNames)
{
    for (const std::string& fileName : dirFileNames) {
        std::string extension = TfStringToLower(TfGetExtension(fileName));
        if (extension == "json") {
            std::string uri = TfStringCatPaths(dirPath, fileName);
            std::string className = TfStringGetBeforeSuffix(fileName, '.');

            if (!foundNames->insert(className).second) {
                 TF_DEBUG(SDR_DISCOVERY).Msg(
                     "Duplicate moonray class [%s] found at URI [%s], ignoring.",
                     className.c_str(), uri.c_str());
                continue;
            }

            foundNodes->emplace_back(
                SdrIdentifier(className),          // Identifier
                SdrVersion().GetAsDefault(),       // Version
                className,                         // Name
                TfToken(),                         // Family
                moonrayNodeType,                   // DiscoveryType
                moonrayNodeType,                   // SourceType
                uri,
                ArGetResolver().Resolve(uri)
            );
        }
    }

    // Continue walking directories
    return true;
}
} // namespace {

const SdrStringVec&
MoonrayDiscoveryPlugin::GetSearchURIs() const
{
    return _searchPaths;
}

MoonrayDiscoveryPlugin::MoonrayDiscoveryPlugin()
{
    const char* env = std::getenv("MOONRAY_CLASS_PATH");
    if (env) {
        _searchPaths = TfStringSplit(env, ":");
    }
}

SdrShaderNodeDiscoveryResultVec
MoonrayDiscoveryPlugin::DiscoverShaderNodes(const Context& context)
{
    SdrShaderNodeDiscoveryResultVec foundNodes;
    SdrStringSet foundNames;
    ArResolverScopedCache resolverCache;

    for (const std::string& searchPath : _searchPaths) {

        if (!TfIsDir(searchPath)) {
            continue;
        }

        TfWalkDirs(
            searchPath,
            std::bind(
                &examineFiles,
                &foundNodes,
                &foundNames,
                &context,
                std::placeholders::_1,
                std::placeholders::_3
            ),
            /* topDown = */ true,
            TfWalkIgnoreErrorHandler,
            /* followSymlinks = */ true
        );
    }

    return foundNodes;
}

SDR_REGISTER_DISCOVERY_PLUGIN(MoonrayDiscoveryPlugin);

PXR_NAMESPACE_CLOSE_SCOPE
