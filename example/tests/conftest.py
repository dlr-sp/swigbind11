"""Fixture for the unit test"""

import pytest

from example_mesh_library import Mesh

@pytest.fixture()
def mesh():
    """Generates a small mesh with four nodes and one element."""
    mesh = Mesh()

    mesh.addNode(0, 0, 0)
    mesh.addNode(1, 0, 0)
    mesh.addNode(0, 1, 0)
    mesh.addNode(0, 0, 1)

    mesh.addElement(0, 1, 2, 3)

    return mesh
