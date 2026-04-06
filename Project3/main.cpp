#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const float W = 800, H = 600, R1 = 30, R2 = 25;

bool hitting(sf::CircleShape& a, sf::CircleShape& b) {
    auto d = a.getPosition() - b.getPosition();
    return std::sqrt(d.x*d.x + d.y*d.y) <R1+ R2;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ (unsigned)W,(unsigned)H }), "Collision");
    window.setFramerateLimit(60);

    sf::CircleShape c1(R1); c1.setOrigin({ R1,R1 }); c1.setPosition({ R1, H / 2 });
    sf::CircleShape c2(R2); c2.setOrigin({ R2,R2 }); c2.setPosition({ W / 2, R2 });

    float flash = 0.f;
    sf::Clock clk;

    while (window.isOpen()) {
        while (const std::optional e = window.pollEvent())
            if (e->is<sf::Event::Closed>()) window.close();

        float dt = clk.restart().asSeconds();

        c1.move({ 220.f * dt, 0 });
        if (c1.getPosition().x - R1 > W) c1.setPosition({ -R1, H / 2 });

        auto p = c2.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    p.y -= 260 * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  p.y += 260 * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  p.x -= 260 * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) p.x += 260 * dt;
        p.x = std::max(R2, std::min(W - R2, p.x));
        p.y = std::max(R2, std::min(H - R2, p.y));
        c2.setPosition(p);

        if (hitting(c1, c2)) flash = 0.25f;
        flash -= dt;

        bool hit = flash > 0;
        c1.setFillColor(hit ? sf::Color(255, 80, 0) : sf::Color::Cyan);
        c2.setFillColor(hit ? sf::Color(255, 80, 0) : sf::Color::Red);
        c1.setScale(hit ? sf::Vector2f{ 1.3f,1.3f } : sf::Vector2f{ 1.f,1.f });
        c2.setScale(hit ? sf::Vector2f{ 1.3f,1.3f } : sf::Vector2f{ 1.f,1.f });

        window.clear(hit ? sf::Color(120, 30, 0) : sf::Color(20, 20, 30));
        window.draw(c1); window.draw(c2);
        window.display();
    }
}