#include "objss6.h"

void OBJSS6::init(const std::string& animName, const b2Vec2& b2Pos, int loop, const VECTOR2& scale, float rotation, const VECTOR4& color)
{
    if (animName.empty()) return;

    ss_player->play(animName);
    ss_player->setLoop(loop);

    setPosition(b2Pos);
    setScale(scale);
    setRotation(rotation);
    setColor(color);

    if (body_)
    {
        body_->SetTransform(b2Pos, rotation);
    }
}

void OBJSS6::update()
{
    VECTOR2 pos = GameLib::view::box2dToWorld(position_);
    ss_player->setPosition(pos.x, pos.y);
    ss_player->setRotation(0.0f, 0.0f, DirectX::XMConvertToDegrees(rotation()));
    ss_player->setAlpha(color().w * 255);
    ss_player->setColor(color().x * 255, color().y * 255, color().z * 255);
    ss_player->setFlip(flipX_, flipY_);


}



