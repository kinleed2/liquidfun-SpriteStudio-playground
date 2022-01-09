#include "player.h"

#include "game.h"
#include "../GameLib/game_lib.h"
#include "liquidfun/Test.h"

Player::Player()
{
    string dataKey = ss::ResourceManager::getInstance()->addData(
        "Data/SS6/character_template_comipo/character_template1.ssbp");

    ss_player = ss::Player::create();
    ss_player->setData(dataKey);

    body_ = Util::CreateBody(Game::instance()->world(), b2_dynamicBody, position_);

    b2FixtureDef fixture_def;
    fixture_def.density = 10.0f;
    fixture_def.friction = 4.0f;
    fixture_def.restitution = 0.0f;
    Util::AddCircleFixture(body_, b2Vec2(0, 1.0f), 1.0f, &fixture_def);
    Util::AddBoxFixture(body_, b2Vec2(0, 3.5f), b2Vec2(1.0f, 2.5f), &fixture_def);
    Util::AddCircleFixture(body_, b2Vec2(0, 6.0f), 1.0f, &fixture_def);

    remainingJumpSteps = 0;
}

Player::~Player()
{
    safe_delete(ss_player);
    Game::instance()->world()->DestroyBody(body_);
}

void Player::update()
{
    using namespace GameLib::input;



    int moveState;
    if (STATE(0) & PAD_LEFT)
    {
        moveState = MS_LEFT;
        flipX_ = false;
    }
    else if (STATE(0) & PAD_RIGHT)
    {
        moveState = MS_RIGHT;
        flipX_ = true;
    }
    else
    {
        moveState = MS_STOP;
    }

    b2Vec2 vel = body_->GetLinearVelocity();
    float desiredVel = 0;
    switch (moveState)
    {
    case MS_LEFT:  vel.x = -5; break;
    case MS_STOP:  vel.x = 0; break;
    case MS_RIGHT: vel.x = 5; break;
    }

    if (STATE(0) & PAD_UP && remainingJumpSteps == 0)
    {
        remainingJumpSteps = 6;
    }


    body_->SetLinearVelocity(vel);
    body_->SetFixedRotation(true);

    if (remainingJumpSteps > 0)
    {
        body_->ApplyForce(b2Vec2(0, 1500), body_->GetWorldCenter(), false);
        remainingJumpSteps--;

    }

    position_ = body_->GetPosition();
    rotation_ = body_->GetAngle();

    OBJSS6::update();

    ss_player->update(1.0f / 60.f);
}


void Player::draw()
{
    ss_player->draw();
}
