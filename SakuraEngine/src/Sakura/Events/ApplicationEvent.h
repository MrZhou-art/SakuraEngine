#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//���ڴ�С�¼�
	class SAKURA_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: mWidth(width), mHeight(height) {}

		inline int getWidth() { return mWidth; }
		inline int getHeight() { return mHeight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window's width is: " << mWidth << ",window's height is: " << mHeight;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION)
		EVENT_CLASS_TYPE(EventType::WindowResize)
	private:
		int mWidth, mHeight;
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