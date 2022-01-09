#include "grid.h"
#include "../GameLib/game_lib.h"

using namespace GameLib;

int Grid::num = 20;

void Grid::setNum(int n)
{
    num = n;
}

void Grid::draw()
{
    const float b2Scale = view::getBox2dScale();
    primitive_batch::begin();
    for (int i = -num; i <= num; i++)
    {
        if (!i) continue;
        float alpha = 0.4;
        if (i % 5 == 0) alpha = 1;

        //c
        primitive_batch::line(VECTOR2(b2Scale * i, -b2Scale * num),
            VECTOR2(b2Scale * i, b2Scale * num), VECTOR4(1, 1, 1, alpha), 1, true);
        //‰¡
        primitive_batch::line(VECTOR2(-b2Scale * num, b2Scale * i),
            VECTOR2(b2Scale * num, b2Scale * i), VECTOR4(1, 1, 1, alpha), 1, true);
    }

    //Ž²
    primitive_batch::line(VECTOR2(0, -b2Scale * num),
        VECTOR2(0, b2Scale * num),VECTOR4(0,1,0,1),1,true);
    primitive_batch::line(VECTOR2(-b2Scale * num, 0),
        VECTOR2(b2Scale * num,0), VECTOR4(1, 0, 0, 1), 1, true);

    primitive_batch::end();

}

