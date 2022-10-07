#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// prototypes
void loadTileset();
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

// globals
const int NUM_OF_TILES = 21;
//Image IMAGES[NUM_OF_TILES];
Texture TILES[NUM_OF_TILES];

int main()
{
    RenderWindow window(sf::VideoMode(1050, 700), "Level Editor");
    loadTileset();

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event);
        }

        update(window);
        render(window);
    }

    return 0;
}

// Loads all tile textures
void loadTileset() {
    for (int i = 0; i < sizeof(TILES) / sizeof(Texture); i++) {
        /*IMAGES[i].loadFromFile("Tileset/70x70/Platformer-" + to_string(i) + ".png");
        TILES[i].loadFromImage(IMAGES[i]);*/
        TILES[i].loadFromFile("Tileset/70x70/Platformer-" + to_string(i) + ".png");
        cout << "Loaded Platformer-" << i << ".png" << endl;
    }
}

void handleInput(RenderWindow& window, Event& e) {
    if (e.type == sf::Event::Closed)
        window.close();


}

void update(RenderWindow& window) {

}

void render(RenderWindow& window) {
    window.clear();
    window.display();
}