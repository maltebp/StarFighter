#pragma once

#include <unordered_map>
#include <vector>

#include "River/Event/KeyEvent/KeyEventController.h"
#include "River/Error.h"
#include "River/Graphics/GL.h"
#include "River/Primitives/Color.h"


namespace River {

	class Window {
	public:

		Window(std::string title, unsigned int width, unsigned int height);
		~Window();

		void clear();
		void clearDepth();
		bool shouldClose();
		void close();
		unsigned int getNumTextureSlots();
		std::vector<KeyEvent> getKeyEvents();
		double getFps();
		void setClearColor(Color color);



	private:
		static std::unordered_map<GLFWwindow *, Window *> glfwWindowMap;
		static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void glfwMousePosCallback(GLFWwindow* window, double xpos, double ypos);
		static void glfwMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void glfwMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mode);

	private:

        GLFWwindow* glfwWindow;
        int width;
        int height;

		double mouseXTransform;
		double mouseYTransform;

        std::string title = "River Window";

		/* The number of texture slots (or units) accessible from the fragment shader */
		int numTextureSlots;

		
		double fps = 0;
		double previousFpsTime;
		unsigned int frameCount;

		Color clearColor;

		KeyEventController keyEventController;

	};
}


