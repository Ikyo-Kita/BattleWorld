#include"Texture2D.h"

namespace Renderer
{
	/*The method for generation texture*/
	void Texture2D::GenerationTexture(const unsigned char* data)
	{
		glGenTextures(1, &m_ID);//Generation the textureID
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	/*The texture parameter input method*/
	void Texture2D::TextureParameters(const GLenum& wrapMode, const GLenum& filter)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glBindTexture(GL_TEXTURE_2D, 0);//This line make the current texture isn`t current
	}
	/*The realization the constructor of class Texture2D annoucement at Texture2D*/
	Texture2D::Texture2D(const GLuint width, const GLuint height,
		const unsigned  char* data,
		const unsigned int  channels,
		const GLenum filter,
		const GLenum wrapMode)
		:m_width(width),
		m_height(height)
	{
		switch (channels)
		{
		case 4:
			m_mode = GL_RGBA;
			break;
		case 3:
			m_mode = GL_RGB;
			break;

		default:
			m_mode = GL_RGBA;
			break;
		}

		GenerationTexture(data);
		TextureParameters(wrapMode, filter);
	}
	
	/*Realization the move operator of class Texture2D*/
	Texture2D& Texture2D:: operator=(Texture2D&& texture2D)
	{
		glDeleteTextures(1, &m_ID);
		m_ID = texture2D.m_ID;
		texture2D.m_ID = 0;
		m_mode = texture2D.m_mode;
		m_width = texture2D.m_width;
		m_height = texture2D.m_height;
		return*this;
	}
	/*Realization the move constructor of class Texture2D*/
	Texture2D::Texture2D(Texture2D&& texture2D)
	{
		m_ID = texture2D.m_ID;
		texture2D.m_ID = 0;
		m_mode = texture2D.m_mode;
		m_width = texture2D.m_width;
		m_height = texture2D.m_height;
	}
	Texture2D::~Texture2D()//Realization the destructor of class Texture2D
	{
		glDeleteTextures(1, &m_ID);
	}
	/*
	Realization the method bind() annoucemented at Texture2D.h 
	This method make the texture is current.
	*/
	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}