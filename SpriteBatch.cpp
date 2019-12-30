#include "SpriteBatch.h"

#include <algorithm>

#include "glew.h"

namespace Engine
{
	Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, uint32_t texture, float depth, const ColorRGBA8 &color) :
		texture(texture),
		depth(depth)
	{
		topLeft.color = color;
		topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.SetPosition(destRect.x, destRect.y);
		bottomLeft.SetUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	RenderBatch::RenderBatch(uint32_t offset, uint32_t numVertices, uint32_t texture) :
		offset(offset),
		numVertices(numVertices),
		texture(texture)
	{
		// empty
	}

	SpriteBatch::SpriteBatch() :
		m_vbo(0),
		m_vao(0),
		m_sortType(Glyph::SortType::None)
	{
		// empty
	}

	void SpriteBatch::Init()
	{
		createVertexArray();
	}

	void SpriteBatch::Begin(Glyph::SortType sortType /*= Glyph::SortType::TEXTURE*/)
	{
		this->m_sortType = sortType;
		m_renderBatches.clear();
		m_glyphs.clear();
	}

	void SpriteBatch::Draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, uint32_t texture, float depth, const ColorRGBA8 &color)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::End()
	{
		m_glyphPointers.resize(m_glyphs.size());
		for (uint32_t i = 0; i < m_glyphs.size(); i++)
			m_glyphPointers[i] = &m_glyphs[i];

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::RenderBatches()
	{
		/*opengl > 3*/ //glBindVertexArray(vao);
		/*opengl 2.1*/ bindBufferAndAttribs();
		for (uint32_t i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}
		/*opengl > 3*/ //glBindVertexArray(0);
		/*opengl 2.1*/ unbindBufferAndAttribs();
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphPointers.size() * 6);

		if (m_glyphPointers.empty())
			return;

		int offset = 0;
		int cv = 0;

		RenderBatch rb(offset, 6, m_glyphPointers[0]->texture);
		m_renderBatches.emplace_back(rb);
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->topRight;
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		offset += 6;

		for (uint32_t cg = 1; cg < m_glyphPointers.size(); cg++)
		{
			if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture)
			{
				RenderBatch rb(offset, 6, m_glyphPointers[cg]->texture);
				m_renderBatches.emplace_back(rb);
			}
			else
			{
				m_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->topRight;
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		/* use for opengl > 3
		if(!vao)
			glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);*/

		if (!m_vbo)
			glGenBuffers(1, &m_vbo);

		/* use for opengl > 3
		bindBufferAndAttribs();

		glBindVertexArray(0);*/
	}
	void SpriteBatch::bindBufferAndAttribs()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	}
	void SpriteBatch::unbindBufferAndAttribs()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (m_sortType)
		{
		case Glyph::SortType::BackToFront:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), [](Glyph *a, Glyph *b) {
				return a->depth > b->depth;
			});
			break;
		case Glyph::SortType::FrontToBack:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), [](Glyph *a, Glyph *b) {
				return a->depth < b->depth;
			});
			break;
		case Glyph::SortType::Texture:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), [](Glyph *a, Glyph *b) {
				return a->texture < b->texture;
			});
			break;
		}
	}
}
