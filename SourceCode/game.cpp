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
#include "block.h"

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
    BlockManager::instance().clear();

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

    // ポーズ処理l
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
        //////// game start setting ////////
        view::init();
        view::setScale(0.3f);
        view::setCenter(view::box2dToWorld(b2Vec2(0, 10)));

        m_world->SetGravity(b2Vec2(0, -30));
        

        timer_ = 0;

        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        //ssbpLib
        player_ = new Player();
        player_->init("character_template_3head/walk", b2Vec2(-20, 5));


        for (int i = 0; i < 10; ++i)
        {
            BlockManager::instance().add(b2Vec2(-10, 1 + i * 2), b2Vec2(2, 1));
        }
        // set ground
        {
            b2BodyDef bd;
            b2Body* ground = m_world->CreateBody(&bd);

            b2EdgeShape shape;
            shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
            ground->CreateFixture(&shape, 0.0f);
        }

        state_++;    // move to game update

    case 1:
        //////// game update ////////
        scroll();

        if (player_)player_->update();

        BlockManager::instance().update();
        EffectManager::instance().update();

        Step(&settings_, false);

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

    BlockManager::instance().draw();

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
