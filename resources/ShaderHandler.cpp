#include "ShaderHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{
		bool ShaderHandler::addShader(std::string name, sf::Shader* shader)
		{
			VE_PROFILE_FUNC;

			if (shader == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add shader with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete shader;
				return false;
			}

			if (shaders.find(name) != shaders.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add shader with name: " + name + ", name already exist (shader is now deleted)", true);
				delete shader;
				return false;
			}
			shaders.emplace(std::make_pair(name, shader));
			return true;
		}

		bool ShaderHandler::addShader(std::string name, std::string vertexpath, std::string fragementpath)
		{
			VE_PROFILE_FUNC;
			if (shaders.find(name) != shaders.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add shader with name: " + name + ", name already exist", true);
				return false;
			}
			
			sf::Shader* shader = new sf::Shader;
			if (vertexpath.empty())
			{
				if (shader->loadFromFile(fragementpath,sf::Shader::Type::Fragment) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add fragment only shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}
			else if (fragementpath.empty())
			{
				if (shader->loadFromFile(vertexpath, sf::Shader::Type::Vertex) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add vertex only shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}
			else
			{
				if (shader->loadFromFile(vertexpath,fragementpath) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}

			shaders.emplace(std::make_pair(name, shader));
			return true;
		}

		bool ShaderHandler::addShaderString(std::string name, std::string vertexData, std::string fragmentData)
		{
			VE_PROFILE_FUNC;
			if (shaders.find(name) != shaders.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add shader with name: " + name + ", name already exist", true);
				return false;
			}

			sf::Shader* shader = new sf::Shader;
			if (vertexData.empty())
			{
				if (shader->loadFromMemory(fragmentData, sf::Shader::Type::Fragment) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add fragment only shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}
			else if (fragmentData.empty())
			{
				if (shader->loadFromMemory(vertexData, sf::Shader::Type::Vertex) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add vertex only shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}
			else
			{
				if (shader->loadFromMemory(vertexData, fragmentData) == false)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add shader with name: " + name + ", file path may be invalid", true);
					delete shader;
					return false;
				}
			}

			shaders.emplace(std::make_pair(name, shader));
			return true;
		}
		
		bool ShaderHandler::isShader(std::string name)
		{
			return (shaders.find(name) != shaders.end());
		}

		const sf::Shader* ShaderHandler::getShader(std::string name)
		{
			VE_PROFILE_FUNC;
			std::unordered_map<std::string, sf::Shader*>::iterator result = shaders.find(name);
			if (result != shaders.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get shader with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool ShaderHandler::removeShader(std::string name)
		{
			VE_PROFILE_FUNC;
			if (shaders.find(name) != shaders.end())
			{
				shaders.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove shader with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private

		ShaderHandler::ShaderHandler()
		{

		}

		ShaderHandler::~ShaderHandler()
		{
			VE_PROFILE_FUNC_ONCE;
			for (auto& shader : shaders)
				delete shader.second;
		}
	}
}