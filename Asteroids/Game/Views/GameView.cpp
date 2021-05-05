#include "Engine/Managers/GameManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Views/GameView.hpp"

GameView::GameView() {
    entities.push_back(ManagerHelper::get<GameManager>()->get<PlayerEntity>());
}
