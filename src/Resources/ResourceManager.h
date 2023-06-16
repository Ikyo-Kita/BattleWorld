#pragma once
#include<string>
#include<memory>
#include<map>
namespace Renderer 
{
	class ShaderProgram;
	class Texture2D;
}
class ResourceManager
{
public:
	ResourceManager(const std::string& executablePath);//The Announcement constructor of class ResourceManager
	~ResourceManager() = default;//The Announcement destructor of class ResourceManager


	/*The banned variation constructor*/
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	/*The Announcement the method loadShaders*/
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	/*The Announcement the method getShaderProgram*/
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	/*The Announcement the method loadTexture*/
	std:: shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	/*The Announcement the method getTexture*/
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);


private:
	std::string getFileString(const std::string& relativeFilePath) const;//The Announcement the method getFileString

	typedef std::map<const  std::string, std::shared_ptr<Renderer::ShaderProgram>>ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>>TexturesMap;
	TexturesMap m_textures;
	std::string m_path;
	
};