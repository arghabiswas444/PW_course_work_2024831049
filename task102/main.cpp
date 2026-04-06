#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Growing Circle");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);

    float radius = 50.f;
    sf::Clock clock;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();


        radius += 80.f * clock.restart().asSeconds();


        if (radius >= 300.f)
            radius = 50.f;


        circle.setRadius(radius);
        circle.setOrigin({ radius, radius });
        circle.setPosition({ 400.f, 300.f });

        window.clear(sf::Color(150, 100, 150));
        window.draw(circle);
        window.display();
    }
}