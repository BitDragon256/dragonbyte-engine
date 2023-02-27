#pragma once

#include <map>
#include <GLFW/glfw3.h>

namespace dragonbyte_engine
{
	class InputEngine
	{
	public:
		bool get_key(char key);
	private:
		void create(GLFWwindow* pWindow);
		void tick();

		friend class Overseer;

		static const int kHeldKeySize = 32;
		std::map<int, int> m_heldKeys; // map: key -> action
		void key_callback(int key, int action);
		static void s_key_callback_wrapper(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
	};

} // namespace dragonbyte_engine