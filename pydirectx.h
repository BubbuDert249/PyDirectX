#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>

namespace py = pybind11;

// Supported versions
enum class DXVersion { DX10 = 10, DX11 = 11, DX12 = 12 };

// Forward declarations for D3D/DX classes
class D3DRenderer;
class DXRenderer;

class PyDirectX {
public:
    PyDirectX() : version(DXVersion::DX12) {}

    void init(int ver);  // Initialize DirectX/D3D

    std::unique_ptr<D3DRenderer> d3d;
    std::unique_ptr<DXRenderer> dx;

private:
    DXVersion version;
};

// ----------- D3D Commands -----------
class D3DRenderer {
public:
    void render_triangle(float x, float y, float z,
                         float height, float width,
                         float rotation, float depth,
                         const std::string& texture = "");
    void render_box(float x, float y, float z,
                    float height, float width,
                    float rotation, float depth,
                    const std::string& texture = "");
    void render_circle(float x, float y, float z,
                       float height, float width,
                       float rotation, float depth,
                       const std::string& texture = "");
    void render_3dtext(float x, float y, float z,
                       float height, float width,
                       float rotation, float depth,
                       const std::string& text,
                       const std::string& texture = "");

    void remove_triangle(int id);
    void remove_box(int id);
    void remove_circle(int id);
    void remove_3dtext(int id);

private:
    std::vector<int> objects; // simple object registry
};

// ----------- DX Commands -----------
class DXRenderer {
public:
    void render_text(const std::string& text, float x, float y, float size);
    void render_box(float x, float y, float width, float height, const std::string& color = "white");
    void clear();
};
