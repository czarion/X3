#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>

// Function to parse sensor data from binary format
std::vector<sf::Vector2f> parseSensorData(const std::string& filePath, float radius) {
    std::vector<sf::Vector2f> objects;
    std::ifstream sensorData(filePath, std::ios::binary);

    if (!sensorData.is_open()) {
        std::cerr << "Failed to open sensor data file." << std::endl;
        return objects;
    }

    float angle, distance;
    while (sensorData.read(reinterpret_cast<char*>(&angle), sizeof(float)) &&
           sensorData.read(reinterpret_cast<char*>(&distance), sizeof(float))) {
        if (distance <= radius) {
            float x = std::cos(angle * M_PI / 180.f) * distance;
            float y = std::sin(angle * M_PI / 180.f) * distance;
            objects.emplace_back(x, y);
        }
    }

    return objects;
}

int main() {
    const int windowSize = 800;          // Window dimensions (square)
    const float radarRadius = 375.f;    // Radar circle radius
    const std::string sensorFile = "sensor_data.bin"; // Path to sensor data

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Live Radar Simulation");
    window.setFramerateLimit(60);

    // Radar circle
    sf::CircleShape radar(radarRadius);
    radar.setFillColor(sf::Color::Black);
    radar.setOutlineColor(sf::Color::Green);
    radar.setOutlineThickness(2.f);
    radar.setOrigin(radarRadius, radarRadius);
    radar.setPosition(windowSize / 2, windowSize / 2);

    // Radar sweep line
    sf::RectangleShape sweep(sf::Vector2f(radarRadius, 2.f));
    sweep.setFillColor(sf::Color::Green);
    sweep.setOrigin(0.f, 1.f);
    sweep.setPosition(windowSize / 2, windowSize / 2);

    float angle = 0.f; // Starting angle of the sweep

    // Fading trail for the sweep line
    std::deque<sf::VertexArray> trail;
    const int maxTrailLength = 50;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Read objects from sensor data
        auto objects = parseSensorData(sensorFile, radarRadius);

        // Update the sweep angle
        angle += 0.36f; // 50 Hz sweep (360° in 2.5 seconds)
        if (angle > 360.f)
            angle -= 360.f;
        sweep.setRotation(angle);

        // Create a new trail segment
        sf::VertexArray segment(sf::Lines, 2);
        segment[0].position = sf::Vector2f(windowSize / 2, windowSize / 2);
        segment[0].color = sf::Color::Green;
        segment[1].position = sf::Vector2f(
            windowSize / 2 + std::cos(angle * M_PI / 180.f) * radarRadius,
            windowSize / 2 + std::sin(angle * M_PI / 180.f) * radarRadius
        );
        segment[1].color = sf::Color::Green;
        trail.push_back(segment);

        // Limit trail length
        if (trail.size() > maxTrailLength) {
            trail.pop_front();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the grid
        sf::Color gridColor(0, 128, 0, 100);
        for (int i = 0; i <= windowSize; i += 25) { // Increase grid density
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i, 0), gridColor),
                sf::Vertex(sf::Vector2f(i, windowSize), gridColor)
            };
            window.draw(line, 2, sf::Lines);

            sf::Vertex line2[] = {
                sf::Vertex(sf::Vector2f(0, i), gridColor),
                sf::Vertex(sf::Vector2f(windowSize, i), gridColor)
            };
            window.draw(line2, 2, sf::Lines);
        }

        // Draw radar circle
        window.draw(radar);

        // Draw objects as blinking dots
        for (const auto& obj : objects) {
            sf::CircleShape dot(5.f);
            sf::Uint8 alpha = static_cast<sf::Uint8>(128 + 127 * std::sin(angle * M_PI / 180.f)); // Blinking effect
            dot.setFillColor(sf::Color(0, 255, 0, alpha));
            dot.setOrigin(2.5f, 2.5f);
            dot.setPosition(windowSize / 2 + obj.x, windowSize / 2 + obj.y);
            window.draw(dot);
        }

        // Draw the trail
        int alpha = 255;
        for (auto& t : trail) {
            t[0].color.a = alpha;
            t[1].color.a = alpha;
            alpha = std::max(0, alpha - 255 / maxTrailLength);
            window.draw(t);
        }

        // Draw the radar sweep line
        window.draw(sweep);

        // Display the contents
        window.display();
    }

    return 0;
}
