#pragma once
#include<string>
#include<glad/glad.h>
#include<glm/mat4x4.hpp>
namespace Renderer 
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);//The designer for class ShaderProgram
		~ShaderProgram();

		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value);
		void setmatrix4(const std::string& name, const glm::mat4& matrix);	
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&)=delete;//Ban using the ShaderProgram as argument at ShaderProgram
		ShaderProgram& operator=(ShaderProgram&&shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram)noexcept;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);//The method for create shader

		bool m_isCompiled=false;
		GLuint m_ID=0;

	};
}