#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

bool isColliding(const sf::Sprite& dude_s, const sf::Sprite& wall_s){
    return dude_s.getGlobalBounds().intersects(wall_s.getGlobalBounds());
}

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

    sf::Texture texture_g;
    if (!texture_g.loadFromFile("goal.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //Creating sprites
    vector<sf::Sprite> walls;

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
    walls.emplace_back(wall1);

    sf::Sprite wall2;
    wall2.setPosition(grid_size * 4, grid_size * 5);
    wall2.setTexture(texture2);
    wall2.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size, grid_size * 11));
    walls.emplace_back(wall2);

    sf::Sprite wall3;
    wall3.setPosition(grid_size * 2, grid_size * 2);
    wall3.setTexture(texture2);
    wall3.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 7, grid_size));
    walls.emplace_back(wall3);

    sf::Sprite wall4;
    wall4.setPosition(grid_size * 11, grid_size * 0);
    wall4.setTexture(texture2);
    wall4.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 4, grid_size * 14));
    walls.emplace_back(wall4);

    sf::Sprite wall5;
    wall5.setPosition(grid_size * 15, grid_size * 13);
    wall5.setTexture(texture2);
    wall5.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 2, grid_size));
    walls.emplace_back(wall5);

    sf::Sprite wall6;
    wall6.setPosition(grid_size * 17, grid_size * 6);
    wall6.setTexture(texture2);
    wall6.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 2, grid_size * 5));
    walls.emplace_back(wall6);

    sf::Sprite wall7;
    wall7.setPosition(grid_size * 17, grid_size * 3);
    wall7.setTexture(texture2);
    wall7.setTextureRect(sf::IntRect(grid_size, grid_size, grid_size * 3, grid_size));
    walls.emplace_back(wall7);

    sf::Sprite goal;
    goal.setPosition(grid_size * 18, 0);
    goal.setTexture(texture_g);
    goal.setScale(0.5, 0.5);


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
        window.draw(goal);

        for(const auto& wall : walls)
            window.draw(wall);

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

        //Collisions
        sf::Vector2u windowSize = window.getSize();
        sf::FloatRect dudeBounds = dude.getGlobalBounds();


        for(const auto& wall : walls){
            if(isColliding(dude, wall))
                dude.move(-velocity);
        }


        if(dudeBounds.left < 0){//left
            dude.setPosition(0, dude.getPosition().y);
        }
        else if(dudeBounds.left + dudeBounds.width > windowSize.x){//right
            dude.setPosition(windowSize.x - dudeBounds.width, dude.getPosition().y);
        }

        if(dudeBounds.top < 0){//top
            dude.setPosition(dude.getPosition().x, 0);
        }
        else if(dudeBounds.top + dudeBounds.height > windowSize.y){//bottom
            dude.setPosition(dude.getPosition().x, windowSize.y - dudeBounds.height);
        }

        //Game win scenario
        if(isColliding(dude, goal)){
            cout << "You win!" << endl;
            return 0;
        }
    }
    return 0;
}
