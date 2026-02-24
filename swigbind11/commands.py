"""
Path discovery utilities for the swigbind11 package.

This module provides helper functions to locate internal package resources
and installation directories, primarily for use by build systems (like CMake)
and CLI tools.
"""

import os
from pathlib import Path

# The absolute path to the directory containing this file
DIR = Path(__file__).parent.resolve()


def get_cmake_dir() -> str:
    """
    Locate the swigbind11 CMake module configuration directory.

    This function searches for the 'share/cmake/swigbind11' directory relative
    to the package installation path. This directory typically contains
    'swigbind11Config.cmake' used by external projects.

    Returns:
        str: The absolute path to the CMake module directory.

    Raises:
        ImportError: If the CMake directory cannot be found, usually
            indicating that the package was not installed correctly or
            is being run from a source tree without a build.
    """
    cmake_installed_path = os.path.join(DIR, "share", "cmake", "swigbind11")
    if os.path.exists(cmake_installed_path):
        return cmake_installed_path

    msg = f"Path {cmake_installed_path} does not exist."
    raise ImportError(msg)
