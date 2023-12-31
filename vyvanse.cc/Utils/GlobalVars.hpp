#pragma once
#include <cstddef>

namespace cs2
{
    struct GlobalVars {
        const float realtime;
        const int framecount;
        const float absoluteFrameTime;
        const std::byte pad[4];
        float currenttime;
        float frametime;
        const int maxClients;
        const int tickCount;
        const float intervalPerTick;
    };
}