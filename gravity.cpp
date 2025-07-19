#include "gravity.h"
#include "Body.h"
#include <cmath>
#include <iostream>

using Vector2d = sf::Vector2<double>;

double gravity::Force(Body& c1, Body& c2)
{
    double r = distance(c1, c2);
    double m1 = c1.getMass();
    double m2 = c2.getMass();
    if (r == 0.0) return 0.0;
    return (getG() * m1 * m2) / square(r);
}

Vector2d gravity::ForceVector(Body& c1, Body& c2)
{
    double F = Force(c1, c2);
    Vector2d normalizedDir = normalizedDirection(c1, c2);
    return Vector2d(normalizedDir.x * F, normalizedDir.y * F);
}

double gravity::acceleration(Body& c1, Body& c2)
{
    double F = Force(c1, c2);
    double m1 = c1.getMass();
    return m1 == 0.0 ? 0.0 : F / m1;
}

Vector2d gravity::accelerationVector(Body& c1, Body& c2)
{
    double r = distance(c1, c2);
    if (r == 0.0) return Vector2d(0.0, 0.0);
    Vector2d Fv = ForceVector(c1, c2);
    double m1 = c1.getMass();
    return Vector2d(Fv.x / m1, Fv.y / m1);
}

double gravity::distance(Body& c1, Body& c2)
{
    return std::sqrt(square(c1.getPosition().x - c2.getPosition().x) +
        square(c1.getPosition().y - c2.getPosition().y));
}

Vector2d gravity::direction(Body& c1, Body& c2)
{
    return Vector2d(c2.getPosition().x - c1.getPosition().x,
        c2.getPosition().y - c1.getPosition().y);
}

Vector2d gravity::normalizedDirection(Body& c1, Body& c2)
{
    double r = distance(c1, c2);
    if (r == 0.0) return Vector2d(0.0, 0.0);
    Vector2d dir = direction(c1, c2);
    return Vector2d(dir.x / r, dir.y / r);
}

void gravity::interaction(std::vector<Body>& bodies, double dt)
{
    std::vector<Vector2d> positions(bodies.size(), Vector2d(0.0, 0.0));
    std::vector<Vector2d> accelerations(bodies.size(), Vector2d(0.0, 0.0));
    std::vector<Vector2d> velocities(bodies.size(), Vector2d(0.0, 0.0));
	int n = static_cast<int>(bodies.size());

    for (int i = 0; i < n; i++)
    {
        Vector2d F_net = gravity::ForceVectorSum(bodies, i);
        Vector2d a = F_net / bodies[i].getMass();
		accelerations[i] = a;
    }
	for (int i = 0; i < n; ++i)
	{
		velocities[i] = bodies[i].getVelocity() + accelerations[i] * dt;
		positions[i] =  bodies[i].getPosition() + velocities[i] * dt;
	}


    for (int i = 0; i < n; ++i)
    {
        bodies[i].setPosition(positions[i]);
        bodies[i].setAcceleration(accelerations[i]);
        bodies[i].setVelocity(velocities[i]);
    }
}

Vector2d gravity::ForceVectorSum(std::vector<Body>& bodies, int k)
{
    if (k < 0 || k >= static_cast<int>(bodies.size())) return Vector2d(0.0, 0.0);

    Vector2d sigmaF(0.0, 0.0);
    for (int i = 0; i < static_cast<int>(bodies.size()); i++)
    {
        if (k == i) continue;
        sigmaF += gravity::ForceVector(bodies[k], bodies[i]);
    }

    return sigmaF;
}

double gravity::KE(Body& body)
{
    Vector2<double> v = body.getVelocity();
    return 0.5 * body.getMass() * ((v.x * v.x) + (v.y* v.y)); //   KE= 1/2 * m * v^2
}

double gravity::KE(std::vector<Body>& bodies)
{
    double KEtotal = 0;
    for (int i = 0; i < bodies.size(); i++)
    {
		KEtotal += KE(bodies[i]);
    }
	return KEtotal;
}

double gravity::Etotal(std::vector<Body>& bodies)
{
	double U = GPE(bodies);
	double K = KE(bodies);
	return U + K;
}

double gravity::GPE(std::vector<Body>& bodies)
{
    double GPE = 0.0;
    for (int i = 0; i < bodies.size(); i++)
    {
        for (int j = i + 1; j < bodies.size(); j++)
        {
            double rij = distance(bodies[i], bodies[j]);
            if (rij != 0.0)
            {
                GPE += -G * bodies[i].getMass() * bodies[j].getMass() / rij;
            }
        }
    }
    return GPE;
}


