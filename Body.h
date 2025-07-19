#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
class gravity; // Forward declare

class Body : public sf::Drawable
{
private:
    sf::CircleShape shape;
    double radius_size;
    double mass;
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    sf::Vector2<double> acceleration;

public:
    Body(double radius_size,
        double mass,
        const sf::Vector2<double>& position = sf::Vector2<double>(0, 0),
        const sf::Vector2<double>& velocity = sf::Vector2<double>(0, 0),
        const sf::Vector2<double>& acceleration = sf::Vector2<double>(0, 0));

	// create a constructor that only takes position and mass
	Body(const sf::Vector2<double>& position, double mass);
void addForce(const sf::Vector2<double>& force) {  
   acceleration.x += force.x / mass;  
   acceleration.y += force.y / mass;  
}
    // create a constructor that only takes position
	Body(const sf::Vector2<double>& position);

    // create a constructor that only takes position, veloctiy andd mass
	Body(const sf::Vector2<double>& position, const sf::Vector2<double>& velocity, double mass);

    void updateAcceleration(std::vector<Body>& bodies);
    void updateVelocity(double deltaTime);
    void updatePosition(double deltaTime);

    double getRadius_Size() const;
    double getMass() const;
    sf::Vector2<double> getPosition() const;
    sf::Vector2<double> getVelocity() const;
    sf::Vector2<double> getAcceleration() const;

    void setRadius(double r);
    void setPosition(const sf::Vector2<double>& pos);
    void setVelocity(const sf::Vector2<double>& vel);
    void setAcceleration(const sf::Vector2<double>& acc);
    void setColor(const sf::Color& color);

    void setMass(double m);

    void setRadiusSize(double r) {
        radius_size = r;
        shape.setRadius(static_cast<float>(radius_size));
        shape.setOrigin(static_cast<float>(radius_size), static_cast<float>(radius_size));
    }

    sf::CircleShape& getShape() {
        return shape;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
