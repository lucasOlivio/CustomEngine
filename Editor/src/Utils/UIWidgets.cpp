#include "pch.h"

#include "UIWidgets.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void Guizmo(Scene* pScene, Entity entityId)
    {
        TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
        if (!pTransform)
        {
            return;
        }

        glm::mat4 viewMatrix = GraphicsLocator::GetCamera()->ViewMat();
        glm::mat4 projectionMatrix = GraphicsLocator::GetWindow()->ProjectionMat();

        // Set the ImGuizmo transformation matrix
        ImGuizmo::SetID(0); // Use 0 as the ID for a single gizmo
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist(); // Setup draw list

        // Specify the operation (translate, rotate, scale)
        ImGuizmo::OPERATION operation = ImGuizmo::TRANSLATE;

        // Specify the mode (local, world)
        ImGuizmo::MODE mode = ImGuizmo::LOCAL;

        // Get the model matrix from the transform component
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        TransformUtils::GetTransform(pTransform->worldPosition,
                                    pTransform->worldOrientation, 
                                    pTransform->worldScale, modelMatrix);

        // Draw the ImGuizmo manipulator
        ImGuizmo::DrawGrid(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), 
                           glm::value_ptr(modelMatrix), 100.f);
        ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
                             operation, mode, glm::value_ptr(modelMatrix));
    }
}
