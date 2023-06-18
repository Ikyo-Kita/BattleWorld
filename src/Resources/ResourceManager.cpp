#include"ResourceManager.h"
#include"../Renderer/ShaderProgram.h"
#include"../Renderer/Texture2D.h"
#include<sstream>
#include<fstream>
#include<iostream>
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");

	m_path = executablePath.substr(0, found);
}
/*The realization the method getFileString annoucmented in ResourceManager.h*/
std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);//Open source shaders 
	if (!f.is_open() )
	{
		std::cerr << "ERROR Open file: " << relativeFilePath << std::endl;
		system("pause");
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
/*The realization the method loadShaders annoucmented in ResourceManager.h*/
std::shared_ptr<Renderer::ShaderProgram>ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader ERROR!" << std::endl;
		system("pause");
		return nullptr;
	}
	std::string fragmentxString = getFileString(fragmentPath);
	if (fragmentxString.empty())
	{
		std::cerr << "No fragment shader ERROR!" << std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader =m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentxString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Can`t load shader program ERROR: \n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;
	system("pause");
	return nullptr;
}
/*The realization the method getShaderProgram of class ResourceManager annoucmented in ResourceManager.h*/
std::shared_ptr<Renderer::ShaderProgram>ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can`t find the shader program ERROR: " << shaderName << std::endl;
	system("pause");
	return nullptr;
};
/*The realization the loadTexture method of class ResourceManager annoucemented at ResourceManager.h*/
std::shared_ptr<Renderer::Texture2D>ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{

	int channels = 0;
	int width = 0;
	int height = 0;
	
	stbi_set_flip_vertically_on_load(true);

	unsigned char*pixels= stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height,&channels,0);

	if (!pixels) {
		std::cerr << "Load texture ERROR: " << textureName << std::endl;
		system("pause");
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName,
		std::make_shared<Renderer::Texture2D>(
			width, 
			height, 
			pixels,
			channels,
			GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}
/*The realization the getTexture method  */
std::shared_ptr<Renderer::Texture2D>ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Can`t find the texture ERROR: " << textureName << std::endl;
	system("pause");
	return nullptr;

}