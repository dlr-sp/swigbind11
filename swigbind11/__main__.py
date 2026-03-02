"""
CLI entry point for the package.

This module provides a command-line interface to access package configuration
metadata, specifically the location of the installed CMake files. It is
intended to be invoked via `python -m <package_name>`.
"""

from __future__ import annotations

import argparse
import functools
import sys

from .commands import get_cmake_dir

def main() -> None:
    """
    Execute the main command-line interface logic.

    Configures an argument parser to handle user requests for package
    information.
    """

    make_parser = functools.partial(argparse.ArgumentParser, allow_abbrev=False)

    if sys.version_info >= (3, 14):
        make_parser = functools.partial(make_parser, color=True, suggest_on_error=True)

    parser = make_parser()
    parser.add_argument(
        "--cmakedir",
        action="store_true",
        help="Print the CMake config directory.",
    )

    args = parser.parse_args()

    if not sys.argv[1:]:
        parser.print_help()
        sys.exit(0)

    if args.cmakedir:
        try:
            print(get_cmake_dir())
        except ImportError as e:
            print(e, file=sys.stderr)
            sys.exit(1)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
