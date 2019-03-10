#include "InputManager.h"

namespace aurora
{
	void InputManager::Reset()
	{
		for (auto iter = key_states_.begin(); iter != key_states_.end(); ++iter)
		{
			iter->second = INPUT_INVAlID;
		}

		for (auto iter = mouse_states_.begin(); iter != mouse_states_.end(); ++iter)
		{
			iter->second = INPUT_INVAlID;
		}
		
		scroll_offset_x_ = 0;
		scroll_offset_y_ = 0;
	}

	void InputManager::InputKey(uint32_t key, uint32_t state)
	{
		key_states_.emplace(key, state);
	}

	void InputManager::InputMouse(uint32_t mouse, uint32_t state)
	{
		mouse_states_.emplace(mouse, state);
	}

	void InputManager::InputScrollOffset(float offset_x, float offset_y)
	{
		scroll_offset_x_ = offset_x;
		scroll_offset_y_ = offset_y;
	}

	void InputManager::InputCursorPos(float x, float y)
	{
		cursor_pos_x_ = x;
		cursor_pos_y_ = y;
	}

	uint32_t InputManager::GetKey(uint32_t key)
	{
		auto iter = key_states_.find(key);
		if (iter == key_states_.end())
		{
			return INPUT_INVAlID;
		}
		return iter->second;
	}

	uint32_t InputManager::GetMouse(uint32_t mouse)
	{
		auto iter = mouse_states_.find(mouse);
		if (iter == mouse_states_.end())
		{
			return INPUT_INVAlID;
		}
		return iter->second;
	}
}