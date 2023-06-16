#pragma once

#include<glad/glad.h>
#include<string>


namespace Renderer
{
	class Texture2D
	{
	public:
		/*The annoucement constructor of class Texture2D*/
		Texture2D(const GLuint width, const GLuint height,
			const unsigned  char* data,
			const unsigned int  channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture2D() = delete;//Ban the empty constructor
		Texture2D(const Texture2D&) = delete;//Ban redesigns the constructor  in the constructor as argument
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2D);
		Texture2D(Texture2D&& texture2D);

		~Texture2D();//The annoucement the destructor of class Texture2D
		void bind() const;
		

		

	private:
		GLuint m_mode;
		GLuint m_ID;//The texture ID
		
		unsigned int m_width;
		unsigned int m_height;
	};
}