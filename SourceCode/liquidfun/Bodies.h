#pragma once

#ifndef BODIES_H
#define BODIES_H

#include "Test.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Bodies : public Test
{
public:
    //in the class itself, not inside the constructor!
    b2Body* dynamicBody;
public:
    Bodies()
    {
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        myBodyDef.position.Set(0, 20);
        myBodyDef.active = true;

        dynamicBody = m_world->CreateBody(&myBodyDef);


        b2PolygonShape boxShape;
        boxShape.SetAsBox(1, 1);

        b2FixtureDef boxFixtureDef;
        boxFixtureDef.shape = &boxShape;
        boxFixtureDef.density = 1;
        dynamicBody->CreateFixture(&boxFixtureDef); 

        //45 degrees counter-clockwise
        dynamicBody->SetTransform(b2Vec2(10, 20), 45 * DEGTORAD);

        dynamicBody->SetLinearVelocity(b2Vec2(-5, 5)); //moving up and left 5 units per second
        dynamicBody->SetAngularVelocity(-90 * DEGTORAD); //90 degrees per second clockwise

        myBodyDef.type = b2_staticBody; //this will be a static body
        myBodyDef.position.Set(0, 10); //slightly lower position
        b2Body* staticBody = m_world->CreateBody(&myBodyDef); //add body to world
        staticBody->CreateFixture(&boxFixtureDef); //add fixture to body

        myBodyDef.type = b2_kinematicBody; //this will be a kinematic body
        myBodyDef.position.Set(-18, 11); // start from left side, slightly above the static body
        b2Body* kinematicBody = m_world->CreateBody(&myBodyDef); //add body to world
        kinematicBody->CreateFixture(&boxFixtureDef); //add fixture to body

        kinematicBody->SetLinearVelocity(b2Vec2(1, 0)); //move right 1 unit per second
        kinematicBody->SetAngularVelocity(360 * DEGTORAD); //1 turn per second counter-clockwise


    }

    void Step(Settings* settings)
    {
        Test::Step(settings);

        b2Vec2 pos = dynamicBody->GetPosition();
        float angle = dynamicBody->GetAngle();
        b2Vec2 vel = dynamicBody->GetLinearVelocity();
        float angularVel = dynamicBody->GetAngularVelocity();
        m_debugDraw.DrawString(5, m_textLine,
            "Position:%.3f,%.3f Angle:%.3f", pos.x, pos.y, angle * RADTODEG);
        m_textLine += 15;
        m_debugDraw.DrawString(5, m_textLine,
            "Velocity:%.3f,%.3f Angular velocity:%.3f", vel.x, vel.y, angularVel * RADTODEG);
        m_textLine += 15;
    }

    static Test* Create()
    {
        return new Bodies;
    }
};
#endif
