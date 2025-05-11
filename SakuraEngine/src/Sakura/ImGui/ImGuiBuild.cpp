#include "sakuraPCH.h"

//禁用默认 imgui 加载器(glad),使用自定义的 OpenGL 函数加载器(glad)
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"