from setuptools import setup, Extension
import sys
import pybind11

# Get the include path for pybind11
include_dirs = [
    pybind11.get_include(),
]

# Source file
sources = ["pydirectx.cpp"]

# Define the extension
pydirectx_module = Extension(
    "pydirectx",
    sources=sources,
    include_dirs=include_dirs,
    language="c++",
    extra_compile_args=[
        "/std:c++17",  # Use C++17 for MSVC
        "/O2"          # Optimization
    ],
    extra_link_args=[]
)

setup(
    name="pydirectx",
    version="0.1",
    description="Direct3D/DirectX Python binding",
    ext_modules=[pydirectx_module],
)
