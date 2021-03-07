#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace VEngine
{
	namespace Resources
	{
		//TODO: there is a problems with shaders:
		//unlike a texture, we will need to change a shader's params at some point (passing input) and when we do, all drawables
			//using it will be afected by that change

		//one solution to the 2nd problem is by adding shader params to renderedDraw event, so the're set right before drawable is drawn
			//and then set back to default or to different params when another drawable is using that same shader
		class ShaderHandler 
		{
		public:
			static ShaderHandler& init() { static ShaderHandler instance; return instance; }

			bool addShader(const std::string& name, sf::Shader* shader);
			//NOTE if only one of the shaders is to be set, make sure the other param is empty string ""
			bool addShader(const std::string& name, const std::string& vertexpath, const std::string& fragementpath);
			bool addShaderString(const std::string& name, const std::string& vertexData, const std::string& fragmentData);
			bool isShader(const std::string& name)const;
			const sf::Shader* getShader(const std::string& name)const;
			bool removeShader(const std::string& name);

		private:

			std::unordered_map<std::string, sf::Shader*> shaders;

			ShaderHandler();
			~ShaderHandler();
		};
	}
}