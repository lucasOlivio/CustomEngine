#include "pch.h"
#include "Math.h"

namespace MyEngine
{
    void WrapMinMax(int min, int max, int& numOut)
    {
        if (numOut < min)
        {
            numOut = max;
        }
        else if (numOut > max)
        {
            numOut = min;
        }
    }

    void WrapMinMax(float min, float max, float& numOut)
    {
        if (numOut < min)
        {
            numOut = max;
        }
        else if (numOut > max)
        {
            numOut = min;
        }
    }
}
