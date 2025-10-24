import sys
from example_mesh_library import Mesh
import meshplugin

class TestFoo():
    def test_init(self, mesh):
        foo = meshplugin.Foo(mesh)
        assert foo

    def test_clone(self, mesh):
        foo = meshplugin.Foo(mesh)

        mesh_copy = foo.clone()

        correct_type = isinstance(mesh_copy, type(mesh))
        equal_number_of_nodes = mesh_copy.numNodes() == mesh.numNodes()
        assert correct_type and equal_number_of_nodes

    def test_info(self, mesh):
        meshplugin.Foo(mesh).info()


def test_create_mesh():
    mesh = meshplugin.create_mesh()
    assert isinstance(mesh, Mesh)


def test_ref_count_foo(mesh):
    mesh_ref_cnt = sys.getrefcount(mesh)

    foo = meshplugin.Foo(mesh)
    correct_ref_count_before = sys.getrefcount(mesh) == mesh_ref_cnt + 1

    del foo
    correct_ref_count_after =  sys.getrefcount(mesh) == mesh_ref_cnt

    assert correct_ref_count_after and correct_ref_count_before


def test_ref_count_create_mesh():
    mesh = meshplugin.create_mesh()
    mesh_ref_cnt = sys.getrefcount(mesh)
    assert mesh_ref_cnt == 2
