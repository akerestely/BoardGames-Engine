#pragma once
#include "Vertex.h"
#include <gtc\matrix_transform.hpp>
#include <vector>

namespace Engine
{
	struct Glyph
	{
		enum class SortType
		{
			None,
			FrontToBack,
			BackToFront,
			Texture
		};

		Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, uint texture, float depth, const ColorRGBA8 &color);

		uint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	struct RenderBatch
	{
		RenderBatch(uint offset, uint numVertices, uint texture);

		uint offset;
		uint numVertices;
		uint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();

		void Init();

		void Begin(Glyph::SortType sortType = Glyph::SortType::Texture);
		void Draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, uint texture, float depth, const ColorRGBA8 &color);
		void End();

		void RenderBatches();

	private:
		void createRenderBatches();
		void createVertexArray();
		void bindBufferAndAttribs();
		void unbindBufferAndAttribs();
		void sortGlyphs();

	private:
		uint m_vbo;
		uint m_vao;

		Glyph::SortType m_sortType;

		std::vector<Glyph*> m_glyphPointers; /// for sorting
		std::vector<Glyph> m_glyphs; /// actual glyphs
		std::vector<RenderBatch> m_renderBatches;
	};
}

