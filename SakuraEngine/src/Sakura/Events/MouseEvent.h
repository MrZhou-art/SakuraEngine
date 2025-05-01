#pragma once

#include "Event.h"

namespace Sakura
{
	//鼠标位置消息
	class SAKURA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) //构造函数(传入鼠标 XY 位置)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetMouseX() const { return m_MouseX; } //获取鼠标 X 位置
		inline float GetMouseY() const { return m_MouseY; } //获取鼠标 Y 位置

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "MouseX: " << m_MouseX << ", MouseY: " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//生成获取该消息种类的函数
		EVENT_CLASS_TYPE(EventType::MouseMoved)//生成 Type 相关的函数
	private:
		float m_MouseX, m_MouseY;
	};

	//鼠标滚轮消息
	class SAKURA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset),m_YOffset(yOffset){}//构造函数(传入鼠标滚轮 XY 位置)

		inline float GetXOffset() const { return m_XOffset; } //获取鼠标滚轮X偏移
		inline float GetYOffset() const { return m_YOffset; } //获取鼠标滚轮Y偏移

		std::string ToString() const override //输出鼠标滚轮信息
		{
			std::stringstream ss;
			ss << "MouseX offset: " << m_XOffset << ", MouseY offset: " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//生成获取该消息种类的函数
		EVENT_CLASS_TYPE(EventType::MouseScrolled)//生成 Type 相关的函数
	private:
		float m_XOffset, m_YOffset;
	};

	//鼠标按键类
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_MouseButton; }//获取鼠标按键值

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSEBUTTON)//生成获取事件种类掩码的方法
	protected:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {}
		int m_MouseButton;//鼠标按键值
	};

	//鼠标按键按下
	class SAKURA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "Mouse button: " << m_MouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	};

	//鼠标按键松开
	class SAKURA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "Mouse button: " << m_MouseButton << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	};
}
