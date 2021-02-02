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
			std::uniform_real_distribution<float> dist(min,max);
			return dist(mtwister);
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