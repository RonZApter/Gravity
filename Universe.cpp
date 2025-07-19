#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Body.h"
#include "gravity.h"
#include <iostream>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using sf::Vector2;
using std::vector;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

void threeBodyProblem()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Three-Body Problem");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    Body body1({ WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 }, { 0, 40 }, 1000);
    body1.setRadius(10);
    body1.setColor(sf::Color::Red);
    bodies.push_back(body1);

    Body body2({ WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2 }, { 0, -40 }, 1000);
    body2.setRadius(10);
    body2.setColor(sf::Color::Green);
    bodies.push_back(body2);

    Body body3({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 150 }, { -40, 0 }, 1000);
    body3.setRadius(10);
    body3.setColor(sf::Color::Blue);
    bodies.push_back(body3);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double dt = clock.restart().asSeconds();

        for (auto& body : bodies)
            body.updateAcceleration(bodies);

        for (auto& body : bodies)
        {
            body.updateVelocity(dt);
            body.updatePosition(dt);
        }

        window.clear();
        for (const auto& body : bodies)
            window.draw(body);
        window.display();
    }
}

void swirlingGalaxy()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Swirling Galaxy");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    Body blackHole({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 1000000);
    blackHole.setRadius(30);
    blackHole.setColor(sf::Color::Black);
    bodies.push_back(blackHole);

    for (int i = 0; i < 1000; ++i)
    {
        double angle = i * 0.15;
        double radius = 50 + i * 0.4;

        double x = WINDOW_WIDTH / 2 + radius * cos(angle);
        double y = WINDOW_HEIGHT / 2 + radius * sin(angle);
        Vector2<double> pos = { x, y };

        Vector2<double> tangential = { -sin(angle) * 15, cos(angle) * 15 };
        double mass = 0.2 + (i % 5) * 0.1;

        Body star(pos, tangential, mass);
        star.setRadius(2);
        star.setColor(sf::Color(255 - (i % 255), i % 255, 200));
        bodies.push_back(star);
    }

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double dt = clock.restart().asSeconds();

        for (auto& body : bodies)
            body.updateAcceleration(bodies);

        for (auto& body : bodies)
        {
            body.updateVelocity(dt);
            body.updatePosition(dt);
        }

        window.clear();
        for (const auto& body : bodies)
            window.draw(body);
        window.display();
    }
}

void magneticSpiralChaos()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Magnetic Spiral Chaos");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    Body blackHole({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 3000000);
    blackHole.setRadius(35);
    blackHole.setColor(sf::Color::Black);
    bodies.push_back(blackHole);

    for (int i = 0; i < 900; ++i)
    {
        double r = 70 + (i * 0.6);
        double spiral = 0.2 * i + sin(i * 0.05);
        double x = WINDOW_WIDTH / 2 + r * cos(spiral);
        double y = WINDOW_HEIGHT / 2 + r * sin(spiral);

        Vector2<double> pos(x, y);
        Vector2<double> vel(-sin(spiral) * 18, cos(spiral) * 18);
        Body star(pos, vel, 0.4);
        star.setRadius(2);
        star.setColor(sf::Color(100 + rand() % 155, 100 + rand() % 155, 255));
        bodies.push_back(star);
    }

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double dt = clock.restart().asSeconds();

        for (auto& body : bodies)
            body.updateAcceleration(bodies);

        for (auto& body : bodies)
        {
            body.updateVelocity(dt);
            body.updatePosition(dt);
        }

        window.clear();
        for (const auto& body : bodies)
            window.draw(body);
        window.display();
    }
}

