#include "Camera2D.h"

#include <gtc/matrix_transform.hpp>

namespace Engine
{
	Camera2D::Camera2D() :
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_needsUpdate(true),
		m_screenWidth(500),
		m_screenHeight(500)
	{
		// empty
	}

	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
	}

	void Camera2D::Update()
	{
		if (m_needsUpdate)
		{
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			m_needsUpdate = false;
		}
	}

	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords)
	{
		screenCoords.y = m_screenHeight - screenCoords.y;
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		screenCoords /= m_scale;
		screenCoords += m_position;
		return screenCoords;
	}
}
