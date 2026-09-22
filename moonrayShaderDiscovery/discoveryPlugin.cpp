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

PXR_NAMESPACE_OPEN_SCOPE

TfToken moonrayNodeType("moonrayClass");

namespace {

bool examineFiles(MoonrayUsdShaderApi::NodeDiscoveryResultVec* foundNodes,
                  MoonrayUsdShaderApi::StringSet* foundNames,
                  const MoonrayUsdShaderApi::DiscoveryPluginContext* context,
                  const std::string& dirPath,
                  const MoonrayUsdShaderApi::StringVec& dirFileNames)
{
    for (const std::string& fileName : dirFileNames) {
        std::string extension = TfStringToLower(TfGetExtension(fileName));
        if (extension == "json") {
            std::string uri = TfStringCatPaths(dirPath, fileName);
            std::string className = TfStringGetBeforeSuffix(fileName, '.');

            if (!foundNames->insert(className).second) {
                 TF_DEBUG(MOONRAY_SHADER_DISCOVERY_DEBUG).Msg(
                     "Duplicate moonray class [%s] found at URI [%s], ignoring.",
                     className.c_str(), uri.c_str());
                continue;
            }

            foundNodes->emplace_back(
                MoonrayUsdShaderApi::Identifier(className),    // Identifier
                MoonrayUsdShaderApi::Version().GetAsDefault(), // Version
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

const MoonrayUsdShaderApi::StringVec&
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

#if PXR_VERSION >= 2605
MoonrayUsdShaderApi::NodeDiscoveryResultVec
MoonrayDiscoveryPlugin::DiscoverShaderNodes(const Context& context)
#else
MoonrayUsdShaderApi::NodeDiscoveryResultVec
MoonrayDiscoveryPlugin::DiscoverNodes(const Context& context)
#endif
{
    MoonrayUsdShaderApi::NodeDiscoveryResultVec foundNodes;
    MoonrayUsdShaderApi::StringSet foundNames;
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

MOONRAY_REGISTER_DISCOVERY_PLUGIN(MoonrayDiscoveryPlugin);

PXR_NAMESPACE_CLOSE_SCOPE
