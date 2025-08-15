#include "pydirectx.h"
#include <iostream>

#ifdef _WIN32
#include <d3d12.h>
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxgi.lib")
#endif

void PyDirectX::init(int ver) {
    if(ver == 10) version = DXVersion::DX10;
    else if(ver == 11) version = DXVersion::DX11;
    else if(ver == 12) version = DXVersion::DX12;
    else throw std::runtime_error("Unsupported DirectX version");

    // Simple GPU/driver check
    bool supported = false;
#ifdef _WIN32
    IDXGIFactory* factory = nullptr;
    if(SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory))) {
        IDXGIAdapter* adapter = nullptr;
        if(factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
            supported = false;
        else supported = true;
        if(adapter) adapter->Release();
        factory->Release();
    }
#endif
    if(!supported)
        throw std::runtime_error("DirectX/Direct3D " + std::to_string(ver) + " is not supported");

    d3d = std::make_unique<D3DRenderer>();
    dx  = std::make_unique<DXRenderer>();
}

// ------------- D3DRenderer -------------
void D3DRenderer::render_triangle(float x, float y, float z,
                                  float height, float width,
                                  float rotation, float depth,
                                  const std::string& texture) {
    std::cout << "Render triangle at " << x << "," << y << "," << z << " with texture: " << texture << "\n";
}
void D3DRenderer::render_box(float x, float y, float z,
                             float height, float width,
                             float rotation, float depth,
                             const std::string& texture) {
    std::cout << "Render box with texture: " << texture << "\n";
}
void D3DRenderer::render_circle(float x, float y, float z,
                                float height, float width,
                                float rotation, float depth,
                                const std::string& texture) {
    std::cout << "Render circle with texture: " << texture << "\n";
}
void D3DRenderer::render_3dtext(float x, float y, float z,
                                float height, float width,
                                float rotation, float depth,
                                const std::string& text,
                                const std::string& texture) {
    std::cout << "Render 3D text: " << text << " with texture: " << texture << "\n";
}
void D3DRenderer::remove_triangle(int id) {}
void D3DRenderer::remove_box(int id) {}
void D3DRenderer::remove_circle(int id) {}
void D3DRenderer::remove_3dtext(int id) {}

// ------------- DXRenderer -------------
void DXRenderer::render_text(const std::string& text, float x, float y, float size) {
    std::cout << "Render text: " << text << "\n";
}
void DXRenderer::render_box(float x, float y, float width, float height, const std::string& color) {
    std::cout << "Render 2D box with color: " << color << "\n";
}
void DXRenderer::clear() {
    std::cout << "Clear screen\n";
}

// ---------------- PYBIND11 MODULE ----------------
PYBIND11_MODULE(pydirectx, m) {
    py::class_<PyDirectX>(m, "PyDirectX")
        .def(py::init<>())
        .def("init", &PyDirectX::init)
        .def_readonly("d3d", &PyDirectX::d3d)
        .def_readonly("dx", &PyDirectX::dx);

    py::class_<D3DRenderer>(m, "D3DRenderer")
        .def("render_triangle", &D3DRenderer::render_triangle,
             py::arg("x"), py::arg("y"), py::arg("z"),
             py::arg("height"), py::arg("width"),
             py::arg("rotation"), py::arg("depth"),
             py::arg("texture") = "")
        .def("render_box", &D3DRenderer::render_box,
             py::arg("x"), py::arg("y"), py::arg("z"),
             py::arg("height"), py::arg("width"),
             py::arg("rotation"), py::arg("depth"),
             py::arg("texture") = "")
        .def("render_circle", &D3DRenderer::render_circle,
             py::arg("x"), py::arg("y"), py::arg("z"),
             py::arg("height"), py::arg("width"),
             py::arg("rotation"), py::arg("depth"),
             py::arg("texture") = "")
        .def("render_3dtext", &D3DRenderer::render_3dtext,
             py::arg("x"), py::arg("y"), py::arg("z"),
             py::arg("height"), py::arg("width"),
             py::arg("rotation"), py::arg("depth"),
             py::arg("text"), py::arg("texture") = "")
        .def("remove_triangle", &D3DRenderer::remove_triangle)
        .def("remove_box", &D3DRenderer::remove_box)
        .def("remove_circle", &D3DRenderer::remove_circle)
        .def("remove_3dtext", &D3DRenderer::remove_3dtext);

    py::class_<DXRenderer>(m, "DXRenderer")
        .def("render_text", &DXRenderer::render_text)
        .def("render_box", &DXRenderer::render_box)
        .def("clear", &DXRenderer::clear);
}
