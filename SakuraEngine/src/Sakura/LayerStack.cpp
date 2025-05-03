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
		for (Layer* layer : m_Layers)//*** LayerStack ����һ��Ҫ�� begin ���� ***
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		//��ͼ��ᱻ���뵽 m_LayerInsert ��������ָ���λ��֮ǰ
		//	��ˣ���� m_LayerInsert ���ָ�� layer1����ô���� layer1 Ӧ����������˳��layer3, layer2, layer1��
		m_Layers.emplace(m_LayerInsert, layer);
	}
	void LayerStack::PushOverLayer(Layer* overLayer)
	{
		//��ͼ��ᱻ��ӵ��б��ĩβ��
		//	��ˣ�ʹ��overlay1, overlay2, overlay3 �ֱ��ʾ����ĸ���ͼ��Ӧ����������˳��overlay1, overlay2, overlay3
		m_Layers.emplace_back(overLayer);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);//������ָ�������ɾ��֮��,������������һ��λ��
			/*
			* �ݼ������˼����
			*	��Ȼ Insert-- ȷʵ�Ὣָ��ָ����һ��Ԫ�أ���������ȫ������ɾ����Ԫ��һ���������루ջ��Ԫ�أ��Ļ����ϡ�
			*	���ɾ��ջ��Ԫ�أ�  Insert  ��ջ�����Ƶ���һ��Ԫ���ϣ���������һ��Ԫ�ؽ���ջ����λ�á�
			*	���� Insert-- ��ɾ������Ԫ��ʱ����ȫû����������ġ�
			* �ж�������˼����
			*	�Ǽ�Ȼ�Ѿ���������ˣ���Insert--��ֻ����ɾ���̶��ġ���ȷ�ġ�ջ��Ԫ�������ʹ����
			*	���ԣ���ǰ����ж����������Ϊ��ȷ����Ҫɾ����Ԫ�ش��� vector ��
			*	���������� std::find ȥѰ�ҳ�ջ�������Ԫ�ز�����ɾ����˼·�ˡ�
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