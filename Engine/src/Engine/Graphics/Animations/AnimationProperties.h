#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	enum class eEasingType
	{
		Linear,
		SineEaseIn,
		SineEaseOut,
		SineEaseInOut
	};

	struct KeyFrame
	{
		KeyFrame()
		{
			time = 0.0f;
			easeType = eEasingType::Linear;
		}
		KeyFrame(float time_, eEasingType type = eEasingType::Linear)
		{
			time = time_;
			easeType = type;
		}

		eEasingType easeType;
		float time;
	};

	struct PositionKeyFrame : KeyFrame
	{
		PositionKeyFrame()
			: KeyFrame()
		{
			value = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		PositionKeyFrame(glm::vec3 position, float time_, eEasingType type = eEasingType::Linear)
			: KeyFrame(time_, type)
		{
			value = position;
		}

		glm::vec3 value;
	};

	struct ScaleKeyFrame : KeyFrame
	{
		ScaleKeyFrame()
			: KeyFrame()
		{
			value = 0.0f;
		}
		ScaleKeyFrame(float scale, float time_, eEasingType type = eEasingType::Linear)
			: KeyFrame(time_, type)
		{
			value = scale;
		}

		float value;
	};

	struct RotationKeyFrame : KeyFrame
	{
		RotationKeyFrame()
			: KeyFrame()
		{
			value = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		}
		RotationKeyFrame(glm::vec3 rotation, float time_, eEasingType type = eEasingType::Linear)
			: KeyFrame(time_, type)
		{
			value = rotation;
		}

		glm::quat value;
	};
}
