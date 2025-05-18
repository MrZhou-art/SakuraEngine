#pragma once

//此头文件用于引入 SakuraEngine 接口文件

#include "Sakura/Application.h"//应用层
#include "Sakura/Layer/Layer.h"//图层
#include "Sakura/Log/Log.h"//日志记录器

#include "Sakura/Core/Timestep.h"

#include "Sakura/ImGui/ImGuiLayer.h"// ImGui 图层
//--------- 输入轮询系统 -------------
#include "Sakura/Input/Input.h"
#include "Sakura/Input/KeyCodes.h"
#include "Sakura/Input/MouseButtonCodes.h"

//--------- 渲染器 -------------
#include "Sakura/Renderer/RendererCommand.h"
#include "Sakura/Renderer/Renderer.h"

#include "Sakura/Renderer/Buffer.h"
#include "Sakura/Renderer/VertexArray.h"
#include "Sakura/Renderer/RendererAPI.h"
#include "Sakura/Renderer/Shader.h"

//--------- 相机 -------------
#include "Sakura/Camera/OrthographicCamera.h"
#include "Sakura/Camera/PerspectiveCamera.h"

//--------- 入口点 -------------
#include "Sakura/EntryPoint.h"
//----------------------------