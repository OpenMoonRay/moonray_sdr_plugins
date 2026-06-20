# moonray_sdr_plugins
These plugins add descriptions of the moonray shader DSOs to the Pixar shader registry (Sdr),
which is required to use them as shader nodes in USD/Hydra.

This repository is part of the larger MoonRay/Arras codebase.  It is included as a submodule in the top-level
OpenMoonRay repository located here: [OpenMoonRay](https://github.com/dreamworksanimation/openmoonray)

## Houdini 20.5 SDR Type Contract

The MoonRay parser maps RDL attribute metadata into Sdr properties consumed by
Houdini, Hydra, and USD shader discovery. For Houdini 20.5 the parser must
provide an Sdf type and default value with matching shape for every mapped RDL
type.

Important mappings:

- `Bool` and `BoolVector` keep real boolean defaults.
- `Rgb` / `Rgba` map to `color3f` / `color4f`.
- `RgbVector` / `RgbaVector` map to `color3f[]` / `color4f[]` with dynamic
  array metadata.
- Numeric vector arrays map to `float2[]`, `float3[]`, `float4[]`,
  `double2[]`, `double3[]`, and `double4[]`.
- `Mat4f` / `Mat4d` and their vector forms use `matrix4d` / `matrix4d[]`,
  because Houdini 20.5 does not expose a valid `matrix4f` Sdf type.
- Scene object pointer/indexable vectors use token-shaped fallbacks.

Ramp-like MoonRay attributes preserve the coredata grouping metadata
`structure_name`, `structure_path`, and `structure_type` in the Sdr property
metadata. This keeps light-filter and material ramps discoverable as grouped
ramps while preserving valid Sdf/default shapes. For example,
`ColorRampLightFilter.colors` and Dwa material `iridescence_colors` are dynamic
`color3f[]` arrays, while Rod/VDB light-filter non-color ramp values are dynamic
`float[]` arrays and their interpolation controls are dynamic `int[]` arrays.
