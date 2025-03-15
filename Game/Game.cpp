#include "Game.h"

using namespace sf;

//Private Methods
void Game::init_attributes()
{
    this->window = nullptr;  //Initialise window pointer
    this->baseDelay = 0;
    this->patternDelay = 300;
    this->currentPattern = 0;
    this->frameRate = 120;

    //Flags
    this->patternChanged = false;
    this->creating = true;
    this->testing = false;
}

void Game::init_window()
{
    this->resolution.height = 720;
    this->resolution.width = 1280;

    this->window = new RenderWindow(this->resolution, "Bullet Hell Creator", Style::Titlebar | Style::Close);

    this->window->setFramerateLimit(this->frameRate);  
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

void Game::init_bullet(BulletPattern* pattern, const float size, const float speed, const int time, 
                       const float pos_x, const float pos_y, const float target_x, const float target_y)
{
   Bullet* bullet = new Bullet();  

   //Load bullet data
   bullet->set_size(size);
   bullet->set_speed(Vector2f(speed, speed));
   bullet->set_fire_time(time*this->frameRate);
   this->spawn_bullet(pattern, bullet, pos_x, pos_y);

   bullet->turn_to_target(target_x, target_y);
}

//Constructors / Destructors
Game::Game()
{
    this->init_attributes();
    this->init_window();
    this->init_player();
    this->init_pattern();  //Empty first pattern to fill
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

const bool Game::creating_pattern() const
{
    return this->creating;
}

const bool Game::testing_pattern() const
{
    return this->testing;
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

//Testing
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
        }else if (pattern->get_pattern()[counter]->get_bounds().intersects(this->player->get_bounds()))
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

//Final functions
void Game::create()  //que puta mierda es esto chaval
{
    //Initialise input variables
    float bulletSize;
    float bulletSpeed;
    int bulletTime;
    float bulletXCoordinate;
    float bulletYCoordinate;
    float targetXCoordinate;
    float targetYCoordinate;
    int response;
    bool fireAtPlayer;

    //Get user input
    if (not (this->bulletSequence[currentPattern]->is_full()))
    {
        if (not this->entered)
        {
            std::cout << "Window size is - " << this->resolution.width << "x" 
            << this->resolution.height << std::endl;
            std::cout << "Please enter the following bullet data:" << std::endl;
            std::cout << "Size of bullet: " << std::endl;
            std::cin >> bulletSize;
            std::cout << "Speed of bullet: (base speed is )" << std::endl;
            std::cin >> bulletSpeed;
            std::cout << "Time for bullet to fire: " << std::endl;
            std::cin >> bulletTime;
            std::cout << "X coordinate of bullet" << std::endl;
            std::cin >> bulletXCoordinate;
            std::cout << "Y coordinate of bullet" << std::endl;
            std::cin >> bulletYCoordinate;
            std::cout << "Fire at player? (Enter 1 for true, any other input for false)" << std::endl;
            std::cin >> response;
            if (response == 1)
            {
                fireAtPlayer = true;
            } else {
                fireAtPlayer = false;
            }
            if (not (fireAtPlayer))
            {
                std::cout << "X coordinate of target" << std::endl;
                std::cin >> targetXCoordinate;
                std::cout << "Y coordinate of target" << std::endl;
                std::cin >> targetYCoordinate;
            } else {
                targetXCoordinate = this->player->get_pos().x + this->player->get_size();
                targetYCoordinate = this->player->get_pos().y + this->player->get_size();
            }

            this->entered = true;
        } else{
            //Initialise bullet
            this->init_bullet(this->bulletSequence[currentPattern], bulletSize, bulletSpeed, bulletTime, 
                              bulletXCoordinate, bulletYCoordinate, targetXCoordinate, targetYCoordinate);
            this->entered = false;
        }
    }

    //Check if the user wishes to continue adding to the sequence
}

void Game::test()
{
    //Create the various bullet patterns
    if (this->currentPattern <= this->bulletSequence.size() - 1)
    {
        this->update_bullets(this->bulletSequence[this->currentPattern]);
        if (this->bulletSequence[this->currentPattern]->is_empty() && this->currentPattern <= this->bulletSequence.size() - 1)
        {
            if (this->patternDelay != 0)  //If delaying between patterns, run out the delay before next pattern
            {
                --this->patternDelay;
            } else {
                ++this->currentPattern;
                this->patternChanged = true;  
            }
            if (patternChanged)  //Reset the delay between patterns
            {
                this->patternDelay = this->baseDelay;
                this-> patternChanged = false;
            }              
        }
    }
    //Updates objects on screen
    this->update_player();
}

void Game::render()
{
    this->window->clear(Color::Transparent); //Clear old frame

    //Draw new frame with game objects
    this->player->render(*this->window);
    
    //Render each bullet, pattern by pattern
    if (not (this->bulletSequence[this->currentPattern]->is_empty()))
    {
        if (this->currentPattern < this->bulletSequence.size())
        {
            for (auto *b : this->bulletSequence[this->currentPattern]->get_pattern())
            {
                b->render(*this->window);
            }   
        }
    }
    this->window->display();

}
