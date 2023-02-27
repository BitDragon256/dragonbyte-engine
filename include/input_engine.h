#pragma once

#include <map>
#include <tuple>
#include <string>
#include <GLFW/glfw3.h>

namespace dragonbyte_engine
{
	class InputEngine
	{
	public:
		bool get_key(char key);
		void add_axis(std::string name, char keyUp, char keyDown);
		float get_axis(std::string name);
	private:
		void create(GLFWwindow* pWindow);
		void tick();
		
		friend class Overseer;

		static const int kHeldKeySize = 32;
		std::map<int, int> m_heldKeys; // map: key -> action
		std::map<std::string, std::tuple<float, char, char>> m_axes; // map: axis name -> axis value, key up, key down
#define AXIS_SNAPBACK 0.7
		
		void update_axes();
		void key_callback(int key, int action);
		static void s_key_callback_wrapper(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
		void create_default_axes();
	};

} // namespace dragonbyte_engine