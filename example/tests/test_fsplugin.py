"""Unit tests for the mesh plugin."""

import sys
from example_mesh_library import Mesh
import meshplugin

class TestFoo():
    """Test cases for the Foo class in the meshplugin module."""
    def test_init(self, mesh):
        """
        Test that the Foo constructor initializes successfully.

        Asserts:
            - The Foo instance is successfully created.
        """
        foo = meshplugin.Foo(mesh)
        assert foo

    def test_clone(self, mesh):
        """
        Test that the clone method creates a valid copy of the mesh.

        Asserts:
            - The cloned object is of the same type as the original mesh.
            - The cloned mesh has the same number of nodes as the original.
        """
        foo = meshplugin.Foo(mesh)

        mesh_copy = foo.clone()

        correct_type = isinstance(mesh_copy, type(mesh))
        equal_number_of_nodes = mesh_copy.numNodes() == mesh.numNodes()
        assert correct_type and equal_number_of_nodes

    def test_info(self, mesh):
        """
        Test that the info method executes without error.

        Asserts:
            - The info method completes successfully (no exceptions raised).
        """
        meshplugin.Foo(mesh).info()


def test_create_mesh():
    """
    Test that the create_mesh function returns a valid Mesh object.

    Asserts:
        - The returned object is an instance of Mesh.
    """
    mesh = meshplugin.create_mesh()
    assert isinstance(mesh, Mesh)


def test_ref_count_foo(mesh):
    """
    Test that the Foo instance properly manages reference counting for the mesh.

    Args:
        mesh: A mesh object to test reference counting with.

    Asserts:
        - The reference count increases by 1 when Foo is created.
        - The reference count returns to the original value when Foo is deleted.
    """
    mesh_ref_cnt = sys.getrefcount(mesh)

    foo = meshplugin.Foo(mesh)
    correct_ref_count_before = sys.getrefcount(mesh) == mesh_ref_cnt + 1

    del foo
    correct_ref_count_after =  sys.getrefcount(mesh) == mesh_ref_cnt

    assert correct_ref_count_after and correct_ref_count_before


def test_ref_count_create_mesh():
    """
    Test that the create_mesh function maintains proper reference counting.

    Asserts:
        - The reference count of the mesh returned by create_mesh is increased i.e. 2 in this case.
    """
    mesh = meshplugin.create_mesh()
    mesh_ref_cnt = sys.getrefcount(mesh)
    assert mesh_ref_cnt == 2
