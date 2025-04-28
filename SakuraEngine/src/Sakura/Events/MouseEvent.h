#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//鼠标位置消息
	class SAKURA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) //构造函数(传入鼠标 XY 位置)
			: mMouseX(x), mMouseY(y) {}

		inline float getMouseX() const { return mMouseX; } //获取鼠标 X 位置
		inline float getMouseY() const { return mMouseY; } //获取鼠标 Y 位置

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "MouseX: " << mMouseX << ", MouseY: " << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//生成获取该消息种类的函数
		EVENT_CLASS_TYPE(EventType::MouseMoved)//生成 Type 相关的函数
	private:
		float mMouseX, mMouseY;
	};

	//鼠标滚轮消息
	class SAKURA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: mXOffset(xOffset),mYOffset(yOffset){}//构造函数(传入鼠标滚轮 XY 位置)

		inline float getXOffset() const { return mXOffset; } //获取鼠标滚轮X偏移
		inline float getYOffset() const { return mYOffset; } //获取鼠标滚轮Y偏移

		std::string ToString() const override //输出鼠标滚轮信息
		{
			std::stringstream ss;
			ss << "MouseX offset: " << mXOffset << ", MouseY offset: " << mYOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSE)//生成获取该消息种类的函数
		EVENT_CLASS_TYPE(EventType::MouseScrolled)//生成 Type 相关的函数
	private:
		float mXOffset, mYOffset;
	};

	//鼠标按键类
	class MouseButton : public Event
	{
	public:
		inline int getMouseButton() const { return mMouseButton; }//获取鼠标按键值

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_MOUSEBUTTON)//生成获取事件种类掩码的方法
	protected:
		MouseButton(int mouseButton)
			: mMouseButton(mouseButton) {}
		int mMouseButton;//鼠标按键值
	};

	//鼠标按键按下
	class SAKURA_API MouseButtonPressed : public MouseButton
	{
	public:
		MouseButtonPressed(int mouseButton)
			: MouseButton(mouseButton) {}

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "Mousebutton: " << mMouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	private:
	};

	//鼠标按键松开
	class SAKURA_API MouseButtonReleased : public MouseButton
	{
	public:
		MouseButtonReleased(int mouseButton)
			: MouseButton(mouseButton) {}

		std::string ToString() const override //输出鼠标信息
		{
			std::stringstream ss;
			ss << "Mousebutton: " << mMouseButton << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	private:
	};
}
