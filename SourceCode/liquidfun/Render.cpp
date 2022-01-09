/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
* Copyright (c) 2013 Google, Inc.
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Render.h"
#include "../GameLib/game_lib.h"
#include "../sprite_data.h"
#include "../Dear ImGui/imgui.h"
#include <cstdarg>
#if 0
#include "GL/freeglut.h"

#if defined(__ANDROID__) || defined(__IOS__)
#include "GLEmu/gl_emu.h"
#endif // defined(__ANDROID__) || defined(__IOS__)

#ifdef __ANDROID__
#include <android/log.h>
#endif // __ANDROID__

// We need these 4 from glext.h, and define them here rather than relying on
// the header, which is not universally available.
#ifndef GL_POINT_SPRITE
#define GL_POINT_SPRITE                   0x8861
#endif
#ifndef GL_COORD_REPLACE
#define GL_COORD_REPLACE                  0x8862
#endif
#ifndef GL_GENERATE_MIPMAP
#define GL_GENERATE_MIPMAP                0x8191
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE                  0x812F
#endif

#include <stdio.h>
#include <stdarg.h>


float currentscale = 1;	// amount of pixels that corresponds to one world unit, needed to use glPointSize correctly

void LoadOrtho2DMatrix(double left, double right, double bottom, double top)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	currentscale = float(h / (top - bottom));

#if USE_GL_KIT
	const GLKMatrix4 matrix = GLKMatrix4MakeOrtho(left, right, bottom, top,
													-1.0, 1.0);
	glLoadMatrixf((const GLfloat*)&matrix);
#else
	// L/R/B/T
	gluOrtho2D(left, right, bottom, top);
#endif // USE_GL_KIT
}
#endif

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//glColor3f(color.r, color.g, color.b);
	//glBegin(GL_LINE_LOOP);
	//for (int32 i = 0; i < vertexCount; ++i)
	//{
	//	glVertex2f(vertices[i].x, vertices[i].y);
	//}
	//glEnd();


	//現在のブレンドステートを一旦保持する
	//GameLib::Blender::BLEND_STATE oldState = GameLib::getBlendMode();
	std::vector<VECTOR2> v;
	// スケールの適用
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール
	v.resize(vertexCount);
	for (int32 i = 0; i < vertexCount; i++)
	{
		v[i].x = vertices[i].x * scale;
		v[i].y = vertices[i].y * scale;
	}
	// 描画
	constexpr float lineWeight = 1.0f;     // 線の太さ
	VECTOR4 col{ color.r, color.g, color.b, 1.0f };

	// 線画
	//GameLib::setBlendMode(GameLib::Blender::BS_NONE);
	// 始点→終点までの線画
	const int32 lineNum = vertexCount - 1;  // 始点→終点までの輪郭線の本数

	for (int32 i = 0; i < lineNum; i++)
	{
		GameLib::primitive::line(v[i], v[i + 1], col, lineWeight, true);
	}
	// 終点→始点の線画
	const int32 end = vertexCount - 1;     // 終点のインデックス
	GameLib::primitive::line(v[end], v[0], col, lineWeight, true);
	// ブレンドステートを戻す
	//GameLib::setBlendMode(oldState);
	
}

