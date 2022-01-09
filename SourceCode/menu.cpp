#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "menu.h"
#include "liquidfun/TestMain.h"
#include "liquidfun/Pyramid.h"
#include "liquidfun/AntiPointy.h"
#include "liquidfun/ApplyForce.h"
#include "liquidfun/Bodies.h"
#include "liquidfun/BodyTypes.h"
#include "liquidfun/Breakable.h"
#include "liquidfun/Bridge.h"
#include "liquidfun/Dominos.h"
#include "liquidfun/Gears.h"
#include "liquidfun/PolyCollision.h"
#include "liquidfun/Car.h"
#include "liquidfun/Fixtures.h"

using namespace GameLib;

//******************************************************************************
//
//      ボタン
//
//******************************************************************************

int Button::counter_ = 0;

void Button::draw()
{
    texture::begin(TEXNO::BUTTON);
    data_->draw(pos_, scale_, angle_, color_);
    texture::end(TEXNO::BUTTON);
}

//--------------------------------
//  コンストラクタ
//--------------------------------
Menu::Menu()
    :buttons_(nullptr)
    , curPos_(0)
{
    init();
}

//--------------------------------
//  デストラクタ
//--------------------------------
Menu::~Menu()
{
    deinit();
    Button::reset();
}

//--------------------------------
//  初期設定
//--------------------------------
void Menu::init()
{
    buttons_ = new Button[]{
        { VECTOR2(1024,  80), "Bodies", Bodies::Create}, 
        { VECTOR2(1024, 160), "Fixtures", Fixtures::Create},
        { VECTOR2(1024, 240), "ApplyForce", ApplyForce::Create}, 
        { VECTOR2(1024, 320), "Car", Car::Create}, 
        { VECTOR2(1024, 400), "Breakable", Breakable::Create}, 
        { VECTOR2(1024, 480), "Bridge", Bridge::Create}, 
        { VECTOR2(1024, 560), "Dominos", Dominos::Create}, 
        { VECTOR2(1024, 640), "Gears", Gears::Create}, 
    };

}

//--------------------------------
//  描画
//--------------------------------
void Menu::draw()
{
    for (int i = 0; i < Button::counter(); i++)
    {
        if (curPos_ == buttons_[i].no())
        {
            // カーソル位置
            buttons_[i].setScale(0.7f, 0.7f);
        }
        else
        {
            buttons_[i].setScale(0.5f, 0.5f);
        }

        // ボタンの描画
        buttons_[i].draw();

        // ボタンの文字の描画
        font::textOut(FONT4, buttons_[i].name(),
            buttons_[i].pos(), buttons_[i].scale() * 3,
            VECTOR4(1, 1, 1, 1), TEXT_ALIGN::MIDDLE);
    }
}

//--------------------------------
//  更新
//--------------------------------
void Menu::update()
{
    using namespace input;
    if (TRG(0) & PAD_DOWN)
    {
        if (curPos_ < Button::counter() - 1)
            curPos_++;
    }
    if (TRG(0) & PAD_UP)
    {
        if (curPos_ > 0)
            curPos_--;
    }
}

//--------------------------------
//  終了処理
//--------------------------------
void Menu::deinit()
{
    if (buttons_) safe_delete_array(buttons_);
}
