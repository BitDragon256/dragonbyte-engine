#pragma once

#include <map>
#include <tuple>
#include <string>
#include <GLFW/glfw3.h>

namespace dragonbyte_engine
{
	typedef unsigned short Key;

	typedef struct MousePos {
		double x;
		double y;
	} MousePos;
	class InputEngine
	{
	public:
		bool get_key(Key key);
		void add_axis(std::string name, Key keyUp, Key keyDown);
		float get_axis(std::string name);

		MousePos get_delta_mouse_pos();

	private:
		void create(GLFWwindow* pWindow);
		void tick();
		
		friend class Overseer;

		static const int kHeldKeySize = 32;
		std::map<int, int> m_heldKeys; // map: key -> action
		std::map<std::string, std::tuple<float, Key, Key>> m_axes; // map: axis name -> axis value, key up, key down

		void calc_delta_mouse_pos();
		MousePos m_mousePos;
		MousePos m_lastMousePos;
		MousePos m_mousePosDelta;

#define AXIS_SNAPBACK 0.7
		
		void update_axes();
		void key_callback(int key, int action);
		void cursor_position_callback(double xpos, double ypos);
		static void s_key_callback_wrapper(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
		static void s_cursor_position_callback_wrapper(GLFWwindow* pWindow, double xpos, double ypos);
		void create_default_axes();
	};

} // namespace dragonbyte_engine