void DebugDraw::DrawFlatPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//glColor4f(color.r, color.g, color.b, 1);
	//glBegin(GL_TRIANGLE_FAN);
	//for (int32 i = 0; i < vertexCount; ++i)
	//{
	//	glVertex2f(vertices[i].x, vertices[i].y);
	//}
	//glEnd();

	//GameLib::Blender::BLEND_STATE oldState = GameLib::getBlendMode();
	std::vector<VECTOR2> v;
	// スケールの適用
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール
	v.resize(vertexCount);
	for (int32 i = 0; i < vertexCount; i++)
	{
		v[i].x = vertices[i].x * scale;
		v[i].y = vertices[i].y * scale;
	}
	// 描画
		// 線画
	//GameLib::setBlendMode(GameLib::Blender::BS_NONE);

	VECTOR4 col{ color.r, color.g, color.b, 1.0f };
	// 矩形を塗りつぶす
	const int32 nPolygon = vertexCount - 2; // 描画するポリゴン数
	GameLib::primitive::draw_triangle_fan(v.data(), col, nPolygon, true);


	// ブレンドステートを戻す
	//GameLib::setBlendMode(oldState);

}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	//glBegin(GL_TRIANGLE_FAN);
	//for (int32 i = 0; i < vertexCount; ++i)
	//{
	//	glVertex2f(vertices[i].x, vertices[i].y);
	//}
	//glEnd();
	//glDisable(GL_BLEND);
	//
	//glColor4f(color.r, color.g, color.b, 1.0f);
	//glBegin(GL_LINE_LOOP);
	//for (int32 i = 0; i < vertexCount; ++i)
	//{
	//	glVertex2f(vertices[i].x, vertices[i].y);
	//}
	//glEnd();

	//現在のブレンドステートを一旦保持する
    GameLib::Blender::BLEND_STATE oldState = GameLib::getBlendMode();
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
    std::vector<VECTOR2> v;
    // スケールの適用
    const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール
    v.resize(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
    {
        v[i].x = vertices[i].x * scale;
        v[i].y = vertices[i].y * scale;
    }
    // 描画
    constexpr float dark = 1.0f;    // 暗い部分用
    constexpr float light = 0.25f;  // 明るい部分用
    constexpr float lineWeight = 1.0f;     // 線の太さ
    VECTOR4 col{ color.r, color.g, color.b, light };
    // 矩形を塗りつぶす
    const int32 nPolygon = vertexCount - 2; // 描画するポリゴン数
    GameLib::primitive::draw_triangle_fan(v.data(), col, nPolygon, true);
    // 線画
    GameLib::setBlendMode(GameLib::Blender::BS_NONE);
    // 始点→終点までの線画
    const int32 lineNum = vertexCount - 1;  // 始点→終点までの輪郭線の本数
    col.w = dark;
    for (int32 i = 0; i < lineNum; i++)
    {
        GameLib::primitive::line(v[i], v[i + 1], col, lineWeight, true);
    }
    // 終点→始点の線画
    const int32 end = vertexCount - 1;     // 終点のインデックス
    GameLib::primitive::line(v[end], v[0], col, lineWeight, true);
    // ブレンドステートを戻す
    GameLib::setBlendMode(oldState); 

	


}


void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	//const float32 k_segments = 16.0f;
	//const float32 k_increment = 2.0f * b2_pi / k_segments;
	//float32 theta = 0.0f;
	//glColor3f(color.r, color.g, color.b);
	//glBegin(GL_LINE_LOOP);
	//for (int32 i = 0; i < k_segments; ++i)
	//{
	//	b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
	//	glVertex2f(v.x, v.y);
	//	theta += k_increment;
	//}
	//glEnd();

	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール
	std::vector<VECTOR2> v;
	v.resize(k_segments);
	for (int32 i = 0; i < k_segments; ++i)
	{
		v[i].x = (center.x + radius * cosf(theta)) * scale;
		v[i].y = (center.y + radius * sinf(theta)) * scale;
		theta += k_increment;
	}

	// 始点→終点までの線画
	const int32 lineNum = k_segments - 1;  // 始点→終点までの輪郭線の本数
	VECTOR4 col{ color.r, color.g, color.b, 1.0f };
	for (int32 i = 0; i < lineNum; i++)
	{
		GameLib::primitive::line(v[i], v[i + 1], col, 1, true);
	}
	// 終点→始点の線画
	const int32 end = k_segments - 1;     // 終点のインデックス
	GameLib::primitive::line(v[end], v[0], col, 1, true);
}

float smoothstep(float x) { return x * x * (3 - 2 * x); }

