#include "inc/SpriteSheet.hpp"
#include <glad/glad.h>

SpriteSheet::SpriteSheet(const std::string& path) : textureId(0)
{
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	PrepareData(data);
	stbi_image_free(data);
	data = nullptr;
}

SpriteSheet::SpriteSheet(const std::string&& path) : textureId(0)
{
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	PrepareData(data);
	stbi_image_free(data);
	data = nullptr;
}

SpriteSheet::~SpriteSheet() {
}

void SpriteSheet::PrepareData(unsigned char* data)
{
	if (data) {
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
		
}
