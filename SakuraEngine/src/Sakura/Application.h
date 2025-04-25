#pragma once

#include "core.h"

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
