#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Body.h"


using sf::Vector2;


class gravity
{
private:
    static constexpr double G =1;

    static double square(double value)
    {
        return value * value;
    }

public:
    static double Force(Body& c1, Body& c2);
    static Vector2<double> ForceVector(Body& c1, Body& c2);
    static Vector2<double> ForceVectorSum(std::vector<Body>& bodies, int k);
    static double acceleration(Body& c1, Body& c2);
    static Vector2<double> accelerationVector(Body& c1, Body& c2);
    static double distance(Body& c1, Body& c2);
    static Vector2<double> direction(Body& c1, Body& c2);
    static Vector2<double> normalizedDirection(Body& c1, Body& c2);
    static double getG() { return G; }

    static void interaction(std::vector<Body>& bodies, double dt);

    static double GPE(std::vector<Body>& bodies);
    static double KE(Body& body);
    

    static double KE(std::vector<Body>& bodies);
	
    static double Etotal(std::vector<Body>& bodies);
    
};