void DebugDraw::DrawParticles(const b2Vec2 *centers, float32 radius, const b2ParticleColor *colors, int32 count)
{
	//static unsigned int particle_texture = 0;
	//
	//if (!particle_texture ||
	//		!glIsTexture(particle_texture)) // Android deletes textures upon sleep etc.
	//{
	//	// generate a "gaussian blob" texture procedurally
	//	glGenTextures(1, &particle_texture);
	//	b2Assert(particle_texture);
	//	const int TSIZE = 64;
	//	unsigned char tex[TSIZE][TSIZE][4];
	//	for (int y = 0; y < TSIZE; y++)
	//	{
	//		for (int x = 0; x < TSIZE; x++)
	//		{
	//			float fx = (x + 0.5f) / TSIZE * 2 - 1;
	//			float fy = (y + 0.5f) / TSIZE * 2 - 1;
	//			float dist = sqrtf(fx * fx + fy * fy);
	//			unsigned char intensity = (unsigned char)(dist <= 1 ? smoothstep(1 - dist) * 255 : 0);
	//			tex[y][x][0] = tex[y][x][1] = tex[y][x][2] = 128;
	//			tex[y][x][3] = intensity;
	//		}
	//	}
	//	glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, particle_texture);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	//	glDisable(GL_TEXTURE_2D);
	//
	//	glEnable(GL_POINT_SMOOTH);
	//}
	//
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, particle_texture);
	//
	//#ifdef __ANDROID__
	//	glEnable(GL_POINT_SPRITE_OES);
	//	glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);
	//#else
	//	glEnable(GL_POINT_SPRITE);
	//	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	//#endif
	//
	//const float particle_size_multiplier = 3;  // because of falloff
	//glPointSize(radius * currentscale * particle_size_multiplier);
	//
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(2, GL_FLOAT, 0, &centers[0].x);
	//if (colors)
	//{
	//	glEnableClientState(GL_COLOR_ARRAY);
	//	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &colors[0].r);
	//}
	//else
	//{
	//	glColor4f(1, 1, 1, 1);
	//}
	//
	//glDrawArrays(GL_POINTS, 0, count);
	//
	//glDisableClientState(GL_VERTEX_ARRAY);
	//if (colors) glDisableClientState(GL_COLOR_ARRAY);
	//
	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);
	//#ifdef __ANDROID__
	//	glDisable(GL_POINT_SPRITE_OES);
	//#endif


	if (count > 2048) count = 2048;     // とりあえず最大2048 
	GameLib::texture::begin(BLOB_PARTICLE);
    const float scale = GameLib::view::getBox2dScale();
    const float rate = scale / 24.0f;   // この数値は目視で調整したもの
	for (int32 i = 0; i < count; i++)
	{
		VECTOR4 col{ 0.0f, 0.7f, 1.0f, 0.8f };  // 適当に色を入れておく   
		if (colors)
		{
			col = { colors[i].r / 255.0f, colors[i].g / 255.0f, colors[i].b / 255.0f, 1 };
		}
		const VECTOR2 pos = VECTOR2(centers[i].x, centers[i].y) * scale;
		GameLib::texture::draw(BLOB_PARTICLE, pos, VECTOR2(radius, radius) * rate,
			VECTOR2(0, 0), VECTOR2(64, 64), VECTOR2(32, 32), 0, col, true);
	}
	GameLib::texture::end(BLOB_PARTICLE);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	//const float32 k_segments = 16.0f;
	//const float32 k_increment = 2.0f * b2_pi / k_segments;
	//float32 theta = 0.0f;
	//glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	//glBegin(GL_TRIANGLE_FAN);
	//for (int32 i = 0; i < k_segments; ++i)
	//{
	//	b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
	//	glVertex2f(v.x, v.y);
	//	theta += k_increment;
	//}
	//glEnd();
	//glDisable(GL_BLEND);
	//
	//theta = 0.0f;
	//glColor4f(color.r, color.g, color.b, 1.0f);
	//glBegin(GL_LINE_LOOP);
	//for (int32 i = 0; i < k_segments; ++i)
	//{
	//	b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
	//	glVertex2f(v.x, v.y);
	//	theta += k_increment;
	//}
	//glEnd();
	//
	//b2Vec2 p = center + radius * axis;
	//glBegin(GL_LINES);
	//glVertex2f(center.x, center.y);
	//glVertex2f(p.x, p.y);
	//glEnd();

	auto oldState = GameLib::getBlendMode();
	

	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール
	std::vector<VECTOR2> v;
	v.resize(k_segments);
	for (int32 i = 0; i < k_segments; ++i)
	{
		v[i].x = (center.x + radius * cosf(theta)) * scale;
		v[i].y = (center.y + radius * sinf(theta)) * scale;
		theta += k_increment;
	}
	VECTOR4 col{ color.r * 0.5f, color.g * 0.5f, color.b * 0.5f, 0.5f };
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	// 矩形を塗りつぶす
	const int32 nPolygon = k_segments - 2; // 描画するポリゴン数
	GameLib::primitive::draw_triangle_fan(v.data(), col, nPolygon, true);

	GameLib::setBlendMode(GameLib::Blender::BS_NONE);
	// 始点→終点までの線画
	const int32 lineNum = k_segments - 1;  // 始点→終点までの輪郭線の本数
	col = { color.r, color.g, color.b, 1.0f };
	for (int32 i = 0; i < lineNum; i++)
	{
		GameLib::primitive::line(v[i], v[i + 1], col, 1, true);
	}
	// 終点→始点の線画
	const int32 end = k_segments - 1;     // 終点のインデックス
	GameLib::primitive::line(v[end], v[0], col, 1, true);

	VECTOR2 p1 = { center.x * scale, center.y * scale };
	VECTOR2 p2 = { (center.x + radius * axis.x) * scale, (center.y + radius * axis.y) * scale };
	GameLib::primitive::line(p1, p2, col, 1, true);


	GameLib::setBlendMode(oldState);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	//glColor3f(color.r, color.g, color.b);
	//glBegin(GL_LINES);
	//glVertex2f(p1.x, p1.y);
	//glVertex2f(p2.x, p2.y);
	//glEnd();


	// スケールの適用
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール

	// 描画
	VECTOR4 col{ color.r, color.g, color.b, 1.0 };
	VECTOR2 v1 = { p1.x * scale, p1.y * scale };
	VECTOR2 v2 = { p2.x * scale, p2.y * scale };

	GameLib::primitive::line(v1, v2, col, 1, true);

}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	//b2Vec2 p1 = xf.p, p2;
	//const float32 k_axisScale = 0.4f;
	//glBegin(GL_LINES);
	//
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex2f(p1.x, p1.y);
	//p2 = p1 + k_axisScale * xf.q.GetXAxis();
	//glVertex2f(p2.x, p2.y);
	//
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex2f(p1.x, p1.y);
	//p2 = p1 + k_axisScale * xf.q.GetYAxis();
	//glVertex2f(p2.x, p2.y);
	//
	//glEnd();
	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール

	VECTOR2 p1 = { xf.p.x * scale, xf.p.y * scale};
	VECTOR2 p2;
	const float32 k_axisScale = 0.4f;
	VECTOR4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
	p2 = { (p1.x + k_axisScale * xf.q.GetXAxis().x) * scale ,
	(p1.y + k_axisScale * xf.q.GetXAxis().y) * scale };
	GameLib::primitive::line(p1, p2, color, 1, true);

	color = { 0.0f, 1.0f, 0.0f, 1.0f };
	p2 = { (p1.x + k_axisScale * xf.q.GetYAxis().x) * scale ,
	(p1.y + k_axisScale * xf.q.GetYAxis().y) * scale };
	GameLib::primitive::line(p1, p2, color, 1, true);
	    
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	//glPointSize(size);
	//glBegin(GL_POINTS);
	//glColor3f(color.r, color.g, color.b);
	//glVertex2f(p.x, p.y);
	//glEnd();
	//glPointSize(1.0f);

	GameLib::Blender::BLEND_STATE oldState = GameLib::getBlendMode();
	GameLib::setBlendMode(GameLib::Blender::BS_NONE);

	const float scale = GameLib::view::getScale();
	const float b2Scale = GameLib::view::getBox2dScale();
	const VECTOR2 c = { p.x * b2Scale, p.y * b2Scale };
    const VECTOR2 s = { size / scale, size / scale };
    const VECTOR4 col = { color.r, color.g, color.b, 1.0f };
    GameLib::primitive::rect(c, s, s / 2, 0.0f, col, true);
    setBlendMode(oldState);

}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
#if !defined(__ANDROID__) && !defined(__IOS__)
	//char buffer[128];

	//va_list arg;
	//va_start(arg, string);
	//vsprintf(buffer, string, arg);
	//va_end(arg);
	//
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//int w = glutGet(GLUT_WINDOW_WIDTH);
	//int h = glutGet(GLUT_WINDOW_HEIGHT);
	//LoadOrtho2DMatrix(0, w, h, 0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();
	//
	//glColor3f(0.9f, 0.6f, 0.6f);
	//glRasterPos2i(x, y);
	//int32 length = (int32)strlen(buffer);
	//for (int32 i = 0; i < length; ++i)
	//{
	//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
	//	//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer[i]);
	//}
	//
	//glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
