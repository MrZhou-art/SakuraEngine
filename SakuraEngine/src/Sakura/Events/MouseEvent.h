#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//���λ����Ϣ
	class SAKURA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) //���캯��(������� XY λ��)
			: mMouseX(x), mMouseY(y) {}

		inline float getMouseX() const { return mMouseX; } //��ȡ��� X λ��
		inline float getMouseY() const { return mMouseY; } //��ȡ��� Y λ��

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "MouseX: " << mMouseX << ", MouseY: " << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//���ɻ�ȡ����Ϣ����ĺ���
		EVENT_CLASS_TYPE(EventType::MouseMoved)//���� Type ��صĺ���
	private:
		float mMouseX, mMouseY;
	};

	//��������Ϣ
	class SAKURA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: mXOffset(xOffset),mYOffset(yOffset){}//���캯��(���������� XY λ��)

		inline float getXOffset() const { return mXOffset; } //��ȡ������Xƫ��
		inline float getYOffset() const { return mYOffset; } //��ȡ������Yƫ��

		std::string ToString() const override //�����������Ϣ
		{
			std::stringstream ss;
			ss << "MouseX offset: " << mXOffset << ", MouseY offset: " << mYOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//���ɻ�ȡ����Ϣ����ĺ���
		EVENT_CLASS_TYPE(EventType::MouseScrolled)//���� Type ��صĺ���
	private:
		float mXOffset, mYOffset;
	};

	//��갴����
	class MouseButton : public Event
	{
	public:
		inline int getMouseButton() const { return mMouseButton; }//��ȡ��갴��ֵ

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSEBUTTON)//���ɻ�ȡ�¼���������ķ���
	protected:
		MouseButton(int mouseButton)
			: mMouseButton(mouseButton) {}
		int mMouseButton;//��갴��ֵ
	};

	//��갴������
	class SAKURA_API MouseButtonPressed : public MouseButton
	{
	public:
		MouseButtonPressed(int mouseButton)
			: MouseButton(mouseButton) {}

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "Mousebutton: " << mMouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	private:
	};

	//��갴���ɿ�
	class SAKURA_API MouseButtonReleased : public MouseButton
	{
	public:
		MouseButtonReleased(int mouseButton)
			: MouseButton(mouseButton) {}

		std::string ToString() const override //��������Ϣ
		{
			std::stringstream ss;
			ss << "Mousebutton: " << mMouseButton << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	private:
	};
}
