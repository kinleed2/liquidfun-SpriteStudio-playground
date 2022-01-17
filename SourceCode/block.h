#pragma once
#include "obj2d.h"
#include "sprite_data.h"

class Block : public OBJ2D
{
private:
    TEXNO texNo_;
    b2Vec2 size_;

public:
    Block(const b2Vec2& position, const b2Vec2& hsize);
    ~Block()override;

    void update();
    void draw();
};

class BlockManager
{
public:
    static constexpr  size_t blockMax = 64;
private:
    std::vector<Block*> blocks;

private:
    BlockManager();
    ~BlockManager();

public:
    static BlockManager& instance()
    {
        static BlockManager instance;
        return instance;
    }
    Block* add(const b2Vec2& position, const b2Vec2& hsize);

    void update();
    void draw();

    void clear();

};