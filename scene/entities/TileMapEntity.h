#pragma once

#include <vector>

#include "Engine/scene/entities/Entity.h"
#include "Engine/resources/SFML Extensions/Tile.h"
#include "Engine/debug/Logger.h"

#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	class TileMapEntity : public Entity, public sf::Transformable
	{
	public:
		TileMapEntity();
		~TileMapEntity();

		void start() override;
		void update() override;
		void handleEvent(Event event) override;

		template<typename tileType>
		void fill(sf::Uint16 x, sf::Uint16 y, float xSpacing, float ySpacing, void(*additionalFunc)(tileType* tile) = nullptr)
		{
			VE_PROFILE_FUNC;
			if (x == 0 || y == 0 || xSpacing < 0 || ySpacing < 0)
			{
				VEngine::Debug::Logger::init().Log(VEngine::Debug::Logger::Type::error, "unable to fill the tileMap, inappropriate input: x=" + std::to_string(x) + " - y=" + std::to_string(y) + " - xSpacing=" + std::to_string(xSpacing) + " - ySpacing=" + std::to_string(ySpacing), true);
				return;
			}

			if (std::is_base_of<Tile, tileType>::value == false)
			{
				VEngine::Debug::Logger::init().Log(VEngine::Debug::Logger::Type::error,"unable to fill the tileMap, tileType is not derived from Tile base class",true);
				return;
			}

			columns = x;
			rows = y;
			this->xSpacing = xSpacing;
			this->ySpacing = ySpacing;

			for (Tile* tile : tiles)
				delete tile;
			tiles.clear();

			tiles.reserve(x * y);

			for (sf::Uint16 c = 0; c < x; c++)
			{
				for (sf::Uint16 r = 0; r < y; r++)
				{
					tileType* tile = new tileType;
					tile->setPosition(getPosition() + sf::Vector2f(xSpacing * c,ySpacing * r));

					if (additionalFunc != nullptr)
						additionalFunc(tile);

					tiles.push_back(tile);
				}
			}

		}

		Tile* getTile(sf::Uint16 x, sf::Uint16 y);
		void setDrawLayer(sf::Uint8 layer);

		void setSpacing(float xSpacing,float ySpacing);
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& position);
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);

	private:

		std::vector<Tile*> tiles;
		sf::Uint16 columns;
		sf::Uint16 rows;
		float xSpacing;
		float ySpacing;
		sf::Uint8 drawLayer;

	};
}