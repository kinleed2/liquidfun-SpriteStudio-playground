
#pragma once
#include "obj2d.h"
#include "./SSPlayer/SS6Player.h"

class OBJSS6 : public OBJ2D
{
protected:
    ss::Player* ss_player;
public:
    OBJSS6()
        :ss_player(nullptr){}
    ~OBJSS6()override { safe_delete(ss_player); }

    void init(const std::string& animName, const b2Vec2& b2Pos,
        int loop = 0, const VECTOR2& scale = VECTOR2(1, 1), float rotation = 0,
        const VECTOR4& color = VECTOR4(1, 1, 1, 1));

    void update();

    virtual void draw() = 0;

};