#include "sakuraPCH.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Sakura/Application.h"

namespace Sakura
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}
	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach()
	{
		// 初始化 Dear ImGui 上下文
		IMGUI_CHECKVERSION();          // 检查 ImGui 版本兼容性（确保与当前后端匹配）
		ImGui::CreateContext();        // 创建 ImGui 核心上下文（必须首先调用）

		ImGuiIO& io = ImGui::GetIO();  // 获取 ImGui 输入输出配置（键盘、鼠标、游戏手柄等）
		(void)io;                      // 抑制 "未使用变量" 警告（若后续需要使用可移除）

		// 启用 ImGui 功能特性
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 启用键盘导航（Tab/Shift+Tab 等切换焦点）
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // 启用游戏手柄导航（按需取消注释）
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 启用窗口停靠布局（支持拖拽窗口合并/拆分）***
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 启用多视口（支持独立于主窗口的弹出窗口）
		//io.ConfigViewportsNoAutoMerge = true;                     // 禁用视口自动合并（高级配置，按需启用）
		//io.ConfigViewportsNoTaskBarIcon = true;                   // 视口不显示在任务栏（适合工具窗口）

		// 设置 ImGui 主题风格
		ImGui::StyleColorsDark();        // 使用深色主题（ ImGui 内置主题：Dark/Light/Classic）

		// 视口模式下的样式调整（使系统窗口与 ImGui 窗口外观一致）
		ImGuiStyle& style = ImGui::GetStyle();  // 获取当前样式配置
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;         // 取消窗口圆角（系统原生窗口通常无圆角）
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;  // 窗口背景完全不透明（避免与系统窗口混淆）
		}

		// 获取当前应用的窗口句柄（GLFW 窗口指针）
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

		// 初始化 ImGui 平台及渲染后端
		bool success = ImGui_ImplGlfw_InitForOpenGL(window, true);  // 初始化 GLFW 平台后端（第二个参数：是否安装 GLFW 输入回调）
		success &= ImGui_ImplOpenGL3_Init("#version 460");       // 初始化 OpenGL 渲染后端（参数：GLSL 版本声明，与显卡支持匹配）
		if (!success)
		{
			assert(false);
		}
	}

	void ImGuiLayer::OnDetach()
	{
		//清理
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdata()
	{
		
	}


	void ImGuiLayer::Begin()
	{
		assert(ImGui::GetCurrentContext() != nullptr);//检查 ImGui 上下文是否已创建
		//初始化 OpenGL, Glfw 状态
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		// 设置 ImGui 的显示尺寸（与应用窗口大小同步）
		ImGuiIO& io = ImGui::GetIO();
		auto& app = Application::GetApplication();
		io.DisplaySize = ImVec2{ (float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight() };  // 将 ImGui 的逻辑分辨率设置为应用窗口的物理尺寸

		// 渲染阶段
		ImGui::Render();  // 生成 ImGui 的绘制数据（顶点、索引、样式信息等）
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  // 通过 OpenGL 后端渲染 ImGui 的绘制数据

		// 更新并渲染额外的平台窗口（多视口支持）
		// （平台相关函数可能会改变当前 OpenGL 上下文，因此我们保存/恢复上下文以便于代码移植。
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)  // 如果启用了多视口功能
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();  // 保存当前 OpenGL 上下文（防止被平台窗口修改）
			ImGui::UpdatePlatformWindows();  // 更新平台相关窗口（如独立于主窗口的弹出窗口）
			ImGui::RenderPlatformWindowsDefault();  // 渲染平台窗口的外观（标题栏、边框等系统原生元素）
			glfwMakeContextCurrent(backup_current_context);  // 恢复之前的 OpenGL 上下文（确保后续渲染使用正确的上下文）
		}
	}


	void ImGuiLayer::OnImGuiRender()
	{
		//演示窗口
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}