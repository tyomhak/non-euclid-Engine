#pragma once


#include "Camera.h"
#include "IncludeHeaders.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Level.h"
#include "Portal.h"

// Before Using Set the camera and the lastX lastY position of the mouse!
class EventHandler {
public:
    EventHandler()
    {}

    EventHandler(Player* player_, Level * level_,  GLFWwindow* window_, float lastX, float lastY, Shader *objShader, Shader *portShader) :
        player(player_), 
        window(window_),
        level(level_),
        lastMouseX(lastX), 
        lastMouseY(lastY),
        cursorEnabled(false),
        creativeEnabled(false),
        objectShader(objShader),
        portalShader(portShader)
    {
    }

public:
    void handleEvents(float deltaTime) {
        // handle keyboard
        processInput(deltaTime);

        // handle mouse
        if (!cursorEnabled){    mouse_callback();   }
        //std::cout << selectedObjectId << std::endl;
        if (creativeEnabled)
        {
            castRay();
        }
    }

    void moveSelectedObjectToPosition(glm::vec3 position)
    {
        if (underViewObjectId == "None")
        {
            return;
        }
        level->getObjectPointer(underViewObjectId)->SetPosition(position);
    }

    void moveCreateObjectToPosition(glm::vec3 position)
    {
        if (updateObjectId == "None")
        {
            return;
        }
        level->getObjectPointer(updateObjectId)->SetPosition(position);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void saveObject()
    {
        creativeEnabled = false;
        underViewObjectId = "None";
        updateObjectId = "None";
    }

    void selectObject()
    {
        if (underViewObjectId == "None")
        {
            return;
        }
        updateObjectId = underViewObjectId;
    }

    void deleteObject()
    {
        level->deleteObject(underViewObjectId);
    }

    // add the object into the level and return the id of created object
    string addObject(string name, glm::vec3 Position)
    {
        return level->AddObject(name, Position);
    }

    void addPortals()
    {
        Ray ray(&player->getCamera(), window);
        glm::vec3 locationFirst = ray.getOrigin() + (minDistance + 1.0f) * ray.getDirection();
        glm::vec3 locationSecond = ray.getOrigin() + (minDistance + 3.0f) * ray.getDirection();
        // portals pair creation
        level->AddPortalPair(locationFirst, locationSecond);
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
                    player->move(UPWARD, deltaTime * 2);
                }
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            //if (true)
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

            // make distance longer
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                distance += deltaTime * 5;
            }

