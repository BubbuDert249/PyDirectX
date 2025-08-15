#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdexcept>
#include <string>

namespace pydirectx {

enum class Version {
    DX10 = 10,
    DX11 = 11,
    DX12 = 12
};

enum class APIType {
    DX,
    D3D,
    BOTH
};

class DirectX {
public:
    DirectX(Version version);
    void render_text(int x, int y, const std::string &text, int width = 100, int height = 20);

private:
    Version version_;
    void check_support();
};

class Direct3D {
public:
    Direct3D(Version version);
    void render_triangle(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture = "");
    void render_box(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture = "");
    void render_circle(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &texture = "");
    void render_3dtext(int x, int y, int z, int width, int height, int rotation, int depth, const std::string &text, const std::string &texture = "");
    void remove_triangle();
    void remove_box();
    void remove_circle();
    void remove_3dtext();

private:
    Version version_;
    void check_support();
};

class PyDirectX {
public:
    static void init(int version, const std::string &api);
    static DirectX dx;
    static Direct3D d3d;
};

} // namespace pydirectx
