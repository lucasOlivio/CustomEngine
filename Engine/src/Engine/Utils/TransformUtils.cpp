#include "pch.h"

#include "TransformUtils.h"

namespace MyEngine
{
    void TransformUtils::ApplyTranslation(glm::vec3 position, glm::mat4& matModelOut)
    {
        // Translation
        glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f), position);

        matModelOut = matModelOut * matTranslate;
    }

    void TransformUtils::ApplyRotation(glm::quat orientation, glm::mat4& matModelOut)
    {
        // Rotation matrix generation
        glm::mat4 matRotation = glm::mat4(orientation);

        matModelOut = matModelOut * matRotation;
    }

    void TransformUtils::ApplyScale(float scale, glm::mat4& matModelOut)
    {
        // Scaling matrix
        glm::mat4 matScale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));

        matModelOut = matModelOut * matScale;
    }

    void TransformUtils::GetTransform(glm::vec3 position, 
                                      glm::quat orientation,
                                      float scale, 
                                      glm::mat4& matModelOut)
    {
        // Combine all the transformations
        ApplyTranslation(position, matModelOut);
        ApplyRotation(orientation, matModelOut);
        ApplyScale(scale, matModelOut);

        return;
    }

    glm::vec3 TransformUtils::GetUpVector(glm::quat orientation)
    {
        return orientation * UP_VECTOR;
    }

    glm::vec3 TransformUtils::GetForwardVector(glm::quat orientation)
    {
        return orientation * FORWARD_VECTOR;
    }
}
