import pathlib
import pytest
import os

from FSDataManager import FSClac, FSMesh


@pytest.fixture()
def clac():
    return FSClac()


@pytest.fixture()
def mesh(clac):
    mesh = FSMesh(clac)

    mesh_file = pathlib.Path(os.path.realpath(__file__)).parent / \
        'data' / 'hexcube_10x10x10.h5'

    assert mesh.ImportMeshHDF5(Filename=mesh_file)

    return mesh
