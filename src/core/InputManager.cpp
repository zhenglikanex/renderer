#include "InputManager.h"

namespace aurora
{
	void InputManager::Update()
	{
		// Repeat和Press有延迟,这里做点处理?
		for (auto& key_state : key_states_)
		{
			if (key_state.second == InputState::kPress)
			{
				key_state.second = InputState::kRepeat;
			}
			else if(key_state.second == InputState::kRelease)
			{
				key_state.second = InputState::kNone;
			}
		}
	}

	void InputManager::Reset()
	{
		for (auto iter = key_states_.begin(); iter != key_states_.end(); ++iter)
		{
			iter->second = InputState::kNone;
		}

		for (auto iter = mouse_states_.begin(); iter != mouse_states_.end(); ++iter)
		{
			iter->second = InputState::kNone;
		}
		
		scroll_offset_x_ = 0;
		scroll_offset_y_ = 0;
	}

	void InputManager::InputKey(uint32_t key, InputState state)
	{
		auto iter = key_states_.find(key);
		if (iter != key_states_.end())
		{
			iter->second = state;
		}
		else 
		{
			key_states_.emplace(key, state);
		}
	}

	void InputManager::InputMouse(uint32_t mouse, InputState state)
	{
		mouse_states_.emplace(mouse, state);
		auto iter = mouse_states_.find(mouse);
		if (iter != mouse_states_.end())
		{
			iter->second = state;
		}
		else
		{
			mouse_states_.emplace(mouse, state);
		}
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

	InputState InputManager::GetKey(uint32_t key)
	{
		auto iter = key_states_.find(key);
		if (iter == key_states_.end())
		{
			return InputState::kNone;
		}
		return iter->second;
	}

	InputState InputManager::GetMouse(uint32_t mouse)
	{
		auto iter = mouse_states_.find(mouse);
		if (iter == mouse_states_.end())
		{
			return InputState::kNone;
		}
		return iter->second;
	}
}