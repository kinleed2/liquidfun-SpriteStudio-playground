#pragma once

#include "sprite_data.h"
#include "liquidfun/Test.h"

//==============================================================================
//
//      Buttonクラス
//
//==============================================================================
class Button
{
private:
    static int counter_;
public:
    static void reset() { counter_ = 0; }
    static int counter() { return counter_; }

private:
    GameLib::SpriteData* data_;
    VECTOR2 pos_;
    std::string name_;
    VECTOR2 scale_;
    VECTOR4 color_;
    float angle_;
    int no_;

    int state_;
    int timer_;

    Test::FUNC_PTR func_;

public:
    Button(const VECTOR2& pos, std::string n, Test::FUNC_PTR f)
        :pos_(pos), name_(n)
        , data_(&sprButton)
        , scale_({ 1,1 }), color_({ 1,1,1,1 }), angle_(0), no_(counter_++)
        , state_(0), timer_(0), func_(f)
    {}
    void draw();

    // getter
    std::string name() const { return name_; }
    const VECTOR2& pos() const { return pos_; }
    const VECTOR2& scale() const { return scale_; }
    const VECTOR4& color() const { return color_; }
    int no() const { return no_; }
    Test::FUNC_PTR func() const { return func_; }

    // setter
    void setScale(float x, float y) { scale_ = VECTOR2(x, y); }
};

//==============================================================================
//
//      Menuクラス
//
//==============================================================================

class Menu
{
private:
    Button* buttons_;
    int curPos_;

public:
    Menu();
    ~Menu();
    void init();
    void draw();
    void update();
    void deinit();

    Test::FUNC_PTR func() const
    {
        return buttons_[curPos_].func();
    }

    int curPos() const { return curPos_; }
};
