#include "block.h"
#include "game.h"
#include "liquidfun/util.h"

Block::Block(const b2Vec2& position, const b2Vec2& hsize):texNo_(TEXNO::BLOCK)
{
    position_ = position;
    body_ = Util::CreateBody(Game::instance()->world(), b2_dynamicBody, position);
    Util::AddBoxFixture(body_, b2Vec2(0, 0), hsize);
    size_ = hsize * 2;
}

Block::~Block()
{
    Game::instance()->world()->DestroyBody(body_);
}

void Block::update()
{
    position_ = body_->GetPosition();
    rotation_ = body_->GetAngle();
}

void Block::draw()
{
    VECTOR2 scale = { 400.0f / 256.0f, 200.0f / 128.0f };
    VECTOR2 pos = GameLib::view::box2dToWorld(position_);
    GameLib::texture::draw(texNo_, pos, scale, { 0,0 }, { 256,128 },
        { 128,64 }, rotation_, { 1,1,1,1 }, true);

}


BlockManager::BlockManager()
{
    blocks.reserve(blockMax);
}

BlockManager::~BlockManager()
{
    clear();
    blocks.clear();
}

Block* BlockManager::add(const b2Vec2& position, const b2Vec2& hsize)
{
    Block* block = new Block(position, hsize);
    blocks.emplace_back(block);
    return  (*blocks.rbegin());
}

void BlockManager::update()
{
    for (auto& block : blocks)
    {
        if (block)
        {
            block->update();
        }
    }
}

void BlockManager::draw()
{
    GameLib::texture::begin(TEXNO::BLOCK);
    for (auto& block : blocks)
    {
        if (block)
        {
            block->draw();
        }
    }
    GameLib::texture::end(TEXNO::BLOCK);
}

void BlockManager::clear()
{
    for (auto& block : blocks)
    {
        safe_delete(block);
    }
}





