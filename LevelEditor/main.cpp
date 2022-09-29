#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

Music bgm;
SoundBuffer sfxBuffer;
Sound sfx;

int main()
{
    RenderWindow window(sf::VideoMode(800, 600), "Level Editor");

    // load music
    if (!bgm.openFromFile("Assets/Audio/BGM.wav")) {
        // error
        return -1;
    }
    bgm.play();
    bgm.setLoop(true);

    // load sfx
    if (!sfxBuffer.loadFromFile("Assets/Audio/Victory Jingle SFX.wav")) {
        // error
        return -1;
    }
    sfx.setBuffer(sfxBuffer);

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event);
        }
        
        if (event.key.code == Keyboard::Space)
            sfx.play();

        update(window);
        render(window);
    }

    return 0;
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