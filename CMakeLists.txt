# Copyright 2023-2024 DreamWorks Animation LLC
# SPDX-License-Identifier: Apache-2.0

# TODO: setting this/these should not be necessary before calling find_package.
# see: https://stackoverflow.com/questions/55217771/boostcmake-no-suitable-build-variant
set(BUILD_SHARED_LIBS ON)
find_package(Boost REQUIRED)
add_compile_definitions(BOOST_NO_CXX98_FUNCTION_BASE)

# the DWA installation of pxrConfig.cmake lives in
# the usd_imaging Rez package. To work correctly, it
# requires env vars REZ_USD_CORE_ROOT, REZ_USD_IMAGING_ROOT
# and PXR_INCLUDE_DIRS to be set (e.g. in CMake preset).
# A standard installation should not require these...
if(NOT pxr_FOUND)
    find_package(pxr REQUIRED)
endif()

if(PXR_VERSION VERSION_GREATER_EQUAL 2605)
    set(MOONRAY_SHADER_PLUGIN_LIBRARIES ar sdr)
    set(MOONRAY_DISCOVERY_PLUGIN_BASE_CLASS SdrDiscoveryPlugin)
    set(MOONRAY_PARSER_PLUGIN_BASE_CLASS SdrParserPlugin)
else()
    set(MOONRAY_SHADER_PLUGIN_LIBRARIES ar ndr sdr)
    set(MOONRAY_DISCOVERY_PLUGIN_BASE_CLASS NdrDiscoveryPlugin)
    set(MOONRAY_PARSER_PLUGIN_BASE_CLASS NdrParserPlugin)
endif()

find_package(Python REQUIRED COMPONENTS Development)

add_subdirectory(moonrayShaderDiscovery)
add_subdirectory(moonrayShaderParser)
