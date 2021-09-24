#include "Game.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Game::Game() : s_Content(std::make_shared<Content>())
{
	s_Content->s_Window->create(sf::VideoMode(1280, 736), "Snake",sf::Style::Close);
    s_Content->s_States->PutOnStack(std::make_unique<MainMenu>(s_Content));
}
Game::~Game() 
{
    std::cout << "Game destructor!" << std::endl;
    s_Content = NULL;
}

void Game::Run()
{
    s_Content->s_Window->setFramerateLimit(10);

    while (s_Content->s_Window->isOpen())
    {
        s_Content->s_States->StateChange();
        s_Content->s_States->GetCurrent()->Input_Processing();
        s_Content->s_States->GetCurrent()->Update();
        s_Content->s_States->GetCurrent()->Draw();
    }
}