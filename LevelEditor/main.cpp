/*
* Programmed by Gurkirat Saini
* 10/10/2022
* GAME-230
*/

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
void renderGrid(RenderWindow& window);

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
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::S)
        saveLevel();
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::L)
        loadLevel();

    // save screenshot of level
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Space) {
        Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (texture.copyToImage().saveToFile("LevelScreenshot.png")) {
            cout << "Screenshot of Level Saved." << endl;
        }
    }

    // left click to place tile, right click to remove tile
    if (Mouse::isButtonPressed(Mouse::Left)) {
        int mouseGridX = Mouse::getPosition(window).x / 70;
        int mouseGridY = Mouse::getPosition(window).y / 70;
        if (mouseGridX >= 0 && mouseGridX < 15) {
            if (mouseGridY >= 0 && mouseGridY < 10) {
                GRID[mouseGridY][mouseGridX] = currIndex;
            }
        }
    }
    if (Mouse::isButtonPressed(Mouse::Right)) {
        int mouseGridX = Mouse::getPosition(window).x / 70;
        int mouseGridY = Mouse::getPosition(window).y / 70;
        if (mouseGridX >= 0 && mouseGridX < 15) {
            if (mouseGridY >= 0 && mouseGridY < 10) {
                GRID[mouseGridY][mouseGridX] = -1;
            }
        }
    }
}

// Exports level to a text file
void saveLevel() {
    ofstream level("level.txt");
    if (level.is_open()) {
        for (int i = 0; i < sizeof GRID / sizeof GRID[0]; i++) {
            for (int j = 0; j < sizeof GRID[0] / sizeof(int); j++) {
                if (j == sizeof GRID[0] / sizeof(int) - 1)
                    level << GRID[i][j] << endl;
                else 
                    level << GRID[i][j] << " ";
            }
        }
        cout << "Level Saved!\n";
    }
    else cout << "error creating save file." << endl;  
    level.close();
}

// Imports saved level from a text file
void loadLevel() {
    string tile;
    ifstream level("level.txt");
    if (level.is_open()) {
        for (int i = 0; i < sizeof GRID / sizeof GRID[0]; i++) {
            for (int j = 0; j < sizeof GRID[0] / sizeof(int); j++) {
                level >> GRID[i][j];
            }
        }
        cout << "Level Loaded!\n";
    }
    else cout << "error loading save file." << endl;
    level.close();
}

void update(RenderWindow& window) {
    // updates selected tile
    currTile.setTexture(TILES[currIndex]);
    currTile.setPosition(Mouse::getPosition(window).x - 35, Mouse::getPosition(window).y - 35);
}

void render(RenderWindow& window) {
    window.clear();
    renderGrid(window);
    window.draw(currTile);
    window.display();
}

void renderGrid(RenderWindow& window) {
    for (int i = 0; i < sizeof GRID / sizeof GRID[0]; i++) {
        for (int j = 0; j < sizeof GRID[0] / sizeof(int); j++) {
            Sprite temp;
            temp.setTexture(TILES[GRID[i][j]]);
            temp.setPosition(j*70, i*70);
            if (GRID[i][j] >= 0)
                window.draw(temp);
        }
    }
}