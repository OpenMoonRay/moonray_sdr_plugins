// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H

#include "pxr/pxr.h"
#include "pxr/base/tf/token.h"

#include "pxr/usd/sdr/declare.h"
#include "pxr/usd/sdr/parserPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdrShaderNode;
struct SdrShaderNodeDiscoveryResult;

class MoonrayParserPlugin : public SdrParserPlugin {
public:
    MoonrayParserPlugin() = default;

    ~MoonrayParserPlugin() override = default;

    SdrShaderNodeUniquePtr ParseShaderNode(
        const SdrShaderNodeDiscoveryResult &discoveryResult)
        override;

    const SdrTokenVec &GetDiscoveryTypes() const override;

    const TfToken &GetSourceType() const override;

};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