#endif // !defined(__ANDROID__) && !defined(__IOS__)



	char str[256];
	vsprintf_s(str, string, reinterpret_cast<char*>(&string + 1));
	GameLib::font::textOut(0, str, static_cast<float>(x), static_cast<float>(y), 1, 1,
    	1, 1, 1, 1, GameLib::TEXT_ALIGN::UPPER_LEFT, false);



}

void DebugDraw::DrawString(const b2Vec2& p, const char *string, ...)
{
#if !defined(__ANDROID__) && !defined(__IOS__)
	//char buffer[128];
	//
	//va_list arg;
	//va_start(arg, string);
	//vsprintf(buffer, string, arg);
	//va_end(arg);
	//
	//glColor3f(0.5f, 0.9f, 0.5f);
	//glRasterPos2f(p.x, p.y);
	//
	//int32 length = (int32)strlen(buffer);
	//for (int32 i = 0; i < length; ++i)
	//{
	//	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	//}
	//
	//glPopMatrix();
#endif // !defined(__ANDROID__) && !defined(__IOS__)

}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	//glColor3f(c.r, c.g, c.b);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
	//glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
	//glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
	//glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
	//glEnd();

	const float scale = GameLib::view::getBox2dScale();// Box2Dのスケール

	VECTOR2 v[4] = { {aabb->lowerBound.x * scale, aabb->lowerBound.y * scale},
	{aabb->lowerBound.x * scale, aabb->upperBound.y * scale},
	{aabb->upperBound.x * scale, aabb->upperBound.y * scale},
	{aabb->upperBound.x * scale, aabb->lowerBound.y * scale} };

    VECTOR4 color = { c.r, c.g, c.b, 1.0f };

	// 始点→終点までの線画;
	for (int32 i = 0; i < 3; i++)
	{
		GameLib::primitive::line(v[i], v[i + 1], color, 1, true);
	}

	GameLib::primitive::line(v[3], v[0], color, 1, true);

}

float ComputeFPS()
{
	//static bool debugPrintFrameTime = false;
	//static int lastms = 0;
	//int curms = glutGet(GLUT_ELAPSED_TIME);
	//int delta = curms - lastms;
	//lastms = curms;
	//
	//static float dsmooth = 16;
	//dsmooth = (dsmooth * 30 + delta) / 31;
	//
	//if ( debugPrintFrameTime )
	//{
#ifdef ANDROID
		//__android_log_print(ANDROID_LOG_VERBOSE, "Testbed", "msec = %f", dsmooth);
#endif
	//}

	return 16;
}
