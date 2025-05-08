#pragma once

#include "Sakura/core.h"
#include "Layer.h"

namespace Sakura
{
	class SAKURA_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		//普通层由迭代器维护,覆盖层作为栈使用
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* overLayer);
		void PopLayer(Layer* layer);
		void PopOverLayer(Layer* overLayer);

		inline std::vector<Layer*>::iterator begin()	{ return m_Layers.begin(); }//获取栈顶迭代器(作为接口,在 for 循环中使用)
		inline std::vector<Layer*>::iterator end()		{ return m_Layers.end(); }	//获取栈底迭代器
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;//迭代器,指向容器普通层顶部的元素
	};
}