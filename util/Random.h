#pragma once

#include <random>

namespace VEngine
{
	namespace Util
	{
		class Random
		{
		public:
			static Random& init() { static Random instance;return instance;}

			void setSeed(int seed);
			
			int getInt();
			int getInt(int min, int max);

			float getFloat();
			float getFloat(float min,float max);

			bool getBool();

			//random seaquence

		private:
			std::random_device rd;
			std::mt19937 mtwister;

			Random();
			~Random();
		};
	}
}

