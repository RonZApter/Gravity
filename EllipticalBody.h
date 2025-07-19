#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <corecrt_math_defines.h>
using std::cos;
using std::sin;
using std::string;
using sf::Color;
using sf::Vector2f;
using sf::RenderTarget;
using sf::RenderStates;

class EllipticalBody : public sf::Drawable 
{
private:
    std::string name;
    double a;
    double b;
    double orbitalPeriod;
    double angularVelocity;
    double currentAngle;
    double radius;
    sf::Vector2<double> center;
    sf::CircleShape shape;

public:
    EllipticalBody(const string& name,
        double semiMajorAxis,
        double semiMinorAxis,
        double orbitalPeriod,
        double radius,
        sf::Vector2<double> center)
        : name(name),
        a(semiMajorAxis),
        b(semiMinorAxis),
        orbitalPeriod(orbitalPeriod),
        radius(radius),
        center(center),
        currentAngle(0.0)
    {
        angularVelocity = 2 * M_PI / orbitalPeriod;
        shape.setRadius(static_cast<float>(radius));
        shape.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
        shape.setFillColor(Color::Green);
    }

    void update(double deltaTime) {
        currentAngle += angularVelocity * deltaTime;
        if (currentAngle > 2 * M_PI)
            currentAngle -= 2 * M_PI;

        double x = center.x + a * cos(currentAngle);
        double y = center.y + b * sin(currentAngle);
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    virtual void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(shape, states);
    }
};
