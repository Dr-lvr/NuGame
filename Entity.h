#pragma once
class Entity {

public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
private:
	sf::Vector2f mVelocity;
};
void Entity::setVelocity(sf::Vector2f velocity){
	mVelocity = velocity;
}
void Entity::setVelocity(float vx, float vy){
	mVelocity.x = vx;
	mVelocity.y = vy;
}
sf::Vector2f Entity::getVelocity() const{
	return mVelocity;
}
class Aircraft : public Entity{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};
public:
	explicit Aircraft(Type type);
private:
	Type mType;
};
Aircraft::Aircraft(Type type) : mType(type){
}