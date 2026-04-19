#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <random>
#include <algorithm>
#include <iostream>

const int window_x = 1000;
const int window_y = 1000;
bool running = true;
bool main_menu = true;
bool default_main_menu = true;
int main_menu_state =0;


int main(int argc, char* argv[]){

    

    

    SDL_Event event;
    

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        std::cerr << SDL_GetError() << "\n";

        return -1;
    }


    // Load the WAV file
SDL_AudioSpec spec;
Uint8* wav_data;
Uint32 wav_length;
SDL_LoadWAV("assets/sounds/static.wav", &spec, &wav_data, &wav_length);

SDL_AudioSpec spec2;
Uint8* wav_data2;
Uint32 wav_length2;
SDL_LoadWAV("assets/sound/static2.wav",&spec2,&wav_data2,&wav_length2);

// Create a stream and bind it to the default device
SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(
    SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL
);


// Put the audio data into the stream
SDL_PutAudioStreamData(stream, wav_data, wav_length);
SDL_PutAudioStreamData(stream, wav_data2, wav_length2);



    SDL_Window* window = SDL_CreateWindow(
        "Fnaf 1 Clone",
        window_x,
        window_y,
        0
    );

    if(!window){
        SDL_Quit();
        std::cerr << SDL_GetError() << "\n";
        return -1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_FRect dest = {0, 0, static_cast<float>(w*1.5), (float)h};

    SDL_Renderer* renderer = SDL_CreateRenderer(window,nullptr);


    if(!renderer){
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::cerr << SDL_GetError() << "\n";
        return -1;
    }


    // Main Menu Texture images
    SDL_Surface* surface = IMG_Load("assets/static_and_menu/Menu/431.png");
    SDL_Surface* surface2 = IMG_Load("assets/static_and_menu/Menu/440.png");
    SDL_Surface* surface3 = IMG_Load("assets/static_and_menu/Menu/441.png");
    SDL_Surface* surface4 = IMG_Load("assets/static_and_menu/Menu/442.png");

    SDL_Texture* textures[4]= {SDL_CreateTextureFromSurface(renderer, surface),
                                SDL_CreateTextureFromSurface(renderer, surface2),
                                SDL_CreateTextureFromSurface(renderer, surface3),
                                SDL_CreateTextureFromSurface(renderer, surface4)};

        
    SDL_DestroySurface(surface);
    SDL_DestroySurface(surface2);
    SDL_DestroySurface(surface3);
    SDL_DestroySurface(surface4);


    // Full-Static Background Texture images

    int static_counter = 0;

    const char* path[9]= {
        "assets/static_and_menu/Full_Static/12.png",
        "assets/static_and_menu/Full_Static/13.png",
        "assets/static_and_menu/Full_Static/14.png",
        "assets/static_and_menu/Full_Static/15.png",
        "assets/static_and_menu/Full_Static/16.png",
        "assets/static_and_menu/Full_Static/17.png",
        "assets/static_and_menu/Full_Static/18.png",
        "assets/static_and_menu/Full_Static/19.png",
        "assets/static_and_menu/Full_Static/20.png"
    };

    SDL_Texture* static_textures[9];

    for(int i=0; i<9;i++){
        SDL_Surface* temp_texture = IMG_Load(path[i]);
        static_textures[i]=SDL_CreateTextureFromSurface(renderer,temp_texture);
       SDL_SetTextureAlphaMod(static_textures[i], 50);

        SDL_DestroySurface(temp_texture);
    }
       






    Uint64 last_time = SDL_GetTicks();

    uint32_t frame =0;

    while(running){
        frame++;

        SDL_RenderClear(renderer);
        Uint64 now = SDL_GetTicks();
        float dt = (now - last_time) / 1000.0f;
        last_time = now;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }

        }

        
        if(main_menu){

           SDL_ResumeAudioStreamDevice(stream);

           if (SDL_GetAudioStreamAvailable(stream) < (int)wav_length+wav_length2) {
    SDL_PutAudioStreamData(stream, wav_data, wav_length);
    SDL_PutAudioStreamData(stream, wav_data2, wav_length2);
}



           

            if(default_main_menu){
            
            SDL_RenderTexture(renderer, textures[0], NULL, &dest);
            }
            else{

                switch(main_menu_state){
                    case 1:
                    if(frame<=400){
                        SDL_RenderTexture(renderer, textures[1], NULL, &dest);
                    }
                    else if(frame <=500){
                        SDL_RenderTexture(renderer, textures[2], NULL, &dest);
                    }
                    else if(frame<=700){
                        SDL_RenderTexture(renderer, textures[1], NULL, &dest);
                    }
                    else if(frame<=900){
                        SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    }
                    break;

                    case 2:
                    if(frame<=100){
                        SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    }
                    else if(frame <=200){
                        SDL_RenderTexture(renderer, textures[3], NULL, &dest);
                    }
                    else if(frame <=300){
                        SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    }
                    else if(frame <=400){
                        SDL_RenderTexture(renderer, textures[3], NULL, &dest);
                    }
                    else if(frame <=500){
                        SDL_RenderTexture(renderer, textures[2], NULL, &dest);
                    }
                    else if(frame <=900){
                        SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    }   
                    break;

                    case 3:
                    if(frame <=400){
                        SDL_RenderTexture(renderer, textures[3], NULL, &dest);
                    }
                    else if(frame<=700){
                        SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    }
                    else if(frame<=900){
                        SDL_RenderTexture(renderer, textures[1], NULL, &dest);
                    }
                    break;
                    default:
                    SDL_RenderTexture(renderer, textures[0], NULL, &dest);
                    break;



                }


            }

             

            if(!(frame%900)){
                frame = 0;
                if(random_number(gen) <= 50){
                    default_main_menu=true;
                }
                else{
                    default_main_menu=false;
                    main_menu_state = dist(gen);
                }

            }

            // if(now % 100 <= 16){
            //     static_counter = (static_counter + 1) % 9;
            // }
            SDL_RenderTexture(renderer, static_textures[(rand()+1) % 9], NULL, &dest);

            //SDL_RenderTexture(renderer,static_textures[static_counter],NULL,&dest);
        }








        SDL_RenderPresent(renderer);
    }





    // Clean up

   SDL_DestroyAudioStream(stream);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}