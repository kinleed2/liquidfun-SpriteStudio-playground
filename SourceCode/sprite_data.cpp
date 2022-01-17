//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >--------------------------------------------------------
#include "sprite_data.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< データ >--------------------------------------------------------------

// 2D画像ロードデータ
LoadTexture loadTexture[] = {
    { TEXNO::BUTTON,        L"./Data/Images/button.png",    1U      }, 
    { TEXNO::BLOB_PARTICLE, L"./Data/Images/blob.png",      2048U   },
    { TEXNO::BLOCK,L"./Data/Images/block(2x1).png",64U },
    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------------------------------------------------------------------------------

SpriteData sprButton = SPRITE_CENTER(TEXNO::BUTTON, 0, 0, 689, 125);

//------------------------------------------------------------------------------
//#undef SPRITE_CENTER
//#undef SPRITE_BOTTOM

//******************************************************************************
