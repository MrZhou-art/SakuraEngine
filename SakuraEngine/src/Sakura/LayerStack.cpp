#include "sakuraPCH.h"

#include "LayerStack.h"

namespace Sakura
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)//*** LayerStack 类中一定要有 begin 函数 ***
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		//新图层会被插入到 m_LayerInsert 迭代器所指向的位置之前
		//	因此，如果 m_LayerInsert 最初指向 layer1，那么插入 layer1 应该是这样的顺序：layer3, layer2, layer1。
		m_Layers.emplace(m_LayerInsert, layer);
	}
	void LayerStack::PushOverLayer(Layer* overLayer)
	{
		//新图层会被添加到列表的末尾。
		//	因此，使用overlay1, overlay2, overlay3 分别表示推入的覆盖图层应该是这样的顺序：overlay1, overlay2, overlay3
		m_Layers.emplace_back(overLayer);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);//迭代器指向的内容删除之后,迭代器会向下一个位置
			/*
			* 递减的设计思考：
			*	虽然 Insert-- 确实会将指针指向下一个元素，但是这完全建立在删除的元素一定是最晚传入（栈顶元素）的基础上。
			*	如果删除栈顶元素，  Insert  由栈顶被移到下一个元素上，并且这下一个元素接替栈顶的位置。
			*	否则 Insert-- 在删除其他元素时是完全没有其他意义的。
			* 判断条件的思考：
			*	那既然已经这样设计了，那Insert--就只能在删除固定的、明确的、栈顶元素情况下使用了
			*	所以，这前面的判断条件便仅仅为了确保所要删除的元素存在 vector 中
			*	并不存在用 std::find 去寻找除栈顶以外的元素并将其删除的思路了。
			*/
			m_LayerInsert--;
		}
	}
	void LayerStack::PopOverLayer(Layer* overLayer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), overLayer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
		}
	}
}