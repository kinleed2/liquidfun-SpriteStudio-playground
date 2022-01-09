//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include <iostream>

#include "../GameLib/game_lib.h"
#include "scene.h"
#include "title.h"
#include <Box2D/Box2D.h>
#pragma comment(lib,"liquidfun.lib")


//--------------------------------------------------------------
//  WinMain�i�G���g���|�C���g�j
//--------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{

    SceneManager sceneManager;
    sceneManager.execute(Title::instance());

    return 0;
}

//******************************************************************************
