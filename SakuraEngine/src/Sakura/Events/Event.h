#pragma once
#include "sakuraPCH.h"
#include "Sakura/core.h"


namespace Sakura
{
	//Ŀǰ�����е��¼���������,һ��������Ϣ,���̴���
	//δ������ʹ���¼���������

	enum class EventType // ö���¼�����(ǿ����ö��:����ʹ��������ǰ׺,������ʽת��Ϊ������������ʽת��(static_cast))
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowMoved, 
		AppTick, AppUpdata, AppRender,
		KeyPressed, KeyReleased,KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory : int//ö���¼�����(��ͳö��:����ʹ��������ǰ׺,ö��ֵ����ʽת��Ϊ��������)
	{
		//ʹ�ö�����λ����,���ڶ���Ϣ���ദ��
		NONE						= 0,
		EVENTCATEGORY_APPLICATION	= BIT(0),
		EVENTCATEGORY_INPUT			= BIT(1),
		EVENTCATEGORY_KEYBOARD		= BIT(2),
		EVENTCATEGORY_MOUSE			= BIT(3),
		EVENTCATEGORY_MOUSEBUTTON	= BIT(4)
	};

//������¼�ϵͳʵ�ֵĹ���
	//##�����ճ�������������� EventType::������ type ���ӳ�������ö��ֵ
	//#���ַ�������������: ������� type ת��Ϊ�ַ�����������
	//������ͨ��Ԥ�������Զ������¼���Ĺؼ��ӿڣ������ظ�����.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName_C() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class SAKURA_API Event
	{
		friend class EventDispatcher;//��Ԫ�¼��ַ���,�����ȡ m_Handled
	public:
		virtual EventType GetEventType() const = 0;//��ȡ�¼�����
		virtual const char* GetName_C() const = 0;//��ȡchar���͵��¼�����
		virtual int GetCategoryFlags() const = 0;//��ȡ��ǰ�¼���������
		virtual std::string ToString() const { return GetName_C(); }//��ȡstring���͵��¼�����
		inline virtual bool GetHandled() const { return m_Handled; }//��ȡ�¼�����״̬

		inline bool IsInCategory(EventCategory category)//�ж�ʵ���Ƿ��ǵ�ǰ�¼�������
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;//�¼��Ƿ��ڴ���״̬
	};

	//�¼��ַ���(���ڽ��¼���̬���ɸ���Ӧ�Ĵ�����)
	//	������ ��̬���ͼ�� + ����ʱ����ƥ�� �Ĳ��ԣ�ʵ���˸�Ч�����Ͱ�ȫ���¼��������
	class EventDispatcher
	{
		/*
		* ����ģ��
		* using ����Ƕ�� ::type,֧��ģ������Ƶ����� C++ �� auto �ͷ����㷨������
		* std::function �� C++ ��׼���ṩ�Ķ�̬������װ�����ɴ洢�����ƺ͵��� *** �κοɵ��ö��� *** ��
		* bool(T&) ��ʾ����ǩ��������һ�� T& ���͵Ĳ������¼����ã������� bool ���͡�
		*/
		template<typename T>//ģ����������װ������������
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) 
			:m_Event(event){} //���캯��:����һ���¼�����
		
		template<typename T>
		bool Dispatch(EventFn<T> func) //���Խ��¼����ɸ��ض����͵Ĵ�����
		{
			if (m_Event.GetEventType() == T::GetStaticType()) //�����¼�����ƥ������ִ�ж�Ӧ�Ĵ����������ش�������
			{
				/*
				* ���ͼ�飺�Ƚϵ�ǰ�¼������ͣ�mEvent.GetEventType()���Ƿ���ģ����� T �ľ�̬���ͣ�T::GetStaticType()��һ�¡�
				* ����ת�������ƥ��ɹ����� Event& ǿ��ת��Ϊ T&�� *** ��ȫ������ת�ͣ���Ϊ������ȷ�� *** ����
				* ִ�д����������ô���Ĵ����� func��*** ������������bool������ m_Event.m_Handled *** ��
				* ���ؽ�������� true ��ʾ�¼��ѱ��������򷵻� false��
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
		return true; //���� true ��ʾ event ���ڴ����¼�״̬�����򷵻� false��
	});
	*/

	//�� Event ����ֱ�����������,������ʽ���� ToString() ����
	inline std::ostream& operator<<(std::ostream& os, const Event& e)//std::ostream �����������죬��˲����������������� std::ostream&
	{
		return os << e.ToString();
	}
}