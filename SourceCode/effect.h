#pragma once
#include "obj2d.h"
#include "objss6.h"
#include "./SSPlayer/SS6Player.h"

class Effect : public OBJSS6
{
public:
    Effect();
    ~Effect() override;

    bool update();
    void draw() override;
};

class EffectManager
{
private:
    static constexpr size_t effectMax = 64;
    std::vector<Effect*> effects;
private:
    EffectManager();
    ~EffectManager(){}

public:
    static EffectManager& instance()
    {
        static EffectManager instance;
        return instance;
    }

    Effect* add(const std::string& animName,
        const b2Vec2& b2Pos,
        int loop = 0,
        const VECTOR2& scale = VECTOR2(1, 1),
        float rotation = 0,
        const VECTOR4& color = VECTOR4(1, 1, 1, 1));

    void update();
    void draw();
    void clear();

};