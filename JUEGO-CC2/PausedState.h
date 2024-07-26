#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "State.h"
#include "FireboyWatergirlGame.h"

class PausedState : public State {
public:
    void handleInput(FireboyWatergirlGame& game) override;
    void update(FireboyWatergirlGame& game) override;
    void render(FireboyWatergirlGame& game) override;
};

#endif // PAUSEDSTATE_H
