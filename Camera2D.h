#pragma once
#include "glm.hpp"

namespace Engine
{
	class Camera2D
	{
	public:
		Camera2D(void);

		void Init(int screenWidth, int screenHeight);
		void Update();

		glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

		//setters
		void SetPosition(const glm::vec2 &newPosition);
		void SetScale(float newScale);
		void SetScale(const glm::vec2 &newScale);

		//getters
		const glm::vec2& GetPosition();
		const glm::vec2& GetScale();
		const glm::mat4& GetCameraMatrix() const;

	private:
		int m_screenWidth;
		int m_screenHeight;
		bool m_needsUpdate;
		glm::vec2 m_scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
	};
}

