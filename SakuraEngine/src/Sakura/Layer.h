#pragma once

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	class SAKURA_API Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdata() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetLayerName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
	};
}