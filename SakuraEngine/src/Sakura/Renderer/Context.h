#pragma once

namespace Sakura
{
	class Context
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};

}