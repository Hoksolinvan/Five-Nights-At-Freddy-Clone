#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>



class MainMenu{
    srand(time(0));
    public:



    private:
  

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);
    std::uniform_int_distribution<int> random_number(0,100);
};