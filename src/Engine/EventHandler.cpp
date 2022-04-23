#include "EventHandler.h"

string EventHandler::underViewObjectId("None");
string EventHandler::updateObjectId("None");



void EventHandler::HandleEvents(float deltaTime) 
{
    // handle keyboard
    ProcessInput(deltaTime);

    // handle mouse
    if (!cursorEnabled) { MouseCallback(); }
    //std::cout << selectedObjectId << std::endl;
    if (creativeEnabled)
    {
        CastRay();
    }
}


void EventHandler::MoveSelectedObjectToPosition(glm::vec3 position)
{
    if (underViewObjectId == "None")
    {
        return;
    }
    level->GetObjectPointer(underViewObjectId)->SetPosition(position);
}

void EventHandler::MoveCreateObjectToPosition(glm::vec3 position)
{
    if (updateObjectId == "None")
    {
        return;
    }
    level->GetObjectPointer(updateObjectId)->SetPosition(position);
}


void EventHandler::SaveObject()
{
    creativeEnabled = false;
    underViewObjectId = "None";
    updateObjectId = "None";
}

void EventHandler::SelectObject()
{
    if (underViewObjectId == "None")
    {
        return;
    }
    updateObjectId = underViewObjectId;
}

void EventHandler::DeleteObject()
{
    level->DeleteObject(underViewObjectId);
}


string EventHandler::AddObject(string name, glm::vec3 Position)
{
    return level->AddObject(name, Position);
}

void EventHandler::AddPortals()
{
    Ray ray(&player->GetCamera(), window);
    glm::vec3 locationFirst = ray.GetOrigin() + (minDistance + 1.0f) * ray.GetDirection();
    glm::vec3 locationSecond = ray.GetOrigin() + (minDistance + 3.0f) * ray.GetDirection();
    // portals pair creation
    level->AddPortalPair(locationFirst, locationSecond);
}

void EventHandler::ProcessInput(float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else
    {
        Player dummy_player = player->GetCopy();
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            deltaTime *= 2.0f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            dummy_player.Move(FORWARD, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(FORWARD, deltaTime);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            dummy_player.Move(BACKWARD, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(BACKWARD, deltaTime);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            dummy_player.Move(STRAFELEFT, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(STRAFELEFT, deltaTime);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            dummy_player.Move(STRAFERIGHT, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(STRAFERIGHT, deltaTime);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            dummy_player.Move(UPWARD, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(UPWARD, deltaTime * 2);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            //if (true)
        {
            dummy_player.Move(DOWNWARD, deltaTime);
            if (!CheckMovement(dummy_player))
            {
                player->Move(DOWNWARD, deltaTime);
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
            SaveObject();
        }

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            LevelHandler::WriteLevel("temp_level", *level, player->GetCamera());
        }

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            Level newLevel = LevelHandler::ReadLevel("temp_level.lev", player->GetCamera(), *portalShader, *objectShader);
            *level = newLevel;
        }

        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
        {
            for (auto& port : level->GetPortals())
            {
                // port.second.RotateHorizontal(45.0f);
                port.second.Scale(1.05);
            }
        }


        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
        {
            for (auto& port : level->GetPortals())
            {
                // port.second.RotateHorizontal(45.0f);
                port.second.Scale(0.95);
            }
        }


        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            for (auto& port : level->GetPortals())
            {
                port.second.RotateHorizontal(0.05f);
                // port.second.Scale(1.05);
            }
        }


        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            for (auto& port : level->GetPortals())
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
            SaveObject();
        }
    }
    oldStateE = newStateE;

    // select Object
    static int oldStateR = GLFW_RELEASE;
    int newStateR = glfwGetKey(window, GLFW_KEY_R);
    if (newStateR == GLFW_RELEASE && oldStateR == GLFW_PRESS)
    {
        SelectObject();
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


bool EventHandler::CheckObjectCollision(Object obj) const
{
    // check collision with objects
    const std::map<std::string /* object ID */, Object> objects = level->GetObjects();
    for (auto const& it : objects)
    {
        if (it.first == obj.GetId())
        {
            continue;
        }
        if (CollisionHandler::CheckCollision(obj, it.second))
        {
            return true;
        }
    }

    // check collision with portals
    const std::map<std::string /* object ID */, Portal> portals = level->GetPortals();
    for (auto const& portal : portals)
    {
        if (portal.first == obj.GetId())
        {
            continue;
        }
        if (CollisionHandler::CheckCollision(obj, portal.second))
        {
            return true;
        }
    }

    // check collision with player
    return CollisionHandler::CheckCollision(player->GetCamera(), obj);
}


bool EventHandler::CheckMovement(Player dummy_player)
{
    if (!isPassing)
    {
        const std::map<std::string /* object ID */, Object> objects = level->GetObjects();
        for (auto const& it : objects)
        {
            if (CollisionHandler::CheckCollision(dummy_player, it.second))
            {
                return true;
            }
        }
    }


    bool touched_any = false;
    const std::map<std::string /* object ID */, Portal> portals = level->GetPortals();
    for (auto& it : portals)
    {
        if (CollisionHandler::CheckCollision(dummy_player, it.second))
        {
            if (!isPassing)
            {
                player->SetCamera(it.second.GetPairCamera(dummy_player.GetCamera()));
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


void EventHandler::MouseCallback()
{
    double xpos;
    double ypos;

    // gets mouse x and y positions
    glfwGetCursorPos(window, &xpos, &ypos);

    float xoffset = (float)(lastMouseX - xpos);
    float yoffset = (float)(lastMouseY - ypos); // reversed since y-coordinates range from bottom to top
    lastMouseX = (float)xpos;
    lastMouseY = (float)ypos;

    player->GetCamera().ProcessMouseMovement(xoffset, yoffset);
}


void EventHandler::CastRay()
{
    Ray ray(&player->GetCamera(), window);

    float mint = FLT_MAX;

    std::map<std::string /* object ID */, Object> levelObjects = level->GetObjects();

    for (auto const& obj : levelObjects)
    {
        float t = FLT_MAX;
        if (CollisionHandler::CheckCollision(ray, obj.second, t))
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
    const std::map<std::string /* object ID */, Portal> portals = level->GetPortals();
    for (auto const& portal : portals)
    {
        float t = FLT_MAX;
        if (CollisionHandler::CheckCollision(ray, portal.second, t))
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
        while (dist >= minDistance)
        {
            glm::vec3 obj_pos = ray.GetOrigin() + (dist)*ray.GetDirection();
            const glm::mat4 oldWorldMat = level->GetObjectPointer(updateObjectId)->GetWorldMat();
            MoveCreateObjectToPosition(obj_pos);
            if (CheckObjectCollision(level->GetObject(updateObjectId)))
            {
                level->GetObjectPointer(updateObjectId)->SetWorldMatrix(oldWorldMat);
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
