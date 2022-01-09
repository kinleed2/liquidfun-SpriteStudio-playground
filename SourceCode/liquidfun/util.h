
#pragma once

#include "Test.h"

class Util
{
public:
    static b2Body* CreateBody(b2World* world, b2BodyType bodyType, b2Vec2 pos)
    {
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position = pos;
        return world->CreateBody(&bodyDef);
    }

    static b2Body* CreateCircle(b2World* world, b2BodyType bodyType, b2Vec2 bodyPos, float radius)
    {
        b2Body* body = CreateBody(world, bodyType, bodyPos);

        b2CircleShape circleShape;
        circleShape.m_p.Set(0,0); //position, relative to body position
        circleShape.m_radius = radius; //radius

        b2FixtureDef myFixtureDef;
        myFixtureDef.density = 1;
        myFixtureDef.shape = &circleShape;
        body->CreateFixture(&myFixtureDef);

        return body;
    }

    static b2Body* CreatePolygon(b2World* world, b2BodyType bodyType, b2Vec2 bodyPos, b2Vec2* vertices, int vertex_count)
    {
        b2Body* body = CreateBody(world, bodyType, bodyPos);

        b2PolygonShape polygon_shape;
        polygon_shape.Set(vertices, vertex_count);

        b2FixtureDef myFixtureDef;
        myFixtureDef.density = 1;
        myFixtureDef.shape = &polygon_shape;
        body->CreateFixture(&myFixtureDef);

        return body;
    }

    static b2Body* CreateBox(b2World* world, b2BodyType bodyType, b2Vec2 bodyPos, b2Vec2 box_size)
    {
        b2Body* body = CreateBody(world, bodyType, bodyPos);

        b2PolygonShape polygon_shape;
        polygon_shape.SetAsBox(box_size.x, box_size.y);

        b2FixtureDef myFixtureDef;
        myFixtureDef.density = 1;
        myFixtureDef.shape = &polygon_shape;
        body->CreateFixture(&myFixtureDef);

        return body;
    }

    static b2Body* CreateEdge(b2World* world, b2BodyType bodyType, b2Vec2 start_pos, b2Vec2 end_pos)
    {
        b2Body* body = CreateBody(world, bodyType, {0,0});

        b2FixtureDef myFixtureDef;
        b2EdgeShape edgeShape;
        edgeShape.Set(start_pos, end_pos);
        myFixtureDef.shape = &edgeShape;
        body->CreateFixture(&myFixtureDef); //add a fixture to the body
        return body;
    }


    static void AddCircleFixture(b2Body* body, b2Vec2 pos/*relative to body position*/, float radius, b2FixtureDef* myFixtureDef)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(pos.x,pos.y);
        circleShape.m_radius = radius;

        myFixtureDef->shape = &circleShape;
        body->CreateFixture(myFixtureDef);
    }

    static void AddBoxFixture(b2Body* body, b2Vec2 pos/*relative to body position*/, b2Vec2 box_size, b2FixtureDef* myFixtureDef)
    {

        b2PolygonShape polygon_shape;
        polygon_shape.SetAsBox(box_size.x, box_size.y,pos,0);
        myFixtureDef->shape = &polygon_shape;
        body->CreateFixture(myFixtureDef);

    }

    static void AddPolygonFixture(b2Body* body, b2Vec2 pos/*relative to body position*/, b2Vec2* vertices, int vertex_count)
    {
        for (int i = 0; i < vertex_count; i++)
        {
            vertices[i] += pos;
        }
        b2PolygonShape polygon_shape;
        polygon_shape.Set(vertices, vertex_count);

        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygon_shape;
        body->CreateFixture(&myFixtureDef);
    }
};
