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
		//get persentage out of value in a range
		template<typename T>
		static int valToPercent(T value, T min, T max)
		{
			return (value - min) / (max - min);
		}

		//get value out of persentage in a range
		template<typename T>
		static int percentToVal(T percentage, T min, T max)
		{
			return ((max - min) * percentage) + min;
		}

		//distance
		template<typename T>
		static float vecDistance(sf::Vector2<T> start, sf::Vector2<T> end)
		{
			sf::Vector2<T> result;
			result.x = (end.x - start.x) * (end.x - start.x);
			result.y = (end.y - start.y) * (end.y - start.y);
			return std::sqrt(result.x + result.y);
		}

		//normal
		template<typename T>
		static sf::Vector2<T> vecNormal(sf::Vector2<T> vec)
		{
			float distance = vecDistance<T>(sf::Vector2<T>(0,0), vec);
			return sf::Vector2<T>((vec.x / distance) * (vec.x / distance),
								  (vec.y / distance) * (vec.y / distance));
		}

		//dotproduct
		template<typename T>
		static int vecDotProd(sf::Vector2<T> first, sf::Vector2<T> second)
		{
			return (first.x * second.x) + (first.y * second.y);
		}

		//lerp
		template<typename T>
		static float lerp(T value, T min, T max)
		{
			
		}

		//value mapping
		template<typename T>
		static T mapValue(T value, T min, T max, T newMin, T newMax)
		{
			return (value - min) * (newMax - newMin) / (max - min) + newMin;
		}
	}
}