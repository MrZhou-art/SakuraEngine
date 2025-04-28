#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//键盘事件类(抽象类,作为键按下事件和键松开事件的基类)
	class KeyEvent : public Event 
	{
	public:
		inline int getKeyCode() const { return mKeyCode; }//获取键盘按键码值

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_KEYBOARD | EVENTCATEGORY_INPUT);//生成获取当前事件种类掩码的方法

	protected:
		KeyEvent(int keyCode) 
			: mKeyCode(keyCode) {}//有参构造器(设置键盘码值)

		int mKeyCode;//键盘码值
	};

	//键按下事件
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), mRepeatCount(repeatCount){}//有参构造器(设置键盘码值,按下计数)

		inline int getRepeatCount() const { return mRepeatCount; }//获取按下计数
		
		std::string ToString() const override//输出键盘消息
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << "(" << mRepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)//生成 Type 有关的函数
	private:
		int mRepeatCount;//按下计数
	};

	//键松开事件
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode)
			: KeyEvent(keyCode){}//有参构造器(设置键盘码值)

		std::string ToString() const override//输出键盘消息
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode <<  " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)//生成 Type 有关的函数
	private:
	};
}