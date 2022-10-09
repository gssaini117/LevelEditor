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
int currIndex = 0;

Texture TILES[NUM_OF_TILES];
Sprite currTile;

int main()
{
    RenderWindow window(VideoMode(1050, 700), "Level Editor");
    loadTileset();

    // game loop
    while (window.isOpen())
    {
        Event event;
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
    if (e.type == Event::Closed) window.close();

    // changes current tile index based on left or right key press
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Left) 
        if (--currIndex < 0) currIndex = NUM_OF_TILES - 1;
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Right)
        ++currIndex %= NUM_OF_TILES;
}

void update(RenderWindow& window) {
    currTile.setTexture(TILES[currIndex]);
    currTile.setPosition(Mouse::getPosition(window).x - 35, Mouse::getPosition(window).y - 35);
}

void render(RenderWindow& window) {
    window.clear();
    window.draw(currTile);
    window.display();
}