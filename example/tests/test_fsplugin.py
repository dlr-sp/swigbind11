import sys

from FSDataManager import FSFloatArray, FSMesh, FSMeshEnums

import fsplugin


class TestFoo():
    def test_init(clac, mesh):
        foo = fsplugin.Foo(mesh)
        assert foo

    def test_clone(clac, mesh):
        foo = fsplugin.Foo(mesh)

        mesh_copy = foo.clone()

        assert isinstance(mesh_copy, type(mesh))
        assert mesh_copy.IsInitialized()
        assert mesh_copy.ThisPtr() != mesh.ThisPtr()
        assert mesh_copy.GetNCells(FSMeshEnums.CT_Hexa8) == \
            mesh.GetNCells(FSMeshEnums.CT_Hexa8)

    def test_get_coordinates(clac, mesh):
        foo = fsplugin.Foo(mesh)

        data = foo.get_coordinates()
        assert isinstance(data, FSFloatArray)
        assert data.Size(0) == mesh.GetNOwnedCells(FSMeshEnums.CT_Node)
        assert data.Size(1) == 3

    def test_info(clac, mesh):
        fsplugin.Foo(mesh).info()


def test_create_mesh(clac):
    mesh = fsplugin.create_mesh(clac)
    assert mesh
    assert isinstance(mesh, FSMesh)


def test_ref_count_foo(mesh):
    mesh_ref_cnt = sys.getrefcount(mesh)

    foo = fsplugin.Foo(mesh)
    assert sys.getrefcount(mesh) == mesh_ref_cnt + 1

    del foo
    assert sys.getrefcount(mesh) == mesh_ref_cnt


def test_ref_count_create_mesh(clac):
    mesh = fsplugin.create_mesh(clac)
    mesh_ref_cnt = sys.getrefcount(mesh)
    assert mesh_ref_cnt == 2
