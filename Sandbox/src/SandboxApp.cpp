#include <Sakura.h>

#include "imgui/imgui.h"

#include <glm/glm.hpp>

class ExampleLayer : public Sakura::Layer
{
public:
	ExampleLayer() 
		: Layer("example") 
	{
	}

	void OnUpdata() override
	{
		if(Sakura::Input::IsKeyPressed(SAKURA_KEY_TAB))
			SAKURA_INFO("TAB is pressed(onUpdata)!");
	}
	void OnEvent(Sakura::Event& e) override
	{
		if (e.GetEventType() == Sakura::EventType::KeyPressed)
		{
			Sakura::KeyPressedEvent& keyEvent = (Sakura::KeyPressedEvent&)e;
			SAKURA_TRACE("{0}", (char)keyEvent.GetKeyCode());

			if (keyEvent.GetKeyCode() == SAKURA_KEY_TAB)
				SAKURA_INFO("TAB is pressed(onEvent)!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, ImGui!");
		ImGui::End();
	}
};

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

private:
};




Sakura::Application* Sakura::createApplication()
{
	return new Sandbox();
}