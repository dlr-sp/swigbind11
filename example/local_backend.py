import os
from scikit_build_core.build import *

def get_requires_for_build_wheel(config_settings=None):
    # Import the original requirements logic
    from scikit_build_core.build import get_requires_for_build_wheel as _get_reqs
    reqs = _get_reqs(config_settings)

    # Dynamically find the swigbind11 relative to this file
    base_dir = os.path.dirname(os.path.abspath(__file__))
    local_dep = os.path.abspath(os.path.join(base_dir, ".."))

    reqs.append(f"swigbind11 @ file://{local_dep}")
    return reqs
