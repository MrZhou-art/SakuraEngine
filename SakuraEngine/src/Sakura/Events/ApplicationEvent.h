#pragma once

#include "Event.h"

#include <sstream>

namespace Sakura
{
	//窗口大小事件
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

	//窗口关闭事件
	class SAKURA_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::WindowClose)
	};

	//每帧事件
	class SAKURA_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppTick)
	};

	//更新事件
	class SAKURA_API AppUpdataEvent : public Event
	{
	public:
		AppUpdataEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppUpdata)
	};

	//渲染事件
	class SAKURA_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_CATEGORY(EVENTCATEGORY_INPUT | EVENTCATEGORY_APPLICATION);
		EVENT_CLASS_TYPE(EventType::AppRender)
	};
}