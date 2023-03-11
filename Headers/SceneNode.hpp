#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "Category.hpp"

class SceneNode: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	SceneNode() {};
	typedef std::unique_ptr<SceneNode> Ptr;

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	virtual unsigned int getCategory() const;
	void attachChild(Ptr child);
	void update(sf::Time timedelta);
	Ptr detachChild(const SceneNode& node);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time timedelta);
	void updateChildren(sf::Time timedelta);
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

