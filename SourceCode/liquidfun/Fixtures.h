#pragma once

#include "Test.h"
#include "util.h"

class Fixtures : public Test
{
public:
    Fixtures()
    {
       /* GameLib::view::setScale(0.7f);
        GameLib::view::setCenter(GameLib::view::box2dToWorld(b2Vec2(0, 0.8f)));

        b2Body* body = Util::CreateBody(m_world, b2_dynamicBody, b2Vec2(0, 0));

        Util::AddCircleFixture(body, b2Vec2(-10, 20), 1);
        b2Vec2 vertices[5];
        vertices[0].Set(-1, 2);
        vertices[1].Set(-1, 0);
        vertices[2].Set(-1, -3);
        vertices[3].Set(1, 0);
        vertices[4].Set(1, 1);
        Util::AddPolygonFixture(body, b2Vec2(0, 20), vertices, 5);
        Util::AddBoxFixture(body, b2Vec2(10, 20), b2Vec2(2, 1));
        Util::CreateEdge(m_world, b2_staticBody, b2Vec2(-15, 0), b2Vec2(15, 0));*/


    }
    void Step(Settings* settings)
    {
        Test::Step(settings);
    }

    static Test* Create()
    {
        return new Fixtures;
    }
};