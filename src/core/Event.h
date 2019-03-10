#ifndef EVENT_H_
#define EVENT_H_

#include <functional>

namespace aurora
{
	// �¼�����,���,����
	// �������� ����,����,�ƶ�,����ʱ�ƶ�

	class Event
	{
	public:
		enum EventType
		{
			kKey,
			kMouse,
		};
		
		enum TriggerType
		{
			kRelease,	// �ɿ�
			kPress,		// ����
			kRepeat		// ��������
		};

		Event(EventType type) :type_(type) {  }
		virtual ~Event() = 0{}

		EventType type() { return type_; }
		
	protected:
		EventType type_;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent()
			:Event(Event::EventType::kKey)
		{

		}

		~KeyEvent()
		{

		}

		void SetTriggerCallback(Event::TriggerType type, const std::function<void()>& callback)
		{

		}
	private:
		std::function<void()> release_callback_;
		std::function<void()> press_callback_;
		std::function<void()> repeat_callback_;
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent()
			:Event(Event::EventType::kMouse)
		{

		}

		~MouseEvent()
		{

		}

		void SetTriggerCallback(Event::TriggerType type, const std::function<void(uint32_t x, uint32_t y)>& callback)
		{

		}
	private:
		std::function<void(uint32_t x, uint32_t y)> release_callback_;
		std::function<void(uint32_t x, uint32_t y)> press_callback_;
		std::function<void(uint32_t x, uint32_t y)> repeat_callback_;
		std::function<void(uint32_t x, uint32_t y)> move_callback_;
	};

	class MouseMoveEvent : public Event
	{

	};

	//EventManager::GetInstance()->AddEvent(event)
}

#endif
