#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

// Function to create random objects in the radar's vicinity
std::vector<sf::Vector2f> generateObjects(int count, float radius) {
    std::vector<sf::Vector2f> objects;
    for (int i = 0; i < count; ++i) {
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
        float distance = static_cast<float>(rand()) / RAND_MAX * radius;
        objects.emplace_back(std::cos(angle) * distance, std::sin(angle) * distance);
    }
    return objects;
}

int main() {
    const int windowSize = 600;          // Window dimensions (square)
    const float radarRadius = 250.f;    // Radar circle radius
    const int numObjects = 10;          // Number of objects to display

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Radar Simulation");
    window.setFramerateLimit(60);

    // Radar circle
    sf::CircleShape radar(radarRadius);
    radar.setFillColor(sf::Color::Black);
    radar.setOutlineColor(sf::Color::Green);
    radar.setOutlineThickness(2.f);
    radar.setOrigin(radarRadius, radarRadius);
    radar.setPosition(windowSize / 2, windowSize / 2);

    // Objects on the radar
    auto objects = generateObjects(numObjects, radarRadius);

    // Radar sweep line
    sf::RectangleShape sweep(sf::Vector2f(radarRadius, 2.f));
    sweep.setFillColor(sf::Color::Green);
    sweep.setOrigin(0.f, 1.f);
    sweep.setPosition(windowSize / 2, windowSize / 2);

    float angle = 0.f; // Starting angle of the sweep

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the sweep angle
        angle += 0.5f; // Adjust speed of the sweep here
        if (angle > 360.f)
            angle -= 360.f;
        sweep.setRotation(angle);

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw radar components
        window.draw(radar);

        // Draw objects as small circles
        for (const auto& obj : objects) {
            sf::CircleShape dot(5.f);
            dot.setFillColor(sf::Color::Green);
            dot.setOrigin(2.5f, 2.5f);
            dot.setPosition(windowSize / 2 + obj.x, windowSize / 2 + obj.y);
            window.draw(dot);
        }

        // Draw the radar sweep line
        window.draw(sweep);

        // Display the contents
        window.display();
    }

    return 0;
}
