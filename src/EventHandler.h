#pragma once


#include "Camera.h"
#include "IncludeHeaders.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Level.h"

// Before Using Set the camera and the lastX lastY position of the mouse!
class EventHandler {
public:
    EventHandler(Player* player_, const Level * level_,  GLFWwindow* window_, float lastX, float lastY) :
        player(player_), 
        window(window_),
        level(level_),
        lastMouseX(lastX), 
        lastMouseY(lastY),
        cursorEnabled(false)
    {

    }

public:
    void handleEvents(float deltaTime) {
        processInput(deltaTime);
        if (!cursorEnabled)
        {
            mouse_callback();
        }
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
            Player dummy_player = player->getCopy();
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                deltaTime *= 2.0f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                dummy_player.move(FORWARD, deltaTime);
                if (!checkMovement(dummy_player)) 
                {
                    player->move(FORWARD, deltaTime);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                dummy_player.move(BACKWARD, deltaTime);
                if (!checkMovement(dummy_player))
                {
                    player->move(BACKWARD, deltaTime);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                dummy_player.move(STRAFELEFT, deltaTime);
                if(!checkMovement(dummy_player))
                {
                    player->move(STRAFELEFT, deltaTime);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                dummy_player.move(STRAFERIGHT, deltaTime);
                if (!checkMovement(dummy_player))
                {
                    player->move(STRAFERIGHT, deltaTime);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                dummy_player.move(UPWARD, deltaTime);
                if (!checkMovement(dummy_player))
                {
                    player->move(UPWARD, deltaTime);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            {
                dummy_player.move(DOWNWARD, deltaTime);
                if (!checkMovement(dummy_player))
                {
                    player->move(DOWNWARD, deltaTime);
                }
            }

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

            // enables cursor

            static int oldState = GLFW_RELEASE;
            int newState = glfwGetKey(window, GLFW_KEY_C);
            if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
                if (!cursorEnabled)
                {
                    cursorEnabled = true;
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    int display_w, display_h;
                    glfwGetFramebufferSize(window, &display_w, &display_h);
                    glfwSetCursorPos(window, display_w / 2, display_h / 2);
                }
                else
                {
                    cursorEnabled = false;
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    glfwSetCursorPos(window, lastMouseX, lastMouseY);
                }
            }
            oldState = newState;
        }

    }

    bool checkMovement(Player dummy_player) const
    {
        const std::map<std::string /* object ID */, Object> objects = level->getObjects();
        for (auto const& it : objects)
        {
            if (CollisionHandler::check_collision(dummy_player, it.second))
            {
                return true;
            }
        }
        return false;
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
    const Level * level;
    Player* player;
    bool cursorEnabled;
};
