"""Expose MoonRay's USD Python plugin stubs to Houdini's pxr package.

Houdini ships pxr as a regular Python package instead of a namespace package, so
adding MoonRay's lib/python directory to PYTHONPATH is not enough for imports
such as pxr.MoonrayShaderParser.  The Sdr plugins are native USD plugins; these
small Python stubs only prevent Plug from reporting missing Python modules when
the native parser/discovery plugins are loaded.
"""

import os

try:
    import pxr

    moonray_pxr_path = os.path.join(os.path.dirname(__file__), "pxr")
    if hasattr(pxr, "__path__") and moonray_pxr_path not in pxr.__path__:
        pxr.__path__.append(moonray_pxr_path)
except Exception:
    pass
