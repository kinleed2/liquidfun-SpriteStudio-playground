#pragma once
#include "obj2d.h"
#include "objss6.h"
#include "liquidfun/util.h"

class Player : public  OBJSS6
{
public:
    Player();
    ~Player() override;

    void update();
    void draw()override;

private:

    enum _moveState {
        MS_STOP,
        MS_LEFT,
        MS_RIGHT,
    };

    b2Body* body_;
    int remainingJumpSteps;

};