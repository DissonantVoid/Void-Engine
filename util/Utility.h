#pragma once

#include "SFML/System.hpp"
#include <string>
#include <optional>

namespace VEngine::Resources
{
	struct animation;
}

namespace VEngine
{
	namespace Util
	{

		bool ParseFileAnimation(std::string path,Resources::animation* animation);

		//get persentage out of value in a range
		template<typename T>
		static int valToPercent(T value, T min, T max)
		{

		}

		//get value out of persentage in a range
		template<typename T>
		static int percentToVal(T percentage, T min, T max)
		{
			
		}

		//vector calculations: normalizing...
		template<typename T>
		static float vecDistance(sf::Vector2<T> start, sf::Vector2<T> end)
		{
			sf::Vector2<T> result;
			result.x = std::abs((end.x - start.x) * (end.x - start.x));
			result.y = std::abs((end.y - start.y) * (end.y - start.y));
			return std::sqrt(result.x + result.y);
		}

		template<typename T>
		static sf::Vector2<T> vecNormal(sf::Vector2<T> start, sf::Vector2<T> end)
		{
			float distance = vecDistance<T>(start,end);

		}

		//dotproduct
		//Cross Product

		//lerp
		static float lerp(...);

		//value mapping
		template<typename T>
		static int mapValue(T value, T min, T max, T newMin, T newMax)
		{

		}
	}
}