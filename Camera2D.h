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
		void SetPosition(const glm::vec2 &newPosition){ m_position = newPosition; m_needsUpdate=true; }
		void SetScale(float newScale) { m_scale = newScale; m_needsUpdate=true; }

		//getters
		glm::vec2 GetPosition() { return m_position; }
		float GetScale() { return m_scale; }
		const glm::mat4& GetCameraMatrix() const { return m_cameraMatrix; }

	private:
		int m_screenWidth;
		int m_screenHeight;
		bool m_needsUpdate;
		float m_scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
	};
}

