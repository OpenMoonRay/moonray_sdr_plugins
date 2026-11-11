// Copyright 2026 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "pxr/pxr.h"

#if PXR_VERSION >= 2605
#include "pxr/usd/sdr/debugCodes.h"
#include "pxr/usd/sdr/discoveryPlugin.h"
#include "pxr/usd/sdr/parserPlugin.h"
#include "pxr/usd/sdr/shaderNodeDiscoveryResult.h"
#else
#include "pxr/usd/ndr/debugCodes.h"
#include "pxr/usd/ndr/discoveryPlugin.h"
#include "pxr/usd/ndr/parserPlugin.h"
#include "pxr/usd/ndr/nodeDiscoveryResult.h"
#endif

PXR_NAMESPACE_OPEN_SCOPE

namespace MoonrayUsdShaderApi {

#if PXR_VERSION >= 2605
using DiscoveryPlugin = SdrDiscoveryPlugin;
using DiscoveryPluginContext = SdrDiscoveryPluginContext;
using Identifier = SdrIdentifier;
using NodeDiscoveryResult = SdrShaderNodeDiscoveryResult;
using NodeDiscoveryResultVec = SdrShaderNodeDiscoveryResultVec;
using NodeUniquePtr = SdrShaderNodeUniquePtr;
using OptionVec = SdrOptionVec;
using ParserPlugin = SdrParserPlugin;
using PropertyUniquePtrVec = SdrShaderPropertyUniquePtrVec;
using StringSet = SdrStringSet;
using StringVec = SdrStringVec;
using TokenMap = SdrTokenMap;
using TokenVec = SdrTokenVec;
using Version = SdrVersion;
#else
using DiscoveryPlugin = NdrDiscoveryPlugin;
using DiscoveryPluginContext = NdrDiscoveryPluginContext;
using Identifier = NdrIdentifier;
using NodeDiscoveryResult = NdrNodeDiscoveryResult;
using NodeDiscoveryResultVec = NdrNodeDiscoveryResultVec;
using NodeUniquePtr = NdrNodeUniquePtr;
using OptionVec = NdrOptionVec;
using ParserPlugin = NdrParserPlugin;
using PropertyUniquePtrVec = NdrPropertyUniquePtrVec;
using StringSet = NdrStringSet;
using StringVec = NdrStringVec;
using TokenMap = NdrTokenMap;
using TokenVec = NdrTokenVec;
using Version = NdrVersion;
#endif

} // namespace MoonrayUsdShaderApi

PXR_NAMESPACE_CLOSE_SCOPE

#if PXR_VERSION >= 2605
#define MOONRAY_REGISTER_DISCOVERY_PLUGIN SDR_REGISTER_DISCOVERY_PLUGIN
#define MOONRAY_REGISTER_PARSER_PLUGIN SDR_REGISTER_PARSER_PLUGIN
#define MOONRAY_SHADER_DISCOVERY_DEBUG SDR_DISCOVERY
#else
#define MOONRAY_REGISTER_DISCOVERY_PLUGIN NDR_REGISTER_DISCOVERY_PLUGIN
#define MOONRAY_REGISTER_PARSER_PLUGIN NDR_REGISTER_PARSER_PLUGIN
#define MOONRAY_SHADER_DISCOVERY_DEBUG NDR_DISCOVERY
#endif
