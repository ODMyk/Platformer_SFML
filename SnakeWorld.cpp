#include <iostream>
#include "Headers/SnakeWorld.hpp"
#include "Headers/SpriteNode.hpp"
#include<SFML/Graphics.hpp>

SnakeWorld::SnakeWorld(sf::RenderWindow& window): World(window), levelHeight(0), levelWidth(0) {
  loadTextures();
  loadLevel("resources/SnakeMaps/1.txt");
  buildScene();
}

void SnakeWorld::draw()
{
     mWindow.setView(mWorldView);
     mWindow.clear(sf::Color(0, 0, 0));
     sf::RectangleShape r;
     r.setSize({32, 32});
     for(int i=0; i<levelHeight; i++)
     {
         for(int j=0; j<levelWidth; j++)
         {
             if(A[i][j]=='#')
             {
                 r.setFillColor({100, 100, 100, 255});
                 r.setPosition({j*32, i*32});
                 mWindow.draw(r);
             }
             if(A[i][j]=='H')
             {
                 r.setPosition({j*32, i*32});
                 r.setFillColor({255, 255, 255, 255});
                 mWindow.draw(r);
             }
             if(A[i][j]=='T')
             {
                 r.setPosition({j*32, i*32});
                 r.setFillColor({255, 255, 100, 255});
                 mWindow.draw(r);
             }
             if(A[i][j]=='F')
             {
                 r.setPosition({j*32, i*32});
                 r.setFillColor({sf::Color::Red});
                 mWindow.draw(r);
             }
         }

     }
}
void SnakeWorld::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
    {
        if(A[snake.getPosition(0).y-1][snake.getPosition(0).x]=='.' || A[snake.getPosition(0).y-1][snake.getPosition(0).x]=='F')
            snake.MoveUp();

        if(A[snake.getPosition(0).y-1][snake.getPosition(0).x]=='T')
        {
            GameOver=1;
            return;
        }

    } else
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
    {
        if(A[snake.getPosition(0).y+1][snake.getPosition(0).x]=='.' || A[snake.getPosition(0).y+1][snake.getPosition(0).x]=='F')
            snake.MoveDown();

        if(A[snake.getPosition(0).y+1][snake.getPosition(0).x]=='T')
        {
            GameOver=1;
            return;
        }
    } else
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
    {
        if(A[snake.getPosition(0).y][snake.getPosition(0).x-1]=='.' || A[snake.getPosition(0).y][snake.getPosition(0).x-1]=='F')
            snake.MoveLeft();

        if(A[snake.getPosition(0).y][snake.getPosition(0).x-1]=='T')
        {
            GameOver=1;
            return;
        }
    } else
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
    {
        if(A[snake.getPosition(0).y][snake.getPosition(0).x+1]=='.' || A[snake.getPosition(0).y][snake.getPosition(0).x+1]=='F')
            snake.MoveRight();
        if(A[snake.getPosition(0).y][snake.getPosition(0).x+1]=='T')
        {
            GameOver=1;
            return;
        }
    }
    if(A[snake.getPosition(0).y][snake.getPosition(0).x]=='F')
    {
        snake.Eat();
        A[snake.getPosition(0).y][snake.getPosition(0).x]='H';
        spawn_fruit();
    }
}

void SnakeWorld::update(sf::Time timedelta) {
    for(int i=0; i<levelHeight; i++)
    {
        for(int j=0; j<levelWidth; j++)
        {
            if(A[i][j]!='#' && A[i][j]!='F')
            {
                A[i][j]='.';
            }
        }
    }
    A[snake.getPosition(0).y][snake.getPosition(0).x]='H';
    for(int i=1; i<snake.getSize(); i++)
    {
        int x=snake.getPosition(i).x;
        int y=snake.getPosition(i).y;
        A[y][x]='T';
    }
  sf::Vector2f position = snake.getPosition(0);
  position.x*=32; position.y*=32;
  mWorldView.setCenter(position);
}

void SnakeWorld::loadTextures() {

//    mTextures.load(Textures::Background, "resources/img/Background.png");
    mTextures.load(Textures::Avatar, "resources/img/SnakeHead.png");
    mTextures.load(Textures::SnakeHead, "resources/img/SnakeHead.png");
    mTextures.load(Textures::SnakeTailUp, "resources/img/SnakeBodyUp.png");
    mTextures.load(Textures::SnakeTailDown, "resources/img/SnakeBodyDown.png");
    mTextures.load(Textures::SnakeTailLeft, "resources/img/SnakeBodyLeft.png");
    mTextures.load(Textures::SnakeTailRight,"resources/img/SnakeBodyRight.png");
}
void SnakeWorld::loadLevel(std::string s)
{
    LevelMap.open(s);
    LevelMap>>levelHeight;
    LevelMap>>levelWidth;
    A.resize(levelHeight);
    for(int i=0; i<levelHeight; i++)
    {
        A[i].resize(levelWidth);
        for(int j=0; j<levelWidth; j++)
        {
            LevelMap>>A[i][j];
        }
    }
    LevelMap.close();
}

int SnakeWorld::random_number(int x)
{
    return rand()%(x-1)+1;
}

bool SnakeWorld::isGameOver() {return GameOver;}

void SnakeWorld::spawn_fruit()
{
    int x = random_number(levelWidth);
    int y = random_number(levelHeight);
    int cnt=0;
    while(A[y][x]!='.' && cnt<100)
    {
        x = random_number(levelWidth);
        y = random_number(levelHeight);
        cnt++;
    }
    if(A[y][x]!='.')
    {
        for(int i=0; i<levelHeight; i++)
        {
            for(int j=0; j<levelWidth; j++)
            {
                if(A[i][j]=='.')
                {
                    A[i][j]='F';
                    return;
                }
            }
        }
    }
    A[y][x]='F';
}

void SnakeWorld::buildScene() {
  snake.add(5, 5);
  spawn_fruit();

//  sf::Texture &texture0 = mTextures.get(Textures::Foreground_);

//  sf::Texture &texture = mTextures.get(Textures::Background);
//  mWorldBounds.width = levelWidth*32;
//  mWorldBounds.height = levelHeight*32;
//  sf::IntRect textureRect(mWorldBounds);

//  std::unique_ptr<SpriteNode> foregroundSprite(new SpriteNode(texture0));
//  foregroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);


//  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
//  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
//  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}

