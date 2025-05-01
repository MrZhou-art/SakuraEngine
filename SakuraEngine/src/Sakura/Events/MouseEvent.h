#pragma once

#include "Event.h"

namespace Sakura
{
	//���λ����Ϣ
	class SAKURA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) //���캯��(������� XY λ��)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetMouseX() const { return m_MouseX; } //��ȡ��� X λ��
		inline float GetMouseY() const { return m_MouseY; } //��ȡ��� Y λ��

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "MouseX: " << m_MouseX << ", MouseY: " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//���ɻ�ȡ����Ϣ����ĺ���
		EVENT_CLASS_TYPE(EventType::MouseMoved)//���� Type ��صĺ���
	private:
		float m_MouseX, m_MouseY;
	};

	//��������Ϣ
	class SAKURA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset),m_YOffset(yOffset){}//���캯��(���������� XY λ��)

		inline float GetXOffset() const { return m_XOffset; } //��ȡ������Xƫ��
		inline float GetYOffset() const { return m_YOffset; } //��ȡ������Yƫ��

		std::string ToString() const override //�����������Ϣ
		{
			std::stringstream ss;
			ss << "MouseX offset: " << m_XOffset << ", MouseY offset: " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//���ɻ�ȡ����Ϣ����ĺ���
		EVENT_CLASS_TYPE(EventType::MouseScrolled)//���� Type ��صĺ���
	private:
		float m_XOffset, m_YOffset;
	};

	//��갴����
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_MouseButton; }//��ȡ��갴��ֵ

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSEBUTTON)//���ɻ�ȡ�¼���������ķ���
	protected:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {}
		int m_MouseButton;//��갴��ֵ
	};

	//��갴������
	class SAKURA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "Mouse button: " << m_MouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	};

	//��갴���ɿ�
	class SAKURA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "Mouse button: " << m_MouseButton << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	};
}
