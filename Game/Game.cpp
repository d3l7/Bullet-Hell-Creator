#include "Game.h"

using namespace sf;

//Private Methods
void Game::init_attributes()
{
    this->window = nullptr;  //Initialise window pointer
    this->patternDelay = 600;
}

void Game::init_window()
{
    this->resolution.height = 720;
    this->resolution.width = 1280;

    this->window = new RenderWindow(this->resolution, "Bullet Hell Creator", Style::Titlebar | Style::Close);

    this->window->setFramerateLimit(120);  
}

void Game::init_player() 
{
    this->player = new Player();  //Initialise player reference
}

void Game::init_pattern()
{
    //Create an empty pattern and push to current sequence
    BulletPattern* pattern = new BulletPattern();  
    this->bulletSequence.push_back(pattern);
}

void Game::init_bullet(BulletPattern* pattern, const float pos_x, const float pos_y)
{
   Bullet* bullet = new Bullet();  

   //Load bullet data
   this->spawn_bullet(pattern, bullet, pos_x, pos_y);

   bullet->turn_to_target(this->player->get_pos().x + this->player->get_size(), this->player->get_pos().y + this->player->get_size());
}

//Constructors / Destructors
Game::Game()
{
    this->init_attributes();
    this->init_window();
    this->init_player();
    this->init_pattern();

    //Messy, just testing atm
    this->init_bullet(this->bulletSequence[0], 0.f, 0.f);
    this->init_bullet(this->bulletSequence[0], resolution.width - 7.5f, 0.f);
    this->init_bullet(this->bulletSequence[0], 0.f, resolution.height - 7.5f);
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    //Patterns
    for (auto *p : this->bulletSequence)
    {
        delete p;
    }
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

const BulletPattern *Game::access_pattern(int position) const
{
    return this->bulletSequence[position];
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
    //WASD controls
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

void Game::update_bullets(BulletPattern* pattern)
{
    unsigned counter = 0;
    //Access each bullet
    for (auto *b : pattern->get_pattern())
    {
        b->update();

        //Bullet culling 
        if((b->outside_window(this->resolution.width, this->resolution.height)))
        {
            //Delete individual bullet
            pattern->delete_bullet(counter);
            --counter;
        }else if (pattern->get_pattern()[counter]->get_bounds().intersects(this->player->get_bounds()) && pattern->get_pattern()[counter]->impact_destruction() == true)
        {
            //Delete individual bullet
            pattern->delete_bullet(counter);
            --counter;

            //Lower health
            this->player->set_health(-1);  //Mb make a condition attribute to check for this stuff? then can work out other stuff like i frames later :P
        }

        ++counter;
    }
}

void Game::update_current_sequence()
{
    int temp = this->patternDelay;

    for (auto *p : this->bulletSequence)
    {
        this->update_bullets(p);
        if(this->bulletSequence.back() == p and temp > 0) 
        {
            --temp;
        }
    }
}

void Game::update()
{
    //Check for any inputs that will close the window
    this->poll_events();

    //Create the various bullet patterns
    this->update_current_sequence();

    //Updates objects on screen
    this->update_player();
}

void Game::render()
{
    this->window->clear(Color::Transparent); //Clear old frame

    //Draw new frame with game objects
    this->player->render(*this->window);
    
    //Render each bullet, pattern by pattern
    for (auto *p : this->bulletSequence)
    {
        for (auto *b : p->get_pattern())
        {
            b->render(*this->window);
        }
    }
    this->window->display();

}
