#include "Game.h"

void Game::initVariables()
{

}

void Game::initWindow()
{
    screen_size = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT); 
    window = new RenderWindow(screen_size, "Thosu", Style::Close | Style::Titlebar); //Window with close and titlebar
    window->setFramerateLimit(FRAME_LIMIT);
}

Game::Game()
{
    initWindow();
    initVariables();
}

Game::~Game()
{
    delete window;
}

bool Game::isOpen()
{
    return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(exit_event)) {
        if (exit_event.type == Event::Closed) {
            window->close();
        }
        else if (exit_event.KeyPressed && exit_event.Event::key.code == Keyboard::Escape) {
            window->close();
        }
    }
}

void Game::update()
{
    pollEvents();
    world_bkgd_controller.update();
    player_controller.update(SCREEN_HEIGHT, SCREEN_WIDTH);
}

void Game::render()
{
    window->clear();

    world_bkgd_controller.render(*window);
    player_controller.render(*window);

    window->display();
}
