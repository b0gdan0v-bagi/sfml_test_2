#include "engine.h"

using namespace sf;

bool Engine::loadImages()
{
    std::vector<std::string> imageName = { "bullet","player","easyEnemy", "skelletonEnemy" };
    for (std::vector<std::string>::iterator IMAGE = imageName.begin(); IMAGE != imageName.end(); ++IMAGE)
    {
        if (!imageList[*IMAGE].loadFromFile("images/" + *IMAGE + ".png"))
        {
            std::cout << "Cannot load " + *IMAGE + " image!";
            return false;
        }
    }

    imageList["skelletonEnemy"].createMaskFromColor(Color(255, 255, 255));
    imageList["easyEnemy"].createMaskFromColor(Color(0, 0, 0));
    imageList["player"].createMaskFromColor(Color(255, 255, 255));
    return true;
}
bool Engine::loadAnimations()
{
    animationManagerList["player"].create("walk", imageList["player"], 0, 0, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].create("stay", imageList["player"], 0, 0, 40, 80, 1, 0);
    animationManagerList["player"].create("jump", imageList["player"], 0, 241, 40, 80, 1, 0);
    //animationManagerList["player"].create("duck", imageList["player"], 0, 161, 40, 80, 1, 0);
    animationManagerList["player"].create("duck", imageList["player"], 0, 0, 40, 40, 1, 0);
    animationManagerList["player"].create("die", imageList["player"], 0, 81, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].setLoop("die");
    animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
    animationManagerList["skelleton"].loadFromXML("images/skelleton.xml", imageList["skelletonEnemy"]);
    animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
    animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
    return true;
}

void Engine::gameRunning()

{
    window.setView(view);
    if (!menu.mainMenu(window, numberLevel)) return;
    if (numberLevel == 3) pvp = true;
    else pvp = false;
    if (pvp)
    {
        player2View.setSize(resolution.x / 2, resolution.y);
        player1View.setSize(resolution.x / 2, resolution.y);
        player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
    }
    else
    {
        player1View.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        player1View.setSize(resolution.x, resolution.y);
    }
    entities.clear();
    players.clear();
    playerBars.clear();
    if (startGame())
    {
        //numberLevel++;
        //gameRunning(window, numberLevel);
        gameRunning();
    }
}

void Engine::changeLevel(TileMap& lvl)
{
    switch (numberLevel)
    {
    case 1:  lvl.load("map1.tmx"); break;
    case 2:  lvl.load("map1.tmx"); break;
    case 3:  lvl.load("map_test2.tmx"); break;
    default:
        break;
    }
}

