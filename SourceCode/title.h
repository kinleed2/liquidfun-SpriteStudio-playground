#pragma once

//******************************************************************************
//
//
//      タイトルシーン
//
//
//******************************************************************************

#include "../GameLib/game_lib.h"
#include "menu.h"
#include "scene.h"

//==============================================================================
//
//      Titleクラス
//
//==============================================================================

class Title : public Scene
{
private:
	static Title instance_;

public:
	static Title* instance() { return &instance_; }

private:
	// Menu* menu_;
	float fadeOut_;

	void init() override;
	void update() override;
	void draw() override;
	void deinit() override;

private:
	Title()
		:/*menu_(nullptr)
		,*/ fadeOut_(0)
	{}
	Title(const Title&) = delete;
};

//******************************************************************************
