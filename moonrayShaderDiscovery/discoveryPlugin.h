// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H

#include "pxr/pxr.h"
#include "pxr/base/tf/token.h"

#include "pxr/usd/sdr/declare.h"
#include "pxr/usd/sdr/discoveryPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

class MoonrayDiscoveryPlugin : public SdrDiscoveryPlugin {
public:
    MoonrayDiscoveryPlugin();

    ~MoonrayDiscoveryPlugin() override = default;

    virtual SdrShaderNodeDiscoveryResultVec DiscoverShaderNodes(const Context &context)
        override;

    virtual const SdrStringVec& GetSearchURIs() const override;

private:
    SdrStringVec _searchPaths;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
