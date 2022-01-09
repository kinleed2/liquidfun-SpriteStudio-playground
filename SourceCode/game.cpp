//******************************************************************************
//
//
//      �Q�[��
//
//
//******************************************************************************

//------< �C���N���[�h >--------------------------------------------------------
#include "game.h"
#include "sprite_data.h"
#include "title.h"
#include "../Dear ImGui/imgui.h"
#include "../Dear ImGui/imgui_impl_win32.h"
#include "../Dear ImGui/imgui_impl_dx11.h"
#include "effect.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    isPaused_ = false;   // �|�[�Y�t���O�̏�����

    


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
        DirectX11::getContext());//���Q�b�^�[������
    ImGui::StyleColorsDark();

#endif
}

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Game::deinit()
{
    // ���y�̃N���A
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
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{

    using namespace input;

    // �\�t�g���Z�b�g
    if ((STATE(0) & PAD_SELECT) &&      // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
        (TRG(0) & PAD_START) )// 0�R���̃X�^�[�g�{�^���������ꂽ�u��
    {
        changeScene(Title::instance()); // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

    // �|�[�Y����
    if (TRG(0) & PAD_START)
    {
        isPaused_ = !isPaused_;         // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    }
    if (isPaused_) return;              // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

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
        //////// �����ݒ� ////////
        view::init();
        view::setScale(0.167f);
        view::setCenter(0, 0);

        m_world->SetGravity(b2Vec2(0, -30));
        

        timer_ = 0;

        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
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

        state_++;    // �����ݒ菈���̏I��

              /*  if (func_)
            test_ = func_();*/

            /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////
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
    ImGui::Text(u8"�ʒu�F % .2f", 3.14f);
    ImGui::ColorPicker3("color", & back_color.x);
    ImGui::End();


#endif
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
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
//  �����蔻��
//--------------------------------------------------------------
void Game::judge()
{
}

//******************************************************************************
