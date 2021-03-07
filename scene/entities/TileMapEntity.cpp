#include "TileMapEntity.h"

namespace VEngine
{
	TileMapEntity::TileMapEntity()
	{

	}

	TileMapEntity::~TileMapEntity()
	{
		for (Tile* tile : tiles)
			delete tile;
	}

	void TileMapEntity::start()
	{

	}

	void TileMapEntity::update()
	{
		VE_PROFILE_FUNC;
		for (Tile* tile : tiles)
		{
			tile->update();

			Event event(Event::EventType::EngineRendererDraw);
			event.drawEvent.drawable = tile;
			event.drawEvent.drawLayer = drawLayer;
			event.submite();
		}
	}
	
	void TileMapEntity::handleEvent(Event event)
	{


	}

	Tile* TileMapEntity::getTile(sf::Uint16 x, sf::Uint16 y)
	{
		if (x > columns || y > rows)
		{
			VEngine::Debug::Logger::init().Log(VEngine::Debug::Logger::Type::warning, "unable get tile with coordinated: " + std::to_string(x) + " - " + std::to_string(y), true);
			return nullptr;
		}

		return tiles[x + y * columns];

	}

	void TileMapEntity::setDrawLayer(sf::Uint8 layer)
	{
		drawLayer = layer;
	}

	void TileMapEntity::setSpacing(float xSpacing, float ySpacing)
	{
		VE_PROFILE_FUNC;
		if (xSpacing < 0 || ySpacing < 0)
		{
			VEngine::Debug::Logger::init().Log(VEngine::Debug::Logger::Type::error, "unable set spacing with arguments: " + std::to_string(xSpacing) + " - " + std::to_string(ySpacing), true);
			return;
		}

		this->xSpacing = xSpacing;
		this->ySpacing = ySpacing;

		for (sf::Uint16 c = 0; c < columns; c++)
		{
			for (sf::Uint16 r = 0; r < rows; r++)
			{
				getTile(c, r)->setPosition(getPosition() + sf::Vector2f(xSpacing * c, ySpacing * r));
			}
		}
	}

	void TileMapEntity::setPosition(float x, float y)
	{
		VE_PROFILE_FUNC;
		sf::Vector2f oldPos = getPosition();
		sf::Transformable::setPosition(x,y);

		for (sf::Uint16 c = 0; c < columns; c++)
		{
			for (sf::Uint16 r = 0; r < rows; r++)
			{
				getTile(c, r)->move(getPosition() - oldPos);
			}
		}
	}

	void TileMapEntity::setPosition(const sf::Vector2f& position)
	{
		setPosition(position.x,position.y);
	}

	void TileMapEntity::move(float offsetX, float offsetY)
	{
		setPosition(getPosition() + sf::Vector2f(offsetX,offsetY));
	}

	void TileMapEntity::move(const sf::Vector2f& offset)
	{
		move(offset.x, offset.y);
	}

}