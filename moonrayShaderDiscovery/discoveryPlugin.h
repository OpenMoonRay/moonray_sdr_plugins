// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H

#include "pxr/pxr.h"
#include "pxr/base/tf/token.h"

#include "../UsdShaderApi.h"

PXR_NAMESPACE_OPEN_SCOPE

class MoonrayDiscoveryPlugin : public MoonrayUsdShaderApi::DiscoveryPlugin {
public:
    MoonrayDiscoveryPlugin();

    ~MoonrayDiscoveryPlugin() override = default;

#if PXR_VERSION >= 2605
    MoonrayUsdShaderApi::NodeDiscoveryResultVec DiscoverShaderNodes(
        const Context& context) override;
#else
    MoonrayUsdShaderApi::NodeDiscoveryResultVec DiscoverNodes(
        const Context& context) override;
#endif

    const MoonrayUsdShaderApi::StringVec& GetSearchURIs() const override;

private:
    MoonrayUsdShaderApi::StringVec _searchPaths;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
