"""
swigbind11: A bridge between SWIG and pybind11.

This package provides utilities for integrating SWIG-generated code with
pybind11 projects, including CMake discovery tools and path helpers.

Available functions:
    - get_cmake_dir: Returns the installation path of the CMake module files.
"""

from __future__ import annotations

from .commands import get_cmake_dir

__all__ = (
    "get_cmake_dir",
)
