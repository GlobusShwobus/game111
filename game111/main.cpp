#include <fstream>
#include "JSON_Config.h"
#include "Texture_Manager.h"
#include "Entity_Manager.h"
#include "RenderWindow.h"

/*
spawn player with right click
despawn player with left click

figure a way to make map manager
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

    for (const auto& paths : fileman.GetTextureFolderContents("../Textures")) {

        SDL_Texture* passownershiptoidkdoireallycareifsomeonereadsthis = window.UniqueTextureLoad(paths.string().c_str());

        textman.InitializeTexture(paths.stem().string(), passownershiptoidkdoireallycareifsomeonereadsthis);


    }

    //initialize EntityManager

    EntityManager entman;




    //main game loop

    bool gameRunning = true;
    SDL_Event event;


    while (gameRunning) {

        entman.Update();


        SDL_PollEvent(&event);

        if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
            gameRunning = false;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {

                for (auto& ent : entman.GetEntities()) {

                    ent->Kill();

                }

            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {

                entman.AddEntity(*config.Get("Player"), EntityType::player, textman);

            }
        }


        window.Clear();

        for (auto& ent : entman.GetEntities()) {
            window.Render(ent->GetTexture(), ent->GetBB());
        }

        int cont_size = entman.GetEntities().size();
        printf("\n%s%d", "Entity size: ", cont_size);


        window.Display();

    }


    window.~RenderWindow();
    SDL_Quit();
    
    return 0;
}
