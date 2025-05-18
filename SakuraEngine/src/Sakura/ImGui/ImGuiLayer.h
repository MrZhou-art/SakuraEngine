#pragma once

#include "Sakura/Layer/Layer.h"


#include "Sakura/Events/MouseEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/ApplicationEvent.h"


namespace Sakura
{
	class SAKURA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdata(Timestep ts) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}