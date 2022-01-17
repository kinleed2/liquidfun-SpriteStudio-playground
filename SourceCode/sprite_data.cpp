//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< �C���N���[�h >--------------------------------------------------------
#include "sprite_data.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �f�[�^ >--------------------------------------------------------------

// 2D�摜���[�h�f�[�^
LoadTexture loadTexture[] = {
    { TEXNO::BUTTON,        L"./Data/Images/button.png",    1U      }, 
    { TEXNO::BLOB_PARTICLE, L"./Data/Images/blob.png",      2048U   },
    { TEXNO::BLOCK,L"./Data/Images/block(2x1).png",64U },
    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------------------------------------------------------------------------------

SpriteData sprButton = SPRITE_CENTER(TEXNO::BUTTON, 0, 0, 689, 125);

//------------------------------------------------------------------------------
//#undef SPRITE_CENTER
//#undef SPRITE_BOTTOM

//******************************************************************************
