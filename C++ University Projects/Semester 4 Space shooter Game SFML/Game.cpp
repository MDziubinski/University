#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Game.h"
#include "MainMenu.h"


Game::Game() : s_Content(std::make_shared<Content>())
{
    s_Content->s_Window->create(sf::VideoMode(1280, 720), "Space Shooter", sf::Style::Default);
    s_Content->s_States->PutOnStack(std::make_unique<MainMenu>(s_Content));
}
Game::~Game()
{
 
}

void Game::Run()
{
    s_Content->s_Window->setFramerateLimit(60);

    for (auto const& entry : s_Content->s_File->leaderboards)
    {
        std::cout << entry.second << " " << entry.first << '\n';
    }

    while (s_Content->s_Window->isOpen())
    {
        s_Content->s_States->StateChange();
        s_Content->s_States->GetCurrent()->Input_Processing();
        s_Content->s_States->GetCurrent()->Update();
        s_Content->s_States->GetCurrent()->Draw();
    }
}