            // make distance shorter
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                if (distance >= minDistance)
                {
                    distance -= deltaTime * 5;
                }
            }

            // place Object
            if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            {
                saveObject();
            }

            if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            {
                LevelHandler::WriteLevel("temp_level", *level, player->getCamera());
            }

            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            {
                Level newLevel = LevelHandler::ReadLevel("temp_level.lev", player->getCamera(), *portalShader, *objectShader);
                *level = newLevel;
            }

            if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
            {
                for (auto &port : level->getPortals())
                {
                    // port.second.RotateHorizontal(45.0f);
                    port.second.Scale(1.05);
                }
            }


            if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
            {
                for (auto &port : level->getPortals())
                {
                    // port.second.RotateHorizontal(45.0f);
                    port.second.Scale(0.95);
                }
            }


            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                for (auto &port : level->getPortals())
                {
                    port.second.RotateHorizontal(0.05f);
                    // port.second.Scale(1.05);
                }
            }


            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                for (auto &port : level->getPortals())
                {
                    port.second.RotateHorizontal(-0.05f);
                    // port.second.scale(0.95);
                }
            }



            // enables cursor
            static int oldStateC = GLFW_RELEASE;
            int newStateC = glfwGetKey(window, GLFW_KEY_C);
            if (newStateC == GLFW_RELEASE && oldStateC == GLFW_PRESS) {
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
            oldStateC = newStateC;
        }

        static int oldStateE = GLFW_RELEASE;
        int newStateE = glfwGetKey(window, GLFW_KEY_E);
        if (newStateE == GLFW_RELEASE && oldStateE == GLFW_PRESS) {
            if (!creativeEnabled)
            {
                creativeEnabled = true;
            }
            else
            {
                creativeEnabled = false;
                saveObject();
            }
        }
        oldStateE = newStateE;

        // select Object
        static int oldStateR = GLFW_RELEASE;
        int newStateR = glfwGetKey(window, GLFW_KEY_R);
        if (newStateR == GLFW_RELEASE && oldStateR == GLFW_PRESS) 
        {
            selectObject();
        }
        oldStateR = newStateR;

        // select Object
        static int oldStateU = GLFW_RELEASE;
        int newStateU = glfwGetKey(window, GLFW_KEY_U);
        if (newStateU == GLFW_RELEASE && oldStateU == GLFW_PRESS)
        {
            if (!isPortalVisible)
            {
                isPortalVisible = true;
                Portal::portalBackground[0] = 0.1f;
                Portal::portalBackground[1] = 0.1f;
                Portal::portalBackground[2] = 0.1f;
            }
            else
            {
                isPortalVisible = false;
                Portal::portalBackground[0] = 0.3f;
                Portal::portalBackground[1] = 0.8f;
                Portal::portalBackground[2] = 1.0f;
            }
        }
        oldStateU = newStateU;

    }

    bool checkObjectCollision(Object obj) const
    {
        // check collision with objects
        const std::map<std::string /* object ID */, Object> objects = level->getObjects();
        for (auto const& it : objects)
        {
            if (it.first == obj.GetId())
            {
                continue;
            }
            if (CollisionHandler::check_collision(obj, it.second))
            {
                return true;
            }
        }

        // check collision with portals
        const std::map<std::string /* object ID */, Portal> portals = level->getPortals();
        for (auto const& portal : portals)
        {
            if (portal.first == obj.GetId())
            {
                continue;
            }
            if (CollisionHandler::check_collision(obj, portal.second))
            {
                return true;
            }
        }

        // check collision with player
        return CollisionHandler::check_collision(player->getCamera(), obj);
    }

    bool checkMovement(Player dummy_player)
    {
        if (!isPassing)
        {
            const std::map<std::string /* object ID */, Object> objects = level->getObjects();
            for (auto const& it : objects)
            {
                if (CollisionHandler::check_collision(dummy_player, it.second))
                {
                    return true;
                }
            }
        }


        bool touched_any = false;
        const std::map<std::string /* object ID */, Portal> portals = level->getPortals();
        for (auto & it : portals)
        {
            if (CollisionHandler::check_collision(dummy_player, it.second))
            {
                if (!isPassing)
                {
                    player->setCamera(it.second.GetPairCamera(dummy_player.getCamera()));
                }
                isPassing = true;
                touched_any = true;
                break;
            }
        }

        if (!touched_any)
        {
            isPassing = false;
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

    void castRay()
    {
        Ray ray(&player->getCamera(), window);
        
        float mint = FLT_MAX;

        std::map<std::string /* object ID */, Object> levelObjects = level->getObjects();

        for (auto const& obj : levelObjects)
        {
            float t = FLT_MAX;
            if (CollisionHandler::check_collision(ray, obj.second, t))
            {
                if (obj.second.GetId() == updateObjectId)
                {
                    continue;
                }
                if (t < mint)
                {
                    mint = t;
                    underViewObjectId = obj.first;
                }
            }
        }

        // check collision with portals
        const std::map<std::string /* object ID */, Portal> portals = level->getPortals();
        for (auto const& portal : portals)
        {
            float t = FLT_MAX;
            if (CollisionHandler::check_collision(ray, portal.second, t))
            {
                if (portal.first == updateObjectId)
                {
                    continue;
                }
                if (t < mint)
                {
                    mint = t;
                    underViewObjectId = portal.first;
                }
            }
        }

        if (updateObjectId != "None")
        {
            float dist;
            if (mint < distance)
            {
                dist = mint;
            }
            else
            {
                dist = distance;
            }
            if (dist < minDistance)
            {
                dist = minDistance;
            }
            while(dist >= minDistance)
            {
                glm::vec3 obj_pos = ray.getOrigin() + (dist)*ray.getDirection();
                const glm::mat4 oldWorldMat = level->getObjectPointer(updateObjectId)->GetWorldMat();
                moveCreateObjectToPosition(obj_pos);
                if (checkObjectCollision(level->getObject(updateObjectId)))
                {
                    level->getObjectPointer(updateObjectId)->SetWorldMatrix(oldWorldMat);
                }
                else
                {
                    break;
                }
                dist -= 0.1f;
            }

        }


        if (mint == FLT_MAX)
        {
            underViewObjectId = "None";
            return;
        }
        
    }

    float lastMouseX;
    float lastMouseY;
    GLFWwindow* window;
    Level * level;
    Player* player;
    
    const float minDistance = 2.0f;
    float distance = 5.0f;
    float rotation_degree = 0.01f;


public:
    bool isPassing;
    bool cursorEnabled;
    bool creativeEnabled;
    
    static string underViewObjectId;
    static string updateObjectId;

    Shader *objectShader;
    Shader *portalShader;

    bool isPortalVisible = true;
};

string EventHandler::underViewObjectId("None");
string EventHandler::updateObjectId("None");
