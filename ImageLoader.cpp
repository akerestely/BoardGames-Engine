#include "ImageLoader.h"

#include "glew.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

#include <cstdint>

namespace Engine
{
	Engine::Texture ImageLoader::LoadPNG(const char* filepPath)
	{
		Texture texture = {};

		std::vector<uint8_t> in;
		std::vector<uint8_t> out;
		unsigned long width, height;

		if(!IOManager::ReadFileToBuffer(filepPath, in))
			fatalError("Failed to load PNG file to buffer!");

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode)
			fatalError("Decode PNG failed!");

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//for OpenGl <3.0
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		//for OpenGl >3.0
		//glGenerateMipmap(GL_TEXTURE_2D);
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.size.width=width;
		texture.size.height=height;

		return texture;
	}
}