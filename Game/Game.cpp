#include "Game.h"

using namespace sf;

//Private Methods
void Game::init_attributes()
{
    this->window = nullptr;  //Initialise window pointer
    this->bullets = new BulletPattern();
    std::cout << this->bullets->peek() << std::endl;
}

void Game::init_window()
{
    this->resolution.height = 720;
    this->resolution.width = 1280;

    this->window = new RenderWindow(this->resolution, "Bullet Hell Creator", Style::Titlebar | Style::Close);

    this->window->setFramerateLimit(120);  //Might make this part of user settings later :P
}

void Game::init_player() 
{
    this->player = new Player();
}

void Game::init_pattern(BulletPattern* pattern)
{
    pattern = new BulletPattern();
    this->bulletSequence.push_back(pattern);
}

void Game::init_bullet(BulletPattern* pattern, Bullet* bullet, const float pos_x, const float pos_y)
{
   bullet = new Bullet();  //This works
   this->spawn_bullet(pattern, bullet, pos_x, pos_y);
   bullet->turn_to_target(this->player->get_pos().x + this->player->get_size(), this->player->get_pos().y + this->player->get_size());
}

//Constructors / Destructors
Game::Game()
{
    this->init_attributes();
    this->init_window();
    this->init_player();
    this->init_pattern(this->bullets);
    std::cout << this->bullets->peek() << std::endl;

    //Messy, just testing atm
    this->init_bullet(this->bullets, this->bullet, 0.f, 0.f);
    this->init_bullet(this->bullets, this->bulletTwo, resolution.width - 7.5f, 0.f);
    this->init_bullet(this->bullets, this->bulletThree, 0.f, resolution.height - 7.5f);

    std::cout << this->bullets->peek() << std::endl;
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    //Bullets
    for (auto &b : this->bullets->get_pattern())
    {
        delete b;
    }

    delete this->bullets;
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
    if(Keyboard::isKeyPressed(Keyboard::Key::A) && this->player->get_pos().x > 0)
        this->player->move(-1.f, 0.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::D) && this->player->get_pos().x < (this->window->getSize().x - this->player->get_size())) 
        this->player->move(1.f, 0.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::W) && this->player->get_pos().y > 0)
        this->player->move(0.f, -1.f);
    if(Keyboard::isKeyPressed(Keyboard::Key::S) && this->player->get_pos().y < (this->window->getSize().y - this->player->get_size()))
        this->player->move(0.f, 1.f);
}

void Game::spawn_bullet(BulletPattern* pattern, Bullet* bullet, const float pos_x, const float pos_y)
{
    bullet->set_pos(pos_x, pos_y);
    pattern->add_bullet(bullet);
}

void Game::update_player()
{
    //General update method to ensure correct order of method calling 
    this->move_player();
}

void Game::update_bullets()
{
    unsigned counter = 0;
    for (auto *b : this->bullets->get_pattern())
    {
        b->update();

        //Bullet culling 
        if((b->outside_window(this->resolution.width, this->resolution.height)))
        {
            //Delete individual bullet
            this->bullets->delete_bullet(counter);
            --counter;
        }else if (this->bullets->get_pattern()[counter]->get_bounds().intersects(this->player->get_bounds()) && this->bullets->get_pattern()[counter]->impact_destruction() == true)
        {
            //Delete individual bullet
            this->bullets->delete_bullet(counter);
            --counter;

            //Lower health
            this->player->set_health(-1);  //Mb make a condition attribute to check for this stuff? then can work out other stuff like i frames later :P
        }

        ++counter;
    }
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
    
    for (auto *b : this->bullets->get_pattern())
    {
        b->render(*this->window);
    }

    this->window->display();

}