void chaoticSpiral()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaotic Spiral");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    // Central attractor
    Body blackHole({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 2000000);
    blackHole.setRadius(40);
    blackHole.setColor(sf::Color::Black);
    bodies.push_back(blackHole);

    // Add particles in a chaotic spiral pattern
    for (int i = 0; i < 800; ++i)
    {
        double radius = 80 + i * 0.5;
        // Spiral with some chaos added by a sine wave on the angle
        double angle = 0.25 * i + std::sin(i * 0.1) * 0.5;

        double x = WINDOW_WIDTH / 2 + radius * std::cos(angle);
        double y = WINDOW_HEIGHT / 2 + radius * std::sin(angle);

        Vector2<double> pos(x, y);

        // Velocity roughly tangential but with chaotic perturbation
        double vx = -std::sin(angle) * 20 + (std::rand() % 100 - 50) / 10.0;
        double vy = std::cos(angle) * 20 + (std::rand() % 100 - 50) / 10.0;
        Vector2<double> vel(vx, vy);

        Body star(pos, vel, 0.3);
        star.setRadius(2);
        // Color shifts between blue and purple with some randomness
        star.setColor(sf::Color(50 + std::rand() % 100, 50, 150 + std::rand() % 105));
        bodies.push_back(star);
    }

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        // Update accelerations
        for (auto& body : bodies)
            body.updateAcceleration(bodies);

        // Update velocities and positions
        for (auto& body : bodies)
        {
            body.updateVelocity(dt);
            body.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& body : bodies)
            window.draw(body);
        window.display();
    }
}
void latticePattern()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lattice Pattern Simulation");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    // Parameters for grid
    int rows = 20;
    int cols = 30;
    double spacingX = WINDOW_WIDTH / (cols + 1);
    double spacingY = WINDOW_HEIGHT / (rows + 1);

    // Create bodies in a grid lattice
    for (int r = 1; r <= rows; ++r)
    {
        for (int c = 1; c <= cols; ++c)
        {
            double x = c * spacingX;
            double y = r * spacingY;

            Vector2<double> pos(x, y);

            // Random small velocity for some dynamic behavior
            double vx = (rand() % 20 - 10) * 0.5;
            double vy = (rand() % 20 - 10) * 0.5;
            Vector2<double> vel(vx, vy);

            double mass = 1.0;

            Body body(pos, vel, mass);
            body.setRadius(4);

            // Color varies by position for nice gradient effect
            sf::Uint8 red = static_cast<sf::Uint8>(255 * r / rows);
            sf::Uint8 blue = static_cast<sf::Uint8>(255 * c / cols);
            body.setColor(sf::Color(red, 50, blue));

            bodies.push_back(body);
        }
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        for (auto& body : bodies)
            body.updateAcceleration(bodies);

        for (auto& body : bodies)
        {
            body.updateVelocity(dt);
            body.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& body : bodies)
            window.draw(body);
        window.display();
    }
}

