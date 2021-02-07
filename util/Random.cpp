#include "Random.h"

namespace VEngine
{
	namespace Util
	{
		void Random::setSeed(int seed)
		{
			mtwister.seed(seed);
		}

		int Random::getInt()
		{
			std::uniform_int_distribution<int> dist;
			return dist(mtwister);
		}

		int Random::getInt(int min, int max)
		{
			if (min == max) return min;
			if (min > max) return 0;

			std::uniform_int_distribution<int> dist(min, max);
			return dist(mtwister);
		}

		float Random::getFloat()
		{
			std::uniform_real_distribution<float> dist;
			return dist(mtwister);
		}

		float Random::getFloat(float min, float max)
		{
			if (min == max) return min;
			if (min > max) return 0;

			std::uniform_real_distribution<float> dist(min,max);
			return dist(mtwister);
		}

		bool Random::getBool() 
		{
			return getInt(0,1);
		}

		//private

		Random::Random()
			:  rd(), mtwister(rd())
		{

		}

		Random::~Random()
		{

		}
	}
}