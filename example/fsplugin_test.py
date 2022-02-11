import os
import sys
import pathlib
from FSDataManager import FSClac, FSMesh

sys.path.append(os.getcwd())
import fsplugin

clac = FSClac()
mesh = FSMesh(clac)

mesh_file = pathlib.Path(os.path.realpath(__file__)).parent / \
    'data' / 'hexcube_10x10x10.h5'

print(mesh_file)

mesh.ImportMeshHDF5(Filename=mesh_file)

plugin = fsplugin.Plugin(mesh)
plugin.process()
