#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Labirynth");
    window.setFramerateLimit(144);


    const float grid_size = 50.f;

    //Loading all textures
    sf::Texture texture1;
    if (!texture1.loadFromFile("guy.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture texture_back;
    if (!texture_back.loadFromFile("grass.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture_back.setRepeated(true);

    sf::Texture texture2;
    if (!texture2.loadFromFile("wall.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture2.setRepeated(true);

    //Creating sprites
    sf::Sprite dude;
    dude.setTexture(texture1);

    sf::Sprite background;
    background.setTexture(texture_back);
    background.setScale(1, 1);
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    sf::Sprite wall1;
    wall1.setPosition(grid_size, grid_size * 2);
    wall1.setTexture(texture2);
    wall1.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size, grid_size * 7));

    sf::Sprite wall2;
    wall2.setPosition(grid_size * 3, grid_size * 2);
    wall2.setTexture(texture2);
    wall2.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 2, grid_size));

    sf::Sprite wall3;
    wall3.setPosition(grid_size * 3, grid_size * 2);
    wall3.setTexture(texture2);
    wall3.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 2, grid_size));

    sf::Sprite wall4;
    wall4.setPosition(grid_size * 15, grid_size * 2);
    wall4.setTexture(texture2);
    wall4.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size* 5, grid_size * 12));


    const float movement_speed = 250.f;
    sf::Vector2f velocity;



    while(window.isOpen()){
        sf::Clock clock;
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        window.draw(background);
        window.draw(dude);
        window.draw(wall1);
        //window.draw(wall2);
        //window.draw(wall3);
        window.draw(wall4);
        window.display();

        //Controlling movement
        elapsed = clock.getElapsedTime();
        float dt = elapsed.asSeconds();

        velocity.x = 0;
        velocity.y = 0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            velocity.y += -movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            velocity.y += movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += movement_speed * dt;

        dude.move(velocity);

    }
    return 0;
}
