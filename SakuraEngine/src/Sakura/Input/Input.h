#pragma once

namespace Sakura
{

	class SAKURA_API Input
	{
	public:
		static inline bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		static inline bool IsMousePressed(int button) { return s_Instance->IsMousePressedImpl(button); }
		static inline std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static inline float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMousePressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}