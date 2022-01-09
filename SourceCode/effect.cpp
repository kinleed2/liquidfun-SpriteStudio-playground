#include "effect.h"

Effect::Effect()
{
    string dataKey = ss::ResourceManager::getInstance()->addData("./Data/SS6/ParticleEffect/ParticleEffect.ssbp");

    ss_player = ss::Player::create();

    ss_player->setData(dataKey);
}

Effect::~Effect()
{

    safe_delete(ss_player);
}

bool Effect::update()
{
    // I—¹”»’f
    if (ss_player->getLoop())
    {
        if (ss_player->getLoopCount() == ss_player->getLoop() &&
            ss_player->getFrameNo() >= ss_player->getEndFrame())
        {
            return false;
        }
    }

    OBJSS6::update();

    ss_player->update(1 / 60.f);

    return true;
}

void Effect::draw()
{
    ss_player->draw();
}


EffectManager::EffectManager()
{
    effects.reserve(effectMax);
}

void EffectManager::update()
{
    for (auto& effect: effects)
    {
        if (!effect->update())
        {
            safe_delete(effect);
        }
    }

    for (auto it = effects.begin();it !=effects.end(); ++it)
    {
        if (*it == nullptr)
        {
            effects.erase(it);
        }
    }
}


void EffectManager::draw()
{
    GameLib::Blender::BLEND_STATE oldState = GameLib::getBlendMode();

    for (auto& effect : effects)
    {
        effect->draw();
    }

    GameLib::setBlendMode(oldState);
}

Effect* EffectManager::add(const std::string& animName, const b2Vec2& b2Pos, int loop, const VECTOR2& scale, float rotation, const VECTOR4& color)
{
    if (effects.size() >= effectMax)
    {
        return nullptr;
    }
    Effect* effect = new Effect();
    effect->init(animName, b2Pos, loop, scale, rotation, color);
    effects.emplace_back(effect);
    return  *effects.rbegin();

}

void EffectManager::clear()
{
    for (auto& effect: effects)
    {
        safe_delete(effect);
    }
    effects.clear();
}
