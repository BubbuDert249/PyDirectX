#include "pydirectx.h"
#include <iostream>

namespace py = pybind11;
using namespace pydirectx;

// --- Implementation ---

void DirectX::check_support() {
    // Here you should query your GPU for support. Placeholder:
    if (version_ < Version::DX10 || version_ > Version::DX12)
        throw std::runtime_error("DirectX version not supported by GPU.");
}

DirectX::DirectX(Version version) : version_(version) {
    check_support();
}

void DirectX::render_text(int x, int y, const std::string &text, int width, int height) {
    std::cout << "[DX" << int(version_) << "] Render Text: " << text << " at (" << x << "," << y << ")\n";
}

// -------------------

void Direct3D::check_support() {
    if (version_ < Version::DX10 || version_ > Version::DX12)
        throw std::runtime_error("Direct3D version not supported by GPU.");
}

Direct3D::Direct3D(Version version) : version_(version) {
    check_support();
}

void Direct3D::render_triangle(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture) {
    std::cout << "[D3D" << int(version_) << "] Render Triangle at (" << x << "," << y << "," << z << ") with texture: " << texture << "\n";
}

void Direct3D::render_box(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture) {
    std::cout << "[D3D" << int(version_) << "] Render Box at (" << x << "," << y << "," << z << ") with texture: " << texture << "\n";
}

void Direct3D::render_circle(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture) {
    std::cout << "[D3D" << int(version_) << "] Render Circle at (" << x << "," << y << "," << z << ") with texture: " << texture << "\n";
}

void Direct3D::render_3dtext(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &text, const std::string &texture) {
    std::cout << "[D3D" << int(version_) << "] Render 3D Text: " << text << " at (" << x << "," << y << "," << z << ") with texture: " << texture << "\n";
}

void Direct3D::remove_triangle() { std::cout << "Remove Triangle\n"; }
void Direct3D::remove_box() { std::cout << "Remove Box\n"; }
void Direct3D::remove_circle() { std::cout << "Remove Circle\n"; }
void Direct3D::remove_3dtext() { std::cout << "Remove 3D Text\n"; }

// -------------------

DirectX PyDirectX::dx = DirectX(Version::DX10);   // default placeholder
Direct3D PyDirectX::d3d = Direct3D(Version::DX10);

void PyDirectX::init(int version, const std::string &api) {
    Version ver = static_cast<Version>(version);
    if (api == "dx") {
        dx = DirectX(ver);
    } else if (api == "d3d") {
        d3d = Direct3D(ver);
    } else if (api == "both") {
        dx = DirectX(ver);
        d3d = Direct3D(ver);
    } else {
        throw std::runtime_error("Invalid API type, must be 'dx', 'd3d', or 'both'");
    }
}

// --- PYBIND11 MODULE ---

PYBIND11_MODULE(pydirectx, m) {
    py::class_<DirectX>(m, "DirectX")
        .def("render_text", &DirectX::render_text);

    py::class_<Direct3D>(m, "Direct3D")
        .def("render_triangle", &Direct3D::render_triangle)
        .def("render_box", &Direct3D::render_box)
        .def("render_circle", &Direct3D::render_circle)
        .def("render_3dtext", &Direct3D::render_3dtext)
        .def("remove_triangle", &Direct3D::remove_triangle)
        .def("remove_box", &Direct3D::remove_box)
        .def("remove_circle", &Direct3D::remove_circle)
        .def("remove_3dtext", &Direct3D::remove_3dtext);

    py::class_<PyDirectX>(m, "pydirectx")
        .def_static("init", &PyDirectX::init)
        .def_readwrite_static("dx", &PyDirectX::dx)
        .def_readwrite_static("d3d", &PyDirectX::d3d);
}
