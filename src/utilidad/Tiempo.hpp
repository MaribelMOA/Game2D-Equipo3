#pragma once
#include<chrono>

class Tiempo
{
    public:
        static std::chrono::time_point<std::chrono::steady_clock> tiempo_inicial;
        static double get_tiempo();
};