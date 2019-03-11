#ifndef GLFW3_WINDOW_H_
#define GLFW3_WINDOW_H_

#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace aurora
{
	class GLFW3Window : public Window
	{
	public:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double x, double y);
		static void ScrollCallback(GLFWwindow* window, double x, double y);
		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

		GLFW3Window(const std::string& title_name,uint32_t width,uint32_t height);
		~GLFW3Window();

		bool Initialized() override;
		void Destory() override;

		void SwapBuffers() override;

		void PollEvents() override;
	private:
		GLFWwindow* window_;
	};
}

#endif
