#include "PausedState.h"

void PausedState::handleInput(FireboyWatergirlGame& game) {
    game.processEvents();
}

void PausedState::update(FireboyWatergirlGame& game) {
    // No actualizar nada en pausa
}

void PausedState::render(FireboyWatergirlGame& game) {
    game.render();
    game.drawPauseMenu();
}