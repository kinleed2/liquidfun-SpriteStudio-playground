//******************************************************************************
//
//
//      ゲーム
//
//
//******************************************************************************

//------< インクルード >--------------------------------------------------------
#include "game.h"
#include "sprite_data.h"
#include "title.h"
#include "../Dear ImGui/imgui.h"
#include "../Dear ImGui/imgui_impl_win32.h"
#include "../Dear ImGui/imgui_impl_dx11.h"
#include "effect.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  初期化処理
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    isPaused_ = false;   // ポーズフラグの初期化

    


#ifdef USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig config;
    config.MergeMode = true;
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\BIZ-UDGothicR.ttc", 16.0f, &config, io.Fonts->GetGlyphRangesJapanese());
    ImGui_ImplWin32_Init(window::getHwnd());
    ImGui_ImplDX11_Init(DirectX11::getDevice(), 
        DirectX11::getContext());//←ゲッターを自作
    ImGui::StyleColorsDark();

#endif
}

//--------------------------------------------------------------
//  終了処理
//--------------------------------------------------------------
void Game::deinit()
{
    // 音楽のクリア
    music::clear();
    EffectManager::instance().clear();


    {
        b2Body* b = m_world->GetBodyList();
        while(b)
        {
            b2Body* next = b->GetNext();
            m_world->DestroyBody(b);
            b = next;
        }
    }

    //safe_delete(test_);


#ifdef USE_IMGUI
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif

}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{

    using namespace input;

    // ソフトリセット
    if ((STATE(0) & PAD_SELECT) &&      // 0コンのセレクトボタンが押されている状態で
        (TRG(0) & PAD_START) )// 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance()); // タイトルシーンに切り替える
        return;
    }

    // ポーズ処理
    if (TRG(0) & PAD_START)
    {
        isPaused_ = !isPaused_;         // 0コンのスタートボタンが押されたらポーズ状態が反転
    }
    if (isPaused_) return;              // この時点でポーズ中ならリターン

    if (TRG(0) & PAD_TRG1)
    {
        EffectManager::instance().add("e028/beam",
            { 0,0 });
    }
    if (TRG(0) & PAD_TRG2)
    {
        EffectManager::instance().add("e007/thunderball",
            { 0,0 });
    }
    if (TRG(0) & PAD_TRG3)
    {
        EffectManager::instance().add("e009/fire",
            { 0,0 });
    }

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        view::init();
        view::setScale(0.167f);
        view::setCenter(0, 0);

        m_world->SetGravity(b2Vec2(0, -30));
        

        timer_ = 0;

        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        //ssbpLib
        player_ = new Player();
        player_->init("character_template_3head/walk", b2Vec2(-20, 5));

        // Pyramid
        {
            b2BodyDef bd;
            b2Body* ground = m_world->CreateBody(&bd);

            b2EdgeShape shape;
            shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
            ground->CreateFixture(&shape, 0.0f);
        }

        {
            float32 a = 0.5f;
            b2PolygonShape shape;
            shape.SetAsBox(a, a);

            b2Vec2 x(-7.0f, 0.75f);
            b2Vec2 y;
            b2Vec2 deltaX(0.5625f, 1.25f);
            b2Vec2 deltaY(1.125f, 0.0f);

            for (int32 i = 0; i < e_count; ++i)
            {
                y = x;

                for (int32 j = i; j < e_count; ++j)
                {
                    b2BodyDef bd;
                    bd.type = b2_dynamicBody;
                    bd.position = y;
                    b2Body* body = m_world->CreateBody(&bd);
                    body->CreateFixture(&shape, 5.0f);

                    y += deltaY;
                }

                x += deltaX;
            }
        }

        state_++;    // 初期設定処理の終了

              /*  if (func_)
            test_ = func_();*/

            /*fallthrough*/
    case 1:
        //////// 通常時の処理 ////////
        scroll();

        if (player_)player_->update();
        
        EffectManager::instance().update();

        timer_++;

        break;
    }

#ifdef USE_IMGUI
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("ImGUI");
    ImGui::Text(u8"位置： % .2f", 3.14f);
    ImGui::ColorPicker3("color", & back_color.x);
    ImGui::End();


#endif
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(back_color.x,back_color.y,back_color.y, 1));

    Grid::draw();

    //if(test_)
    //    test_->Step(&settings_);

    Step(&settings_);
    
    if (player_)player_->draw();
    
    EffectManager::instance().draw();


#ifdef USE_IMGUI
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}

void Game::scroll()
{
    POINT curPos;
    GetCursorPos(&curPos);
    ScreenToClient(GetActiveWindow(), &curPos);

    if (GetAsyncKeyState(VK_RBUTTON) < 0)
    {
        int dx = curPos.x - lastPos.x;
        int dy = curPos.y - lastPos.y;
        float scale = view::getScale();
        if (dx || dy)
        {
#ifdef GAMELIB_PLUS_UP
            dy = -dy;
#endif
            view::setCenter(view::getCenter() + VECTOR2(-dx / scale, -dy / scale));

        }
    }
    lastPos = curPos;
}

//--------------------------------------------------------------
//  あたり判定
//--------------------------------------------------------------
void Game::judge()
{
}

//******************************************************************************
