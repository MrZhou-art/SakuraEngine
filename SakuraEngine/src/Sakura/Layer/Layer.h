#pragma once

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	class SAKURA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		/*
		* OnUpdate() 执行逻辑更新
		* 通常情况下，OnUpdate() 函数用于更新应用程序的逻辑状态。
		* 例如更新对象的位置、处理输入事件、执行物理模拟等等。这个过程在每一帧都会执行，以确保实时修正逻辑操作内容。
		* 
		* OnImGuiRender() 执行渲染
		* 得到正确的逻辑状态，进行内容的最新渲染结果。
		*/

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdata() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetLayerName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
	};
}