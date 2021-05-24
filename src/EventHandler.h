#pragma once


#include "Camera.h"
#include "IncludeHeaders.h"

// Before Using Set the camera and the lastX lastY position of the mouse!
static class EventHandler {
public:
    EventHandler(Camera* camera_, GLFWwindow* window_, float lastX, float lastY) : camera(camera_), window(window_), lastMouseX(lastX), lastMouseY(lastY)
    {

    }

public:
    void handleEvents(float deltaTime) {
        processInput(deltaTime);
        mouse_callback();
    }


    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }


private:
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
    void processInput(float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        else
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                deltaTime *= 2.0f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera->ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera->ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera->ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera->ProcessKeyboard(RIGHT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                camera->ProcessKeyboard(UPWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                camera->ProcessKeyboard(DOWNWARD, deltaTime);

            // switch polygon mode to LINE
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }

            // switch polygon mode to FILL
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

    }

    void mouse_callback()
    {
        double xpos;
        double ypos;

        // gets mouse x and y positions
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = (float)(lastMouseX - xpos);
        float yoffset = (float)(lastMouseY - ypos); // reversed since y-coordinates range from bottom to top
        lastMouseX = (float)xpos;
        lastMouseY = (float)ypos;

        //const float sensitivity = 0.1f;
        //xoffset *= sensitivity;
        //yoffset *= sensitivity;
        //std::cout << "X: " << lastMouseX << "\t" << "Y: " << lastMouseY << std::endl;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }

    float lastMouseX;
    float lastMouseY;
    GLFWwindow* window;
    Camera* camera;
};
