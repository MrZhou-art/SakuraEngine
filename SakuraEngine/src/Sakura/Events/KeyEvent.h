#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//�����¼���(������,��Ϊ�������¼��ͼ��ɿ��¼��Ļ���)
	class KeyEvent : public Event 
	{
	public:
		inline int getKeyCode() const { return mKeyCode; }//��ȡ���̰�����ֵ

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_KEYBOARD | EVENTCATEGORY_INPUT);//���ɻ�ȡ��ǰ�¼���������ķ���

	protected:
		KeyEvent(int keyCode) 
			: mKeyCode(keyCode) {}//�вι�����(���ü�����ֵ)

		int mKeyCode;//������ֵ
	};

	//�������¼�
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), mRepeatCount(repeatCount){}//�вι�����(���ü�����ֵ,���¼���)

		inline int getRepeatCount() const { return mRepeatCount; }//��ȡ���¼���
		
		std::string ToString() const override//���������Ϣ
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << "(" << mRepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)//���� Type �йصĺ���
	private:
		int mRepeatCount;//���¼���
	};

	//���ɿ��¼�
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode)
			: KeyEvent(keyCode){}//�вι�����(���ü�����ֵ)

		std::string ToString() const override//���������Ϣ
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode <<  " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)//���� Type �йصĺ���
	private:
	};
}