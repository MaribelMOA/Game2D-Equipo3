#pragma once

#include "Estructuras.hpp"
#include<vector>
#include<string>
#include<SDL.h>

#define DEBUG
#define PI 3.1416

#ifdef DEBUG
    #define DEBUGPRINT(X) std::cout<<"\x1B[34m " << X <<"\x1B[0m"<<std::endl;
    #define DEBUGCOOR(P1) std::cout<<"\x1B[34m (" <<P1.x <<", "<<P1.y <<")\x1B[0m"<<std::endl;
    #define DEBUGLINEA(P1,P2) std::cout<<"\x1B[32m (" <<P1.x <<", "<<P1.y<<") -- ("<<P2.x<<", "<<P2.y <<")\x1B[0m"<<std::endl;
#else
    #define DEBUGPRINT(X) do {}while(0)
    #define DEBUGCOOR(X) do {}while(0)
    #define DEBUGLINEA(X) do {}while(0)
#endif

bool tiene_determinante(Coordenadas p1,Coordenadas p2,Coordenadas p3,Coordenadas p4);

Coordenadas interseccion(Coordenadas p1,Coordenadas p2,Coordenadas p3,Coordenadas p4);

float CCW(Coordenadas A,Coordenadas B,Coordenadas C);

bool tiene_interseccion(Coordenadas p1,Coordenadas p2,Coordenadas p3,Coordenadas p4);

int coordenada_maxima(std::vector<Coordenadas> vertices,char eje);

int coordenada_minima(std::vector<Coordenadas> vertices,char eje);

std::vector<Coordenadas> sort_insertion(std::vector<Coordenadas> lista,char eje);

std::vector<Coordenadas> wrapper_sort(std::vector<Coordenadas> vec,char e,std::vector<Coordenadas> (*algoritmo)(std::vector<Coordenadas> lista,char eje));

Coordenadas LERP(Coordenadas p1, Coordenadas p2, float t);

Coordenadas ROTAR(double radianes,Coordenadas P);

Coordenadas TRASLADAR(Coordenadas A, Coordenadas B);