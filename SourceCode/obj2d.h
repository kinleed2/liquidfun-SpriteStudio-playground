#pragma once
#include "Box2D/Box2D.h"
#include "../GameLib/game_lib.h"

class OBJ2D
{
public:

protected:
    b2Vec2 position_;
    VECTOR2 scale_;
    float rotation_;
    VECTOR4 color_;
    bool flipX_;
    bool flipY_;

    b2Body* body_;

public:
    OBJ2D()
        :position_({0,0})
    ,scale_({1,1})
    ,rotation_(0)
    ,color_({1,1,1,1})
    ,flipX_(false)
    ,flipY_(false)
    ,body_(nullptr){}

    virtual  ~OBJ2D(){}

    const b2Vec2& position()const { return position_; }
    void setPosition(const b2Vec2& position) { position_ = position; }

    const VECTOR2& scale() const { return scale_; }
    void setScale(const VECTOR2& scale) { scale_ = scale; }

    float rotation()const { return rotation_; }
    void setRotation(float rotation) { rotation_ = rotation; }

    const VECTOR4& color() const { return color_; }
    void setColor(const VECTOR4& color) { color_ = color; }

    bool flipX()const { return  flipX_; }
    void setFlipX(bool flipX) { flipX_ = flipX; }

    bool flipY()const { return  flipY_; }
    void setFlipY(bool flipY) { flipY_ = flipY; }

};
