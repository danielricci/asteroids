#include "Engine/Managers/WorldManager.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Managers/StageManager.hpp"
#include "Game/Entities/AsteroidEntity.hpp"

void StageManager::nextStage() {
    WorldManager* worldManager = ManagerHelper::get<WorldManager>();
    worldManager->clean();
    switch(stage) {
        case 0: {
            WorldManager* worldManager = ManagerHelper::get<WorldManager>();
            
            AsteroidEntity* asteroidEntity = new AsteroidEntity();
            asteroidEntity->setPosition({300, 550});
            worldManager->addEntity(asteroidEntity);

            AsteroidEntity* asteroidEntity1 = new AsteroidEntity();
            asteroidEntity1->setPosition({325, 275});
            worldManager->addEntity(asteroidEntity1);

            AsteroidEntity* asteroidEntity2 = new AsteroidEntity();
            asteroidEntity2->setPosition({650, 650});
            worldManager->addEntity(asteroidEntity2);

            AsteroidEntity* asteroidEntity3 = new AsteroidEntity();
            asteroidEntity3->setPosition({955, 450});
            worldManager->addEntity(asteroidEntity3);

            AsteroidEntity* asteroidEntity4 = new AsteroidEntity();
            asteroidEntity4->setPosition({800, 200});
            worldManager->addEntity(asteroidEntity4);
            break;
        }
    }
}

void StageManager::reset() {
    stage = 0;
    nextStage();
}
