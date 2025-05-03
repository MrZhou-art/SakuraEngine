#include <Sakura.h>



class ExampleLayer : public Sakura::Layer
{
public:
	ExampleLayer() 
		: Layer("example") {}

	void OnUpdata() override
	{
		SAKURA_INFO("ExampleLayer::UpData");
	}
	void OnEvent(Sakura::Event& e) override
	{
		SAKURA_TRACE("{0}",e.ToString());
	}
};

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverLayer(new Sakura::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};




Sakura::Application* Sakura::createApplication()
{
	return new Sandbox();
}