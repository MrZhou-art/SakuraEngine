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
		// ��ʼ�� Dear ImGui ������
		IMGUI_CHECKVERSION();          // ��� ImGui �汾�����ԣ�ȷ���뵱ǰ���ƥ�䣩
		ImGui::CreateContext();        // ���� ImGui ���������ģ��������ȵ��ã�

		ImGuiIO& io = ImGui::GetIO();  // ��ȡ ImGui ����������ã����̡���ꡢ��Ϸ�ֱ��ȣ�
		(void)io;                      // ���� "δʹ�ñ���" ���棨��������Ҫʹ�ÿ��Ƴ���

		// ���� ImGui ��������
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // ���ü��̵�����Tab/Shift+Tab ���л����㣩
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // ������Ϸ�ֱ�����������ȡ��ע�ͣ�
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // ���ô���ͣ�����֣�֧����ק���ںϲ�/��֣�***
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // ���ö��ӿڣ�֧�ֶ����������ڵĵ������ڣ�
		//io.ConfigViewportsNoAutoMerge = true;                     // �����ӿ��Զ��ϲ����߼����ã��������ã�
		//io.ConfigViewportsNoTaskBarIcon = true;                   // �ӿڲ���ʾ�����������ʺϹ��ߴ��ڣ�

		// ���� ImGui ������
		ImGui::StyleColorsDark();        // ʹ����ɫ���⣨ ImGui �������⣺Dark/Light/Classic��

		// �ӿ�ģʽ�µ���ʽ������ʹϵͳ������ ImGui �������һ�£�
		ImGuiStyle& style = ImGui::GetStyle();  // ��ȡ��ǰ��ʽ����
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;         // ȡ������Բ�ǣ�ϵͳԭ������ͨ����Բ�ǣ�
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;  // ���ڱ�����ȫ��͸����������ϵͳ���ڻ�����
		}

		// ��ȡ��ǰӦ�õĴ��ھ����GLFW ����ָ�룩
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

		// ��ʼ�� ImGui ƽ̨����Ⱦ���
		bool success = ImGui_ImplGlfw_InitForOpenGL(window, true);  // ��ʼ�� GLFW ƽ̨��ˣ��ڶ����������Ƿ�װ GLFW ����ص���
		success &= ImGui_ImplOpenGL3_Init("#version 460");       // ��ʼ�� OpenGL ��Ⱦ��ˣ�������GLSL �汾���������Կ�֧��ƥ�䣩
		if (!success)
		{
			assert(false);
		}
	}

	void ImGuiLayer::OnDetach()
	{
		//����
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdata()
	{
		
	}


	void ImGuiLayer::Begin()
	{
		assert(ImGui::GetCurrentContext() != nullptr);//��� ImGui �������Ƿ��Ѵ���
		//��ʼ�� OpenGL, Glfw ״̬
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		// ���� ImGui ����ʾ�ߴ磨��Ӧ�ô��ڴ�Сͬ����
		ImGuiIO& io = ImGui::GetIO();
		auto& app = Application::GetApplication();
		io.DisplaySize = ImVec2{ (float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight() };  // �� ImGui ���߼��ֱ�������ΪӦ�ô��ڵ�����ߴ�

		// ��Ⱦ�׶�
		ImGui::Render();  // ���� ImGui �Ļ������ݣ����㡢��������ʽ��Ϣ�ȣ�
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  // ͨ�� OpenGL �����Ⱦ ImGui �Ļ�������

		// ���²���Ⱦ�����ƽ̨���ڣ����ӿ�֧�֣�
		// ��ƽ̨��غ������ܻ�ı䵱ǰ OpenGL �����ģ�������Ǳ���/�ָ��������Ա��ڴ�����ֲ��
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)  // ��������˶��ӿڹ���
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();  // ���浱ǰ OpenGL �����ģ���ֹ��ƽ̨�����޸ģ�
			ImGui::UpdatePlatformWindows();  // ����ƽ̨��ش��ڣ�������������ڵĵ������ڣ�
			ImGui::RenderPlatformWindowsDefault();  // ��Ⱦƽ̨���ڵ���ۣ����������߿��ϵͳԭ��Ԫ�أ�
			glfwMakeContextCurrent(backup_current_context);  // �ָ�֮ǰ�� OpenGL �����ģ�ȷ��������Ⱦʹ����ȷ�������ģ�
		}
	}


	void ImGuiLayer::OnImGuiRender()
	{
		//��ʾ����
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}