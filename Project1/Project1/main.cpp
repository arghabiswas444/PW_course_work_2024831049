#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My First Code");
    window.setFramerateLimit(60);

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Red);

    circle.setOrigin({ circle.getRadius(), circle.getRadius() });
    circle.setPosition(sf::Vector2f(
        window.getSize().x / 2.f,
        window.getSize().y / 2.f
    ));

    int r = 150;
    int g = 100;
    int b = 150;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        window.clear(sf::Color(r, g, b));
        window.draw(circle);
        window.display();
    }

    return 0;
}



