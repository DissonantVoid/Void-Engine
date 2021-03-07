#pragma once

#include "Engine/UI/UI.h"
#include "Engine/debug/Logger.h"

namespace VEngine
{
	class UIDrawable : public UI
	{
	public:
		UIDrawable();
		
		UIDrawable(sf::Drawable* drawable);
		~UIDrawable();

		void setDrawable(sf::Drawable* drawable);
		const sf::Drawable* getDrawable() const;

		template<typename as>
		const as* getDrawable() const
		{
			as* castedDrawable = dynamic_cast<as*>(drawable);
			if (castedDrawable != nullptr)
			{
				return castedDrawable;
			}
			else
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't cast UIDrawable drawable into the given type, it isn't of that type", true);
				return nullptr;
			}
		}
		
		void update() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Drawable* drawable = nullptr;
	};
}
