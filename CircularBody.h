#pragma once  
#include <SFML/Graphics.hpp>  
#include <string>  
#include <cmath>  
#include <corecrt_math_defines.h>
using std::string;
using std::endl;
using std::vector;
using sf::Drawable;

class CircularBody : public sf::Drawable
{
private:
    string name;
    double r;
    double T;
    double radius;
    double angularVelocity = (2 * M_PI) / T;
    double currentAngle;
    double a;
    double b;
    sf::Vector2<double> center;
    sf::CircleShape shape;

public:
    CircularBody(const string& name,
        double T,
        double radius, double a, double b,
        sf::Vector2<double> center,
        double initialAngle = 0)
        : name(name), T(T),
        radius(radius), currentAngle(initialAngle), center(center), a(a), b(b)
    {
        shape.setRadius(static_cast<float>(radius));
        shape.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
        shape.setFillColor(sf::Color::Blue);
    }

    void update(double deltaTime)
    {
        currentAngle += deltaTime * angularVelocity;
        if (currentAngle > 2 * M_PI)
            currentAngle -= 2 * M_PI;

        double x = center.x + a * cos(currentAngle);
        double y = center.y + b * sin(currentAngle);
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    void setPosition(double x, double y) {
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    string getName() const { return name; }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void setColor(const sf::Color& color) {
        shape.setFillColor(color);
    }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape, states);
    }
};
