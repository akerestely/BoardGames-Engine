#pragma once
/*
This is a modified version of the SpriteFont class from the
Seed Of Andromeda source code.
Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

November 28 2014
Original Author: Cristian Zaloj
Modified By: Benjamin Arnold
*/

#include <glm.hpp>
#include <vector>

#include "Vertex.h"

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

namespace Engine 
{
	struct Texture;
	class SpriteBatch;

	struct CharGlyph
	{
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

	/// For text justification
	enum class Justification
	{
		Left,
		Middle,
		Right
	};

	class SpriteFont
	{
	public:
		SpriteFont(const char* font, int size, char cs = FIRST_PRINTABLE_CHAR, char ce = LAST_PRINTABLE_CHAR);

		void Init(const char* font, int size, char cs = FIRST_PRINTABLE_CHAR, char ce = LAST_PRINTABLE_CHAR);

		/// Destroys the font resources
		void Dispose();

		int GetFontHeight() const;

		/// Measures the dimensions of the text
		glm::vec2 Measure(const char* s);

		/// Draws using a sprite batch
		void Draw(SpriteBatch& batch, const char* s, glm::vec2 position, glm::vec2 scaling,
			float depth, ColorRGBA8 tint, Justification just = Justification::Left);

	private:
		static std::vector<std::vector<int>> createRows(const std::vector<glm::ivec4> &rects, int rectsLength, int r, int padding, int& w);

	private:
		int m_regStart, m_regLength;
		std::vector<CharGlyph> m_glyphs;
		int m_fontHeight;

		unsigned int m_texID;
	};
}