// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H

#include "pxr/pxr.h"
#include "pxr/base/tf/token.h"

#include "../UsdShaderApi.h"

PXR_NAMESPACE_OPEN_SCOPE

class MoonrayParserPlugin : public MoonrayUsdShaderApi::ParserPlugin {
public:
    MoonrayParserPlugin() = default;

    ~MoonrayParserPlugin() override = default;

#if PXR_VERSION >= 2605
    MoonrayUsdShaderApi::NodeUniquePtr ParseShaderNode(
        const MoonrayUsdShaderApi::NodeDiscoveryResult& discoveryResult) override;
#else
    MoonrayUsdShaderApi::NodeUniquePtr Parse(
        const MoonrayUsdShaderApi::NodeDiscoveryResult& discoveryResult) override;
#endif

    const MoonrayUsdShaderApi::TokenVec& GetDiscoveryTypes() const override;

#if PXR_VERSION >= 2605
    const TfToken& GetShadingSystem() const override;
#else
    const TfToken& GetSourceType() const override;
#endif

};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
