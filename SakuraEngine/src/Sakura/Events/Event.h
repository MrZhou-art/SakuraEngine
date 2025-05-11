#pragma once
#include "sakuraPCH.h"
#include "Sakura/core.h"


namespace Sakura
{
	//目前引擎中的事件是阻塞的,一旦接受消息,立刻处理
	//未来可以使用事件缓冲区域

	enum class EventType // 枚举事件类型(强类型枚举:必须使用作用域前缀,不可隐式转换为整数，必须显式转换(static_cast))
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowMoved, 
		AppTick, AppUpdata, AppRender,
		KeyPressed, KeyReleased,KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory : int//枚举事件种类(传统枚举:无须使用作用域前缀,枚举值可隐式转换为整数类型)
	{
		//使用二进制位掩码,便于对消息分类处理
		NONE						= 0,
		EVENTCATEGORY_APPLICATION	= BIT(0),
		EVENTCATEGORY_INPUT			= BIT(1),
		EVENTCATEGORY_KEYBOARD		= BIT(2),
		EVENTCATEGORY_MOUSE			= BIT(3),
		EVENTCATEGORY_MOUSEBUTTON	= BIT(4)
	};

//定义简化事件系统实现的工具
	//##（标记粘贴操作符）：将 EventType::与宏参数 type 连接成完整的枚举值
	//#（字符串化操作符）: 将宏参数 type 转换为字符串字面量。
	//其子类通过预处理器自动生成事件类的关键接口，减少重复代码.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName_C() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class SAKURA_API Event
	{
		friend class EventDispatcher;//友元事件分发器,让其获取 m_Handled
	public:
		virtual EventType GetEventType() const = 0;//获取事件类型
		virtual const char* GetName_C() const = 0;//获取char类型的事件名字
		virtual int GetCategoryFlags() const = 0;//获取当前事件种类掩码
		virtual std::string ToString() const { return GetName_C(); }//获取string类型的事件名字
		inline virtual bool GetHandled() const { return m_Handled; }//获取事件处理状态

		inline bool IsInCategory(EventCategory category)//判断实参是否是当前事件的种类
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;//事件是否处于处理状态
	};

	//事件分发器(用于将事件动态分派给对应的处理函数)
	//	采用了 静态类型检查 + 运行时类型匹配 的策略，实现了高效且类型安全的事件处理机制
	class EventDispatcher
	{
		/*
		* 别名模板
		* using 无需嵌套 ::type,支持模板参数推导，与 C++ 的 auto 和泛型算法更兼容
		* std::function 是 C++ 标准库提供的多态函数包装器，可存储、复制和调用 *** 任何可调用对象 *** 。
		* bool(T&) 表示函数签名：接受一个 T& 类型的参数（事件引用），返回 bool 类型。
		*/
		template<typename T>//模板参数代表包装函数参数类型
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) 
			:m_Event(event){} //构造函数:接收一个事件对象
		
		template<typename T>
		bool Dispatch(EventFn<T> func) //尝试将事件分派给特定类型的处理函数
		{
			if (m_Event.GetEventType() == T::GetStaticType()) //根据事件类型匹配结果，执行对应的处理函数并返回处理结果。
			{
				/*
				* 类型检查：比较当前事件的类型（mEvent.GetEventType()）是否与模板参数 T 的静态类型（T::GetStaticType()）一致。
				* 类型转换：如果匹配成功，将 Event& 强制转换为 T&（ *** 安全的向下转型，因为类型已确认 *** ）。
				* 执行处理函数：调用传入的处理函数 func，*** 并将处理结果（bool）存入 m_Event.m_Handled *** 。
				* 返回结果：返回 true 表示事件已被处理，否则返回 false。
				*/
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	/*
	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) 
	{
		if (e.GetKeyCode() == KEY_W) {
			player.MoveForward();
		}
		return true; //返回 true 表示 event 处于处理事件状态，否则返回 false。
	});
	*/

	//将 Event 对象直接输出到流中,无需显式调用 ToString() 方法
	inline std::ostream& operator<<(std::ostream& os, const Event& e)//std::ostream 不允许拷贝构造，因此参数必须是引用类型 std::ostream&
	{
		return os << e.ToString();
	}
}