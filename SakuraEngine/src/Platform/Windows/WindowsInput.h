#pragma once

#include "Sakura/Input/Input.h"
#include "Sakura/Application.h"

namespace Sakura
{
	class WindowsInput : public Input
	{
	protected:
		virtual inline bool IsKeyPressedImpl(int keyCode) override;
		virtual inline bool IsMousePressedImpl(int button)override;
		virtual std::pair<float, float> GetMousePositionImpl()override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl()override;
	};

}