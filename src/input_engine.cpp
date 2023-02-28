#include "input_engine.h"

#include "overseer.h"

namespace dragonbyte_engine
{

	void InputEngine::create(GLFWwindow* a_pWindow)
	{
		glfwSetKeyCallback(a_pWindow, s_key_callback_wrapper);

		create_default_axes();
	}
	void InputEngine::tick()
	{
		update_axes();
	}
	bool InputEngine::get_key(char key)
	{
		int keyCode = static_cast<int>(key);
		return m_heldKeys.count(keyCode) && m_heldKeys[keyCode] == GLFW_PRESS;
	}
	void InputEngine::key_callback(int a_key, int a_action)
	{
		if (a_action == GLFW_PRESS || a_action == GLFW_RELEASE)
			m_heldKeys[a_key] = a_action;
	}
	void InputEngine::s_key_callback_wrapper(GLFWwindow* a_pWindow, int a_key, int a_scancode, int a_action, int a_mods)
	{
		INPUT.key_callback(a_key, a_action);
	}
	void InputEngine::add_axis(std::string a_name, char a_keyUp, char a_keyDown)
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
	}

} // namespace dragonbyte_engine