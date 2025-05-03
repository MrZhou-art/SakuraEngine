#pragma once

#include "Event.h"


namespace Sakura
{
	//�����¼���(������,��Ϊ�������¼��ͼ��ɿ��¼��Ļ���)
	class KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }//��ȡ���̰�����ֵ

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_KEYBOARD | EVENTCATEGORY_INPUT);//���ɻ�ȡ��ǰ�¼���������ķ���

	protected:
		KeyEvent(int keyCode) 
			: m_KeyCode(keyCode) {}//�вι�����(���ü�����ֵ)

		int m_KeyCode;//������ֵ
	};

	//�������¼�
	class SAKURA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount){}//�вι�����(���ü�����ֵ,���¼���)

		inline int GetRepeatCount() const { return m_RepeatCount; }//��ȡ���¼���
		
		std::string ToString() const override//���������Ϣ
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)//���� Type �йصĺ���
	private:
		int m_RepeatCount;//���¼���
	};

	//���ɿ��¼�
	class SAKURA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode){}//�вι�����(���ü�����ֵ)

		std::string ToString() const override//���������Ϣ
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode <<  " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)//���� Type �йصĺ���
	private:
	};

	//���������¼�
	class SAKURA_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}//�вι�����(���ü�����ֵ)

		std::string ToString() const override//���������Ϣ
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode << " is released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyTyped)//���� Type �йصĺ���
	private:
	};
}