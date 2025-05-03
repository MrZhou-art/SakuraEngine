#pragma once

#include "Sakura/Layer.h"

#include "Sakura/Events/MouseEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/ApplicationEvent.h"

namespace Sakura
{
	class SAKURA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		//ͼ�㹦�ܻص�����
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdata() override;
		void OnEvent(Event& e) override;

	private:
		//ͼ���¼�
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}