#pragma once


#include "Camera.h"
#include "IncludeHeaders.h"
#include "Player.h"
#include "Level.h"

// Before Using Set the camera and the lastX lastY position of the mouse!
class EventHandler {
public:
    EventHandler(Player* player_, Level level_,  GLFWwindow* window_, float lastX, float lastY) :
        player(player_), 
        window(window_),
        level(level_),
        lastMouseX(lastX), 
        lastMouseY(lastY)
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
                player->move(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                player->move(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                player->move(STRAFELEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                player->move(STRAFERIGHT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                player->move(UPWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                player->move(DOWNWARD, deltaTime);

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

    void checkMovement(MoveDirection direction, float deltaTime) 
    {
        BoundaryBox box = player->getBoundaryBox();
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

        player->getCamera().ProcessMouseMovement(xoffset, yoffset);
    }

    float lastMouseX;
    float lastMouseY;
    GLFWwindow* window;
    Level level;
    Player* player;
};
