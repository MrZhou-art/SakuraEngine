#pragma once

#include "Event.h"


namespace Sakura
{
	//���ڴ�С�¼�
	class SAKURA_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window's width is: " << m_Width << ",window's height is: " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION)
		EVENT_CLASS_TYPE(EventType::WindowResize)
	private:
		int m_Width, m_Height;
	};

	//���ڹر��¼�
	class SAKURA_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::WindowClose)
	};

	//ÿ֡�¼�
	class SAKURA_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppTick)
	};

	//�����¼�
	class SAKURA_API AppUpdataEvent : public Event
	{
	public:
		AppUpdataEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppUpdata)
	};

	//��Ⱦ�¼�
	class SAKURA_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppRender)
	};
}