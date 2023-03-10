#include "input_engine.h"

#include "overseer.h"

namespace dragonbyte_engine
{

	void InputEngine::create(GLFWwindow* a_pWindow)
	{
		glfwSetKeyCallback(a_pWindow, s_key_callback_wrapper);
		glfwSetCursorPosCallback(a_pWindow, s_cursor_position_callback_wrapper);

		glfwSetInputMode(a_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		create_default_axes();
	}
	void InputEngine::tick()
	{
		update_axes();

		calc_delta_mouse_pos();
	}
	bool InputEngine::get_key(Key key)
	{
		int keyCode = static_cast<int>(key);
		return m_heldKeys.count(keyCode) && m_heldKeys[keyCode] == GLFW_PRESS;
	}
	void InputEngine::calc_delta_mouse_pos()
	{
		m_mousePosDelta = { m_lastMousePos.x - m_mousePos.x, m_lastMousePos.y - m_mousePos.y };
		m_lastMousePos = { std::lerp(m_lastMousePos.x, m_mousePos.x, 0.8f), std::lerp(m_lastMousePos.y, m_mousePos.y, 0.8f) };
	}
	void InputEngine::key_callback(int a_key, int a_action)
	{
		if (a_action == GLFW_PRESS || a_action == GLFW_RELEASE)
			m_heldKeys[a_key] = a_action;
	}
	void InputEngine::cursor_position_callback(double a_xpos, double a_ypos)
	{
		m_mousePos = { a_xpos, a_ypos };
	}
	void InputEngine::s_key_callback_wrapper(GLFWwindow* a_pWindow, int a_key, int a_scancode, int a_action, int a_mods)
	{
		INPUT.key_callback(a_key, a_action);
	}
	void InputEngine::s_cursor_position_callback_wrapper(GLFWwindow* a_pWindow, double a_xpos, double a_ypos)
	{
		INPUT.cursor_position_callback(a_xpos, a_ypos);
	}
	void InputEngine::add_axis(std::string a_name, Key a_keyUp, Key a_keyDown)
	{
		m_axes[a_name] = std::make_tuple(0, a_keyUp, a_keyDown);
	}
	float InputEngine::get_axis(std::string a_name)
	{
		return std::get<0>(m_axes[a_name]);
	}
	void InputEngine::update_axes()
	{
		for (auto& [name, tuple] : m_axes)
		{
			auto& [value, keyUp, keyDown] = tuple;
			float dst = 0.f;
			if (get_key(keyUp))
				dst += 1.f;
			if (get_key(keyDown))
				dst -= 1.f;
			value = static_cast<float>(std::lerp(value, dst, AXIS_SNAPBACK));
		}
	}
	void InputEngine::create_default_axes()
	{
		add_axis("Horizontal", 'D', 'A');
		add_axis("Vertical", 'W', 'S');
		add_axis("FlyControl", 'E', 'Q');
		add_axis("ArrowVertical", GLFW_KEY_UP, GLFW_KEY_DOWN);
		add_axis("ArrowHorizontal", GLFW_KEY_RIGHT, GLFW_KEY_LEFT);
	}
	MousePos InputEngine::get_delta_mouse_pos()
	{
		return m_mousePosDelta;
	}

} // namespace dragonbyte_engine