void simulateAtomsCloud()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Atoms Cloud Simulation");
    window.setFramerateLimit(60);

    // Constants
    const double CHARGE_PROTON = +1.0;
    const double CHARGE_NEUTRON = 0.0;
    const double CHARGE_ELECTRON = -1.0;

    const double MASS_PROTON = 1.0;
    const double MASS_NEUTRON = 1.0;
    const double MASS_ELECTRON = 0.1;

    const double COULOMB_K = 9000.0;
    const double NUCLEAR_FORCE_STRENGTH = 700.0;
    const double NUCLEAR_RANGE = 20.0;

    // Store all particles of all atoms here
    vector<Body> particles;
    vector<double> charges; // parallel array for charges

    int atomCount = 10;

    // For each atom:
    for (int atomIdx = 0; atomIdx < atomCount; ++atomIdx)
    {
        // Center position for nucleus (random in window, away from edges)
        double cx = 100 + rand() % (WINDOW_WIDTH - 200);
        double cy = 100 + rand() % (WINDOW_HEIGHT - 200);
        Vector2<double> centerPos(cx, cy);

        // Nucleus: ~5 protons + 5 neutrons tightly clustered
        int protonsPerAtom = 5;
        int neutronsPerAtom = 5;
        double nucleusRadius = 15.0;

        // Add protons randomly in nucleus radius
        for (int p = 0; p < protonsPerAtom; ++p)
        {
            double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
            double dist = ((double)rand() / RAND_MAX) * nucleusRadius * 0.6;
            Vector2<double> pos = { cx + dist * cos(angle), cy + dist * sin(angle) };
            Vector2<double> vel = { 0, 0 };
            particles.emplace_back(pos, vel, MASS_PROTON);
            charges.push_back(CHARGE_PROTON);
            particles.back().setRadius(6.f);
            particles.back().setColor(sf::Color::Red);
        }

        // Add neutrons randomly in nucleus radius
        for (int n = 0; n < neutronsPerAtom; ++n)
        {
            double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
            double dist = ((double)rand() / RAND_MAX) * nucleusRadius * 0.6;
            Vector2<double> pos = { cx + dist * cos(angle), cy + dist * sin(angle) };
            Vector2<double> vel = { 0, 0 };
            particles.emplace_back(pos, vel, MASS_NEUTRON);
            charges.push_back(CHARGE_NEUTRON);
            particles.back().setRadius(6.f);
            particles.back().setColor(sf::Color(128, 128, 128));
        }

        // Electrons orbiting nucleus, spaced evenly, radius ~50 from center
        int electronsPerAtom = protonsPerAtom; // neutral atom
        double electronOrbitRadius = 50.0;

        for (int e = 0; e < electronsPerAtom; ++e)
        {
            double angle = 2 * M_PI * e / electronsPerAtom;
            Vector2<double> pos = { cx + electronOrbitRadius * cos(angle), cy + electronOrbitRadius * sin(angle) };
            // velocity tangential for orbit
            Vector2<double> vel = { -50 * sin(angle), 50 * cos(angle) };
            particles.emplace_back(pos, vel, MASS_ELECTRON);
            charges.push_back(CHARGE_ELECTRON);
            particles.back().setRadius(4.f);
            particles.back().setColor(sf::Color::Blue);
        }
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        // Reset accelerations (assuming Body has setAcceleration or similar)
        for (auto& p : particles)
            p.setAcceleration({ 0, 0 });

        // Calculate forces pairwise
        for (size_t i = 0; i < particles.size(); ++i)
        {
            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                Vector2<double> diff = { particles[j].getPosition().x - particles[i].getPosition().x,
                                         particles[j].getPosition().y - particles[i].getPosition().y };

                double distSq = diff.x * diff.x + diff.y * diff.y;
                double dist = std::sqrt(distSq);
                if (dist < 1) dist = 1;

                // Coulomb force
                double F_coulomb = COULOMB_K * charges[i] * charges[j] / distSq;
                Vector2<double> force_coulomb = { F_coulomb * diff.x / dist, F_coulomb * diff.y / dist };

                particles[i].addForce(force_coulomb);
                particles[j].addForce({ -force_coulomb.x, -force_coulomb.y });

                // Nuclear force if both nucleons (p or n) and close enough
                bool iNucleon = (charges[i] != CHARGE_ELECTRON);
                bool jNucleon = (charges[j] != CHARGE_ELECTRON);
                if (iNucleon && jNucleon && dist < NUCLEAR_RANGE)
                {
                    double F_nuclear = NUCLEAR_FORCE_STRENGTH / distSq;
                    Vector2<double> force_nuclear = { -F_nuclear * diff.x / dist, -F_nuclear * diff.y / dist };

                    particles[i].addForce(force_nuclear);
                    particles[j].addForce({ -force_nuclear.x, -force_nuclear.y });
                }
            }
        }

        // Update velocities and positions
        for (auto& p : particles)
        {
            p.updateVelocity(dt);
            p.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& p : particles)
            window.draw(p);
        window.display();
    }


}
void explodingSupernova()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Exploding Supernova");
    window.setFramerateLimit(60);

    vector<Body> particles;

    Vector2<double> center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    double mass = 0.5;

    for (int i = 0; i < 800; ++i)
    {
        double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
        double speed = 100 + rand() % 100;

        Vector2<double> vel = { speed * cos(angle), speed * sin(angle) };
        Vector2<double> pos = { center.x, center.y };

        Body p(pos, vel, mass);
        p.setRadius(2);
        p.setColor(sf::Color(255, rand() % 255, 0));
        particles.push_back(p);

    }

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        for (auto& p : particles)
			p.updatePosition(dt);

        window.clear();
        for (const auto& p : particles)
            window.draw(p);
        window.display();
    }
}
void binaryStarDance()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Binary Star Dance");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    Vector2<double> center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    double mass = 20000;

    // Binary stars
    Body star1({ center.x - 100, center.y }, { 0, 30 }, mass);
    star1.setRadius(20);
    star1.setColor(sf::Color::White);
    bodies.push_back(star1);

    Body star2({ center.x + 100, center.y }, { 0, -30 }, mass);
    star2.setRadius(20);
    star2.setColor(sf::Color::Red);
    bodies.push_back(star2);

    // Add small orbiters
    for (int i = 0; i < 300; ++i)
    {
        double angle = i * 0.1;
        double r = 250 + (rand() % 100);

        double x = center.x + r * cos(angle);
        double y = center.y + r * sin(angle);
        Vector2<double> pos(x, y);

        Vector2<double> vel(-sin(angle) * 50, cos(angle) * 50);
        Body orbiter(pos, vel, 0.2);
        orbiter.setRadius(2);
        orbiter.setColor(sf::Color::Green);
        bodies.push_back(orbiter);
    }

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        for (auto& b : bodies)
            b.updateAcceleration(bodies);

        for (auto& b : bodies)
        {
            b.updateVelocity(dt);
            b.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& b : bodies)
            window.draw(b);
        window.display();
    }
}
void orbitalRing()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Orbital Ring");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    Body planet({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 100000);
    planet.setRadius(25);
    planet.setColor(sf::Color::Yellow);
    bodies.push_back(planet);

    int ringParticles = 300;
    double radius = 200;

    for (int i = 0; i < ringParticles; ++i)
    {
        double angle = 2 * M_PI * i / ringParticles;
        double x = WINDOW_WIDTH / 2 + radius * cos(angle);
        double y = WINDOW_HEIGHT / 2 + radius * sin(angle);
        Vector2<double> pos(x, y);

        Vector2<double> vel(-sin(angle) * 50, cos(angle) * 50);

        Body p(pos, vel, 0.5);
        p.setRadius(2);
        p.setColor(sf::Color::Cyan);
        bodies.push_back(p);
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        for (auto& b : bodies)
            b.updateAcceleration(bodies);

        for (auto& b : bodies)
        {
            b.updateVelocity(dt);
            b.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& b : bodies)
            window.draw(b);
        window.display();
    }
}
void galacticCollapse()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Galactic Collapse");
    window.setFramerateLimit(60);

    vector<Body> bodies;

    // Massive central black hole
    Body blackHole({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 500000);
    blackHole.setRadius(30);
    blackHole.setColor(sf::Color::Black);
    bodies.push_back(blackHole);

    // Create galaxy
    int starCount = 1200;
    for (int i = 0; i < starCount; ++i)
    {
        double angle = i * 0.07;
        double radius = 100 + (rand() % 400);
        double x = WINDOW_WIDTH / 2 + radius * cos(angle);
        double y = WINDOW_HEIGHT / 2 + radius * sin(angle);
        Vector2<double> pos(x, y);

        double tangentialSpeed = std::sqrt(500000 / radius);
        Vector2<double> vel(-sin(angle) * tangentialSpeed, cos(angle) * tangentialSpeed);

        Body star(pos, vel, 0.3);
        star.setRadius(2);
        star.setColor(sf::Color(200, 200, 255));
        bodies.push_back(star);
    }

    sf::Clock clock;
    double timeAccumulator = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();
        timeAccumulator += dt;

        // After 10 seconds, the black hole starts gaining mass exponentially
        if (timeAccumulator > 10)
        {
            double massBoost = 500000 * std::exp((timeAccumulator - 10) * 0.5);
            bodies[0].setMass(500000 + massBoost);

            // Change colors of stars to red as they fall in
            for (size_t i = 1; i < bodies.size(); ++i)
            {
                bodies[i].setColor(sf::Color(255, 50, 50));
            }
        }

        for (auto& b : bodies)
            b.updateAcceleration(bodies);

        for (auto& b : bodies)
        {
            b.updateVelocity(dt);
            b.updatePosition(dt);
        }

        window.clear(sf::Color::Black);
        for (const auto& b : bodies)
            window.draw(b);
        window.display();
    }
}
void electricDipoleOscillation()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Electric Dipole Oscillation");
    window.setFramerateLimit(60);

    double chargeMagnitude = 5.0;
    double mass = 10.0;

    Vector2<double> pos1(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
    Vector2<double> pos2(WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2);

    Vector2<double> vel1(0, 0);
    Vector2<double> vel2(0, 0);

    Body particle1(pos1, vel1, mass);
    Body particle2(pos2, vel2, mass);

    particle1.setRadius(15);
    particle2.setRadius(15);

    particle1.setColor(sf::Color::Red);
    particle2.setColor(sf::Color::Blue);

    double k = 9000; 

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        double dt = clock.restart().asSeconds();

        Vector2<double> diff = particle2.getPosition() - particle1.getPosition();
        double distSq = diff.x * diff.x + diff.y * diff.y;
        double dist = std::sqrt(distSq);

        if (dist < 1) dist = 1;

        Vector2<double> forceDir = diff / dist;

        Vector2<double> force = forceDir * (k * chargeMagnitude * chargeMagnitude / distSq);

        Vector2<double> acc1 = force / mass;  
        Vector2<double> acc2 = -force / mass;  

     
        particle1.setAcceleration(acc1);
        particle2.setAcceleration(acc2);

        particle1.updateVelocity(dt);
        particle1.updatePosition(dt);

        particle2.updateVelocity(dt);
        particle2.updatePosition(dt);

        window.clear(sf::Color::Black);

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(particle1.getPosition().x, particle1.getPosition().y), sf::Color::White),
            sf::Vertex(sf::Vector2f(particle2.getPosition().x, particle2.getPosition().y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);

        window.draw(particle1);
        window.draw(particle2);
        window.display();
    }
}


