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

		//��ͨ���ɵ�����ά��,���ǲ���Ϊջʹ��
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* overLayer);
		void PopLayer(Layer* layer);
		void PopOverLayer(Layer* overLayer);

		inline std::vector<Layer*>::iterator begin()	{ return m_Layers.begin(); }//��ȡջ��������(��Ϊ�ӿ�,�� for ѭ����ʹ��)
		inline std::vector<Layer*>::iterator end()		{ return m_Layers.end(); }	//��ȡջ�׵�����
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;//������,ָ��������ͨ�㶥����Ԫ��
	};
}