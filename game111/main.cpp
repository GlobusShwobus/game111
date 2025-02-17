#include <fstream>
#include "JSON_Config.h"
#include "Texture_Manager.h"
#include "RenderWindow.h"

/*
1. make a png for ground obj
2. make basic enemey png
3. make player png
4. make bullet png

5. make bounding box
6. fix config
7. make entity class
8. make manager

9. draw it on the screen

10. make movement
11. make collison

*/

struct WindowInit {

    std::string title;
    unsigned int width = 0;
    unsigned int height = 0;

    WindowInit(const nlohmann::json& json) {

        auto& wStuff = json["Window"];

        title = wStuff["game_name"];
        width = wStuff["width"];
        height = wStuff["height"];
    }
};


int main() {

    //initialize config and file manager, (and window but probably should move window at some point)
    FileManager fileman;
    JSONConfig config;

    config.Init(fileman.GetEntityConfig("Config.json"));
    
    if (!config.Good()) {
        MessageBox(nullptr, L"Config failed init", L"error init", MB_OK | MB_ICONERROR);
        return -1;
    }

    WindowInit wParams(config.Get());

    //initalize SDL and RenderWIndow
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        MessageBox(nullptr, L"SDL init fail", L"error init", MB_OK | MB_ICONERROR);
        return -1;
    }

    RenderWindow window(wParams.title.c_str(), wParams.width, wParams.height);

    if (!window.Good()) {
        MessageBox(nullptr, L"Window failed init", L"error init", MB_OK | MB_ICONERROR);
        return -1;
    }

    //initialize TextureManager

    TextureManager textman;
    textman.InitializeTextures(fileman.GetTextureFolderContents("../Textures"), window.GetRenderer());






    bool gameRunning = true;
    SDL_Event event;



    while (gameRunning) {

        SDL_PollEvent(&event);

        if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
            gameRunning = false;
        }

        window.Clear();
        window.Display();

    }


    window.~RenderWindow();
    SDL_Quit();
    
    return 0;
}
