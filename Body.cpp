#include "Body.h"
#include "gravity.h"

// Constructor
Body::Body(double radius_size, double mass,
    const sf::Vector2<double>& position,
    const sf::Vector2<double>& velocity,
    const sf::Vector2<double>& acceleration)
    : radius_size(radius_size), mass(mass), position(position), velocity(velocity), acceleration(acceleration)
{
    shape.setRadius(static_cast<float>(radius_size));
    shape.setOrigin(static_cast<float>(radius_size), static_cast<float>(radius_size));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

// Constructor with position and mass only
Body::Body(const sf::Vector2<double>& position, double mass)
	: radius_size(5.0), mass(mass), position(position), velocity(sf::Vector2<double>(0, 0)), acceleration(sf::Vector2<double>(0, 0))
{
	shape.setRadius(static_cast<float>(radius_size));
	shape.setOrigin(static_cast<float>(radius_size), static_cast<float>(radius_size));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

// Constructor with position only
Body::Body(const sf::Vector2<double>& position)
	: radius_size(5.0), mass(1.0), position(position), velocity(sf::Vector2<double>(0, 0)), acceleration(sf::Vector2<double>(0, 0))
{
	shape.setRadius(static_cast<float>(radius_size));
	shape.setOrigin(static_cast<float>(radius_size), static_cast<float>(radius_size));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}
// Constructor with position, velocity, and mass
Body::Body(const sf::Vector2<double>& position, const sf::Vector2<double>& velocity, double mass)
	: radius_size(5.0), mass(mass), position(position), velocity(velocity), acceleration(sf::Vector2<double>(0, 0))
{
	shape.setRadius(static_cast<float>(radius_size));
	shape.setOrigin(static_cast<float>(radius_size), static_cast<float>(radius_size));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}



// Draw method (from sf::Drawable)
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

void Body::updateAcceleration(std::vector<Body>& bodies)
{
    acceleration = sf::Vector2<double>(0, 0);
    for (size_t i = 0; i < bodies.size(); ++i)
    {
        if (&bodies[i] != this)
        {
            acceleration += gravity::accelerationVector(*this, bodies[i]);
        }
    }
}


// Velocity update using acceleration
void Body::updateVelocity(double deltaTime)
{
    velocity += acceleration * deltaTime;
}

// Position update using velocity
void Body::updatePosition(double deltaTime)
{
    position += velocity * deltaTime;
    shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

void Body::setColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

// Getters
double Body::getRadius_Size() const { return radius_size; }
double Body::getMass() const { return mass; }
sf::Vector2<double> Body::getPosition() const { return position; }
sf::Vector2<double> Body::getVelocity() const { return velocity; }
sf::Vector2<double> Body::getAcceleration() const { return acceleration; }

// Setters
void Body::setRadius(double r) { radius_size = r; }
void Body::setPosition(const sf::Vector2<double>& pos)
{
    position = pos;
    shape.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
}
void Body::setVelocity(const sf::Vector2<double>& vel) { velocity = vel; }
void Body::setAcceleration(const sf::Vector2<double>& acc) { acceleration = acc; }
void Body::setMass(double m) { mass = m; }