int main()
{
    while (true)
    {
        std::cout << "\nChoose simulation to run:\n";
        std::cout << "1. Binary Star Dance\n";
        std::cout << "2. Swirling Galaxy\n";
        std::cout << "3. Magnetic Spiral Chaos\n";
        std::cout << "4. Chaotic Spiral\n";
        std::cout << "5. Atoms Cloud Simulation\n";
		std::cout << "6. Lattice Pattern Simulation\n";
		std::cout << "7. Exploding Supernova\n";
		std::cout << "8. Orbital Ring\n";
		std::cout << "9. Galactic Collapse\n";
		std::cout << "10. Electric Dipole Oscillation\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter number: ";

        int choice;
        std::cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            binaryStarDance();
            break;
        case 2:
            swirlingGalaxy();
            break;
        case 3:
            magneticSpiralChaos();
            break;
        case 4:
            chaoticSpiral();
            break;
        case 5:
            simulateAtomsCloud();
            break;
		case 6:
			latticePattern();
			break;
		case 7:
			explodingSupernova();
			break;
		case 8:
			orbitalRing();
			break;
		case 9:
			galacticCollapse();
			break;
		case 10:
			electricDipoleOscillation();
			break;	
        }
        system("cls");
    }

    std::cout << "Program exited.\n";
    return 0;
}
