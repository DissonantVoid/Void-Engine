#include "UIDrawable.h"

namespace VEngine
{
	UIDrawable::UIDrawable()
	{

	}

	UIDrawable::UIDrawable(sf::Drawable* drawable)
		: drawable(drawable)
	{

	}

	UIDrawable::~UIDrawable()
	{
		if (drawable != nullptr) delete drawable;
	}

	void UIDrawable::setDrawable(sf::Drawable* drawable)
	{
		this->drawable = drawable;
	}

	const sf::Drawable* UIDrawable::getDrawable() const
	{
		return drawable;
	}

	void UIDrawable::update()
	{
		
	}

	void UIDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(*drawable,states);
	}

	//private
}