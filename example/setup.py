from skbuild import setup

setup(
    packages=['fsplugin'],
    package_dir={'': 'src'},
    cmake_install_dir='src/fsplugin',
)
