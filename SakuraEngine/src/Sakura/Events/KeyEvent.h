#pragma once

#include "Event.h"


namespace Sakura
{
	//键盘事件类(抽象类,作为键按下事件和键松开事件的基类)
	class KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }//获取键盘按键码值

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_KEYBOARD | EVENTCATEGORY_INPUT);//生成获取当前事件种类掩码的方法

	protected:
		KeyEvent(int keyCode) 
			: m_KeyCode(keyCode) {}//有参构造器(设置键盘码值)

		int m_KeyCode;//键盘码值
	};

	//键按下事件
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount){}//有参构造器(设置键盘码值,按下计数)

		inline int GetRepeatCount() const { return m_RepeatCount; }//获取按下计数
		
		std::string ToString() const override//输出键盘消息
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)//生成 Type 有关的函数
	private:
		int m_RepeatCount;//按下计数
	};

	//键松开事件
	class SAKURA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode){}//有参构造器(设置键盘码值)

		std::string ToString() const override//输出键盘消息
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode <<  " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)//生成 Type 有关的函数
	private:
	};

	//键盘类型事件
	class SAKURA_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}//有参构造器(设置键盘码值)

		std::string ToString() const override//输出键盘消息
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyTyped)//生成 Type 有关的函数
	private:
	};
}