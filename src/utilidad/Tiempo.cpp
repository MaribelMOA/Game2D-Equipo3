#include "Tiempo.hpp"

/*
Toda variable estática se debe de inicializar antes que todo
*/
std::chrono::time_point<std::chrono::steady_clock> Tiempo::tiempo_inicial = std::chrono::steady_clock::now();

double Tiempo::get_tiempo()
{
    auto tiempo_final = std::chrono::steady_clock::now();
    std::chrono::duration<double> tiempo = tiempo_final-tiempo_inicial;

    return tiempo.count();
};