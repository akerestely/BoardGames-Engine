#include "Sprite.h"

#include "glew.h"

#include "Vertex.h"

namespace Engine
{
	Sprite::Sprite()
	{
		m_vboId = 0;
	}

	void Sprite::Init(float x, float y, float width, float height, const char* texturePath)
	{
		m_bounds.Set(posf{ x, y }, posf{ x + width, y + height });

		m_texture = ResourceMngr::GetTexture(texturePath);

		if (!m_vboId)
		{
			glGenBuffers(1, &m_vboId);
		}

		Vertex vertexData[6];

		vertexData[0].SetPosition(x + width, y + height);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(x, y + height);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(0.0f, 0.0f);

		vertexData[3].SetPosition(x, y);
		vertexData[3].SetUV(0.0f, 0.0f);

		vertexData[4].SetPosition(x + width, y);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5].SetPosition(x + width, y + height);
		vertexData[5].SetUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].SetColor(255, 0, 255, 255);
		}

		vertexData[1].SetColor(0, 0, 255, 255);
		vertexData[4].SetColor(0, 255, 0, 255);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
		if (m_vboId)
			glDeleteBuffers(1, &m_vboId);
	}
}
