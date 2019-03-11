#include "GLFW3Window.hpp"

#include "LogManager.h"
#include "Context.h"
#include "Renderer.h"
#include "DeviceContext.h"
#include "InputManager.h"

namespace aurora
{
	void GLFW3Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputManager::GetInstance()->InputKey(key, action);
	}

	void GLFW3Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		InputManager::GetInstance()->InputMouse(button, action);
	}
	void GLFW3Window::CursorPositionCallback(GLFWwindow* window, double x, double y)
	{
		auto cur_window = Context::GetInstance()->renderer()->device_context()->window();
		auto width = cur_window->width();
		auto height = cur_window->height();

		//InputManager::GetInstance()->InputCursorPos(float((x - width / 2) / width) * 2, float(0 - (y - height / 2) / height) * 2);
		LOG_INFO() << "MOUSE_X:" << x << "MOUSE_Y" << y << LOG_END();
	}
	void GLFW3Window::ScrollCallback(GLFWwindow* window, double x, double y)
	{
		InputManager::GetInstance()->InputScrollOffset(x, y);
	}

	void GLFW3Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto cur_window = Context::GetInstance()->renderer()->device_context()->window();
		cur_window->set_width(width);
		cur_window->set_height(height);

		Context::GetInstance()->renderer()->ChangeViewprot(0, 0, width, height);
	}

	GLFW3Window::GLFW3Window(const std::string& title_name, uint32_t width, uint32_t height)
		:Window(title_name,width,height)
	{

	}

	GLFW3Window::~GLFW3Window()
	{
		std::cout << "GLFW3Window::~GLFW3Window()" << std::endl;
		Destory();
	}

	bool GLFW3Window::Initialized()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
		window_ = glfwCreateWindow(width_, height_, title_name_.c_str(), nullptr, nullptr);
		if (window_ == nullptr)
		{
			LOG_ERROR() << "GLFW3Window 窗口创建失败!" << LOG_END();
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window_);

		// 注册输入事件
		glfwSetKeyCallback(window_, &GLFW3Window::KeyCallback);
		glfwSetMouseButtonCallback(window_, &GLFW3Window::MouseButtonCallback);
		glfwSetCursorPosCallback(window_, &GLFW3Window::CursorPositionCallback);
		glfwSetScrollCallback(window_, &GLFW3Window::ScrollCallback);
		glfwSetFramebufferSizeCallback(window_, &GLFW3Window::FrameBufferSizeCallback);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR() << "glad 初始化失败!" << LOG_END();
			return false;
		}

		return true;
	}

	void GLFW3Window::Destory()
	{
		glfwTerminate();
		window_ = nullptr;
	}

	void GLFW3Window::SwapBuffers()
	{
		glfwSwapBuffers(window_);
	}

	void GLFW3Window::PollEvents()
	{
		if (glfwWindowShouldClose(window_))
		{
			// 退出程序
			Context::GetInstance()->Quit();
		}

		glfwPollEvents();
	}
}

