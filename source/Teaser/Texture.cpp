//------------------------------------------------------------
// <copyright file="Texture.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Texture.hpp>

namespace Teaser
{

Texture* Texture::loadTextureFromFile(std::string path)
{
	Texture* tex = new Texture();

	tex->create();
	int width, height, channels;
	byte* pixels = SOIL_load_image(
	    path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	Texture::Format format = Texture::RGB;
	if (channels > 4 || channels < 3)
	{
		// TODO(markus): better logging statement here
		std::cerr << "Imageformat of image at " << path << " not supported!"
		          << std::endl;
	}
	else if (channels == 4)
	{
		format = Texture::RGBA;
	}

	tex->loadData(pixels, width, height, format);
	SOIL_free_image_data(pixels);

	return tex;
}

void Texture::create()
{

	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::loadData(byte* data, u32 width, u32 height, Format format)
{
	tassert(m_handle != 0,
	        "Texture create() must be called before loadData().");

	glBindTexture(GL_TEXTURE_2D, m_handle);

	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             format,
	             width,
	             height,
	             0,
	             format,
	             GL_UNSIGNED_BYTE,
	             data);

	m_format = format;
	m_width  = width;
	m_height = height;
}

void Texture::destroy() { glDeleteTextures(1, &m_handle); }

} // namespace Teaser