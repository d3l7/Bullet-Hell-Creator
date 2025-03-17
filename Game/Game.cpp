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
    this->entered = false;
    this->start = false;
    this->sequenceBeat = false;
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
   bullet->set_speed_multiplier(speed);
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

//Creating
void Game::edit_bullet(Bullet *bullet)
{
    bool editing = true;
    while (editing)
    {
        std::string attribute;
        std::string anotherBullet;

        std::cout << "Please enter the attribute you would like to edit: " << std::endl;
        std::cout << "'size', 'speed', 'time', 'position', 'target position'" << std::endl;
        std::cin >> attribute;
        if (attribute == "size")
        {
            float newSize;

            std::cout << "Please enter the new size:" << std::endl;
            std::cin >> newSize;
            bullet->set_size(newSize);
        } else if (attribute == "speed") {
            float newSpeed;

            std::cout << "Please enter the new speed: " << std::endl;
            std::cin >> newSpeed;
            bullet->set_speed_multiplier(newSpeed);
        } else if (attribute == "time") {
            int newTime;

            std::cout << "Please enter the new time: " << std::endl;
            std::cin >> newTime;
            bullet->set_fire_time(newTime);
        } else if (attribute == "position") {
            float newXCoordinate;
            float newYCoordinate;

            std::cout << "Please enter the new X coordinate: " << std::endl;
            std::cin >> newXCoordinate;
            std::cout << "Please enter the new Y coordinate: " << std::endl;
            std::cin >> newYCoordinate;

            bullet->set_pos(newXCoordinate, newYCoordinate);
        } else if (attribute == "target position") { 
            std::string response;
            float newTargetX;
            float newTargetY;

            std::cout << "Fire at player? 'Y' for yes, any other input for custom target: " << std::endl;
            std::cin >> response;

            if (response == "Y") 
            {
                newTargetX = this->player->get_pos().x + this->player->get_size();
                newTargetY = this->player->get_pos().y + this->player->get_size();
            } else {
                std::cout << "Please enter the new x coordinate of the target: " << std::endl;
                std::cin >> newTargetX;
                std::cout << "Please enter the new y coordinate of the target" << std::endl;
                std::cin >> newTargetY;
            }

            bullet->turn_to_target(newTargetX, newTargetY);
        }
        std::cout << "Would you like to edit another attribute of the bullet? 'Y' for yes, any other input to finish editing." << std::endl;
        std::cin >> anotherBullet;
        if (anotherBullet == 'Y')
        {
            editing = true;
        } else {
            editing = false;
        }

    }

    this->bulletSequence[currentPattern]->delete_bullet(currentBullet);
    this->bulletSequence[currentPattern]->add_bullet(bullet);
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
void Game::create()
{   
    //User responses
    std::string response;
    std::string response2;
    std::string response3;
    std::string response4;

    int patternToEdit;
    int bulletToEdit;

    //Initialise input variables
    float bulletSize;
    float bulletSpeed;
    int bulletTime;
    float bulletXCoordinate;
    float bulletYCoordinate;
    float targetXCoordinate;
    float targetYCoordinate;
    bool fireAtPlayer;

    //Get user input
    if (not (this->bulletSequence[currentPattern]->is_full()))
    {
        while (not this->entered)
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
            std::cout << "Fire at player? (Enter 'Y' for true, any other input for false)" << std::endl;
            std::cin >> response;
            if (response == "Y")
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
            //Initialise bullet
            this->init_bullet(this->bulletSequence[currentPattern], bulletSize, bulletSpeed, bulletTime, 
                              bulletXCoordinate, bulletYCoordinate, targetXCoordinate, targetYCoordinate);
            std::cout << "Do you wish to add more bullets? Enter 'Y' for yes, any other input for no: " << std::endl;
            std::cin >> response2;
            if (response2 == 'Y')
            {
                this->entered = false;
                ++this->currentBullet;
            } else {
                this->entered = true;
            }
        }
    }

    //Check if the user wishes to continue adding to the sequence
    std::cout << "Do you wish to add another pattern? Enter 'Y' for yes, any other input for no: " << std::endl;
    std::cin >> response3;
    if (response3 == 'Y')
    {
        this->entered = false;
        ++this->currentPattern;
        this->currentBullet = 0;
        this->init_pattern();
    } else {
        std::cout << "Do you wish to edit a pattern? 'Y' for yes, any other input if you would like to move on to test the pattern. (press space to start the pattern in the window)" << std::endl;
        std::cin >> response4;
        if (response4 == 'Y')
        {
            std::cout << "Please enter the indexes of the pattern and bullet you would like to edit." << std::endl;
            std::cout << "Pattern: " << std::endl;
            std::cin >> currentPattern;
            std::cout << "Bullet: " << std::endl;
            std::cin >> currentBullet;

            this->edit_bullet(this->bulletSequence[currentPattern]->get_pattern()[currentBullet]);
        } else {
            this->creating = false;
            this->testing = true;
            this->currentPattern = 0;
        }

    }
}

void Game::test()
{
    //Start testing
    if (not (this->start))
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            this->start = true;
        }
    } else if (this->sequenceBeat) {
        this->testing = false;
    } else {
        if (this->player->get_health() <= 0) {
            std::cout << "Sequence lost, took too much damage" << std::endl;
            this->sequenceBeat = true;
        } else if (this->currentPattern < this->bulletSequence.size()){
            //Create the various bullet patterns
            this->update_bullets(this->bulletSequence[this->currentPattern]);
            if (this->bulletSequence[this->currentPattern]->is_empty() && this->currentPattern < this->bulletSequence.size())
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
                    this->patternChanged = false;
                }              
            }
        } else if (this->currentPattern == this->bulletSequence.size()) {
            std::cout << "Sequence beat" << std::endl;
            this->sequenceBeat = true;
        }
        //Updates objects on screen
        this->update_player();
    }
}

void Game::render()
{
    this->window->clear(Color::Transparent); //Clear old frame

    //Draw new frame with game objects
    this->player->render(*this->window);
    
    //Render each bullet, pattern by pattern
    if (this->currentPattern < this->bulletSequence.size())
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
