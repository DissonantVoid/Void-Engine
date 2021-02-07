#include "Parser.h"

#include "Engine/resources/TextureHandler.h"
#include "Engine/resources/AnimationHandler.h"
#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Util
	{
		bool ParseFileAnimation(std::string path, Resources::animation* animation)
		{
			VE_PROFILE_FUNC;
			if (path.find('.') == -1)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse animation with path: " + path + " , the path isn't valid", true);
				return false;
			}

			std::string extension = path.substr(path.find('.') + 1);
			if ((extension != "ANIM") && (extension != "anim") && (extension != "txt"))
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , the type doesn't match the extension [anim] or [txt]", true);
				return false;
			}

			std::ifstream file;
			file.open(path);
			if (file.is_open() == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , it doesn't exist", true);
				return false;
			}

			int linesSize;
			file >> linesSize >> animation->isLoop;

			for (int i = 0; i < linesSize; i++)
			{
				//add a frame to the animation vec and set frame to it
				animation->frames.push_back(Resources::animFrame());
				Resources::animFrame *frame = &animation->frames[animation->frames.size() - 1];

				//handle texture string
				std::string texture;
				if (!(file >> texture))
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , the data inside the file is wrong", true);
					return false;
				}

				//handle texture data
				frame->texture = Resources::TextureHandler::init().getTextureMd(texture);
				if (frame->texture == nullptr)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , a texture name inside the file is invalid", true);
					return false;
				}

				//handle delay
				float delay;
				if (!(file >> delay))
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , the data inside the file is wrong", true);
					return false;
				}
				frame->delay = delay;

				//handle offset
				std::string offset;
				if (!(file >> offset))
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , the data inside the file is wrong", true);
					return false;
				}

				if (offset.find(',') == -1)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "utility couldn't parse file with path: " + path + " , the data inside the file (no ',' in offset)", true);
					return false;
				}

				frame->offset.x = std::stof(offset.substr(0, offset.find(',')));
				frame->offset.y = std::stof(offset.substr(offset.find(',') + 1));
			}

			return true;
		}
	}
}