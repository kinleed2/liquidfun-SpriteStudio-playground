#pragma once

//******************************************************************************
//
//
//      �Q�[���V�[��
//
//
//******************************************************************************

#include "../GameLib/game_lib.h"
#include "scene.h"
#include "grid.h"
#include "liquidfun/Test.h"
#include "SSPlayer/SS6Player.h"
#include "player.h"
//==============================================================================
//
//      Game�N���X
//
//==============================================================================

class Game : public Scene
{
public:




    //Test* test_;
    enum
    {
        e_count = 20
    };
private:
    bool            isPaused_;
    static Game     instance_;

    POINT lastPos;

    VECTOR3 back_color = {0, 0, 0};

    Test::FUNC_PTR func_;

    Settings settings_;

    //ss::Player* ss_player;
    Player* player_;

    ss::ResourceManager* ss_resource_manager;

public:
    static Game* instance()         { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;
    void scroll();

    void setFunc(Test::FUNC_PTR f) { func_ = f; }
    b2World* world() { return m_world; }

private:
    Game()
        :isPaused_(false)
    {
        ss::SSPlatformInit();
        ss::SSSetPlusDirection(ss::PLUS_UP, GameLib::window::getWidth(), GameLib::window::getHeight());
        ss_resource_manager = ss::ResourceManager::getInstance();

        
    }
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�
    void judge();
    ~Game()
    {
        delete(ss_resource_manager);
        ss::SSPlatformRelease();
    }
};

//******************************************************************************

