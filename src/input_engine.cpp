#include "input_engine.h"

#include "overseer.h"

namespace dragonbyte_engine
{

	void InputEngine::create(GLFWwindow* a_pWindow)
	{
		glfwSetKeyCallback(a_pWindow, s_key_callback_wrapper);
	}
	void InputEngine::tick()
	{
		
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

} // namespace dragonbyte_engine