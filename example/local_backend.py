"""
Custom build backend for scikit-build-core.

This module acts as a wrapper around scikit-build-core to handle local
dependencies that are not yet available on PyPI. It specifically allows
the injection of 'swigbind11' from a relative path, bypassing the
limitation in scikit-build-core which disallows relative paths in
the 'build-system.requires' section of pyproject.toml.
"""
import os
from scikit_build_core.build import *

def get_requires_for_build_wheel(config_settings=None):
    """
    Return a list of dependencies required to build the wheel.

    This dynamically locates 'swigbind11' relative to this
    script's directory and appends it to the build requirements as absolute path.
    """
    from scikit_build_core.build import get_requires_for_build_wheel as _get_reqs
    reqs = _get_reqs(config_settings)

    # Dynamically find the swigbind11 relative to this file
    base_dir = os.path.dirname(os.path.abspath(__file__))
    local_dep = os.path.abspath(os.path.join(base_dir, ".."))

    reqs.append(f"swigbind11 @ file://{local_dep}")
    return reqs
