#include "Game.h"

using namespace sf;

//Private Methods
void Game::init_attributes()
{
    this->window = nullptr;  //Initialise window pointer
}

void Game::init_window()
{
    this->resolution.height = 720;
    this->resolution.width = 1280;

    this->window = new RenderWindow(this->resolution, "Bullet Hell Creator", Style::Titlebar | Style::Close);

    this->window->setFramerateLimit(120);  //Might make this part of user settings later :P
}

void Game::init_player()  //Ffs
{
    this->player = new Player();
}

//Temp

void Game::init_bullet()
{
    this->bullet = new Bullet();
}

//Constructors / Destructors
Game::Game()
{
    this->init_attributes();
    this->init_window();
    this->init_player();
    this->init_bullet();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
    delete this->bullet;
}

//Accessors

const bool Game::running() const
{
    return this->window->isOpen();
}

//Methods

void Game::poll_events()
{
    while(this->window->pollEvent(this->ev))
    {
        //Allow the user to close the game either by pressing escape or hitting the close button on the window
        switch(this->ev.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if(this->ev.key.code == Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::move_player()
{
    if(Keyboard::isKeyPressed(Keyboard::Key::A) && this->player->getX() > 0)
        this->player->move(-1.f, 0.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::D) && this->player->getX() < (this->window->getSize().x - this->player->getSize())) 
        this->player->move(1.f, 0.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::W) && this->player->getY() > 0)
        this->player->move(0.f, -1.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::S) && this->player->getY() < (this->window->getSize().y - this->player->getSize()))
        this->player->move(0.f, 1.f);
}

void Game::update_player()
{
    //General update method to ensure correct order of method calling 
    this->move_player();
}

void Game::update_bullets()
{
    this->bullet->move(1.f, 0.f);
}

void Game::update()
{
    this->poll_events();

    this->update_player();
    this->update_bullets();
}

void Game::render()
{
    this->window->clear(Color::Transparent); //Clear old frame

    //Draw new frame with game objects
    this->player->render(*this->window);
    this->bullet->render(*this->window);

    this->window->display();

}
