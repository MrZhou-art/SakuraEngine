#pragma once

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* createApplication();
}
