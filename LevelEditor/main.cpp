#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

// prototypes
void loadTileset();
void initializeGrid();
void handleInput(RenderWindow& window, Event& e);
void saveLevel();
void loadLevel();
void update(RenderWindow& window);
void render(RenderWindow& window);

// globals
const int NUM_OF_TILES = 21;
int currIndex = 0;
Texture TILES[NUM_OF_TILES];
Sprite currTile;
int GRID[10][15];

int main()
{
    RenderWindow window(VideoMode(1050, 700), "Level Editor");
    loadTileset();
    initializeGrid();

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
        TILES[i].loadFromFile("Tileset/70x70/Platformer-" + to_string(i) + ".png");
        cout << "Loaded Platformer-" << i << ".png" << endl;
    }

}

// Creates a 15x10 Grid (the window is 1050x700 pixels)
void initializeGrid() {
    for (int i = 0; i < sizeof GRID / sizeof GRID[0]; i++) {
        for (int j = 0; j < sizeof GRID[0] / sizeof(int); j++) {
            GRID[i][j] = -1;
        }
    }
}

void handleInput(RenderWindow& window, Event& e) {
    if (e.type == Event::Closed) window.close();

    // changes current tile index based on left or right key press
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Left) 
        if (--currIndex < 0) currIndex = NUM_OF_TILES - 1;
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Right)
        ++currIndex %= NUM_OF_TILES;
    // save or load level
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Down)
        saveLevel();
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Up)
        loadLevel();
}

// Exports level to a text file
void saveLevel() {
    ofstream level("level.txt");
    if (level.is_open()) {
        for (int i = 0; i < sizeof GRID / sizeof GRID[0]; i++) {
            for (int j = 0; j < sizeof GRID[0] / sizeof(int); j++) {
                if (j == sizeof GRID[0] / sizeof(int) - 1)
                    level << endl;
                else 
                    level << GRID[i][j] << " ";
            }
        }
    }
    else cout << "Problem creating save file" << endl;  
    level.close();
}

// Imports saved level from a text file
void loadLevel() {
    int i = 0, j = 0;
    string row;
    ifstream level("level.txt");
    while (getline(level, row)) {
        // read file row space by space and save each int to GRID
    }
}

void update(RenderWindow& window) {
    // updates selected tile
    currTile.setTexture(TILES[currIndex]);
    currTile.setPosition(Mouse::getPosition(window).x - 35, Mouse::getPosition(window).y - 35);
}

void render(RenderWindow& window) {
    window.clear();
    window.draw(currTile);
    window.display();
}