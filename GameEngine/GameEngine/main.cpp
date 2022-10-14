// Add your System.h include file here
#include "System.h"
#include "EngineState.h"
//#include "GameObject.h"
//#include "World.h"

void runMainLoop(EngineState* engine);
void handleEvents(void* engine);
void frameStep(void* arg);
Uint32 GetTicks();

void CreateGameObjects(EngineState* engine);

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    gpr460::System system;
    system.Init();

    //int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //system.Init();
    system.SetMemoryCheckpoint();

    /*THESE BRACKETS ARE CAUSING SCALAR THING*/
    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = &system;

    CreateGameObjects(&engine);

    runMainLoop(&engine);

    engine.ShutDown();
    //system.ShutDown();
    system.ShutDown();
    system.GetMemoryCheckpoint();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void runMainLoop(EngineState* engine)
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(handleEvents, engine, 0, true);
#else
    while (!engine->quit)
    {
        handleEvents(engine);
    }
#endif
    
}

void handleEvents(void* engine)
{
    Uint32 now = GetTicks();
    if (now - ((EngineState*)engine)->frameStart >= 16)
    {
        frameStep(engine);
    }
}

void frameStep(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    Uint32 now = GetTicks();

    engine->frame++;
    engine->frameStart = now;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            engine->quit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);
    
    engine->Update(engine);

    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}

/* Using Structure of Arrays all components end up next to eachother in memory*/

void CreateGameObjects(EngineState* engine)
{
    // Each create compnent allocates _some_ memory
    //  Memory consumption probably isnt a concern -- but
    //  where do each of our new allocations 
    
    engine->world.CreateGameObject("Player", Transform(Vector2(0, 100)));
    engine->world.CreateGameObject("Collided", Transform(Vector2(100, 0)));
    engine->world.CreateGameObject("BackGround", Transform(Vector2(200, 300)));

    engine->world.AddPlayerController(0, PlayerController());
    engine->world.AddRectangleRenderer(0, RectangleRenderer(50, 50, Color(0, 255, 255, 255)));
    engine->world.AddCollisionColorChanger(0, CollisionColorChanger());
    engine->world.AddRectangleCollider(0, RectangleCollider());

    engine->world.AddRectangleRenderer(1, RectangleRenderer(50, 50, Color(100, 0, 255, 255)));
    engine->world.AddRectangleCollider(1, RectangleCollider());
    engine->world.AddCollisionColorChanger(1, CollisionColorChanger());

    engine->world.AddRectangleRenderer(2, RectangleRenderer(100, 100, Color(100, 255, 100, 255)));
    
    /************Old Way of creating Game Objects************/
    /*engine->gameObjects.push_back(new GameObject("Player", Transform(Vector2(0, 100))));
    engine->gameObjects.push_back(new GameObject("Collided", Transform(Vector2(100, 0))));
    engine->gameObjects.push_back(new GameObject("BackGround", Transform(Vector2(200, 300))));

    engine->gameObjects[0]->CreateRenderer(new RectangleRenderer(50, 50, Color(0, 255, 255, 255)));
    engine->gameObjects[0]->CreateCollider(new RectangleCollider());
    engine->gameObjects[0]->CreatePlayerController(new PlayerController());
    engine->gameObjects[0]->CreateColliderColorChanger(new CollisionColorChanger());

    engine->gameObjects[1]->CreateRenderer(new RectangleRenderer(50, 50, Color(100, 255, 100, 255)));
    engine->gameObjects[1]->CreateCollider(new RectangleCollider());
    engine->gameObjects[1]->CreateColliderColorChanger(new CollisionColorChanger());

    engine->gameObjects[2]->CreateRenderer(new RectangleRenderer(75, 75, Color(200, 50, 175, 255)));*/

    // have a bunch of game objects laid out like this:
    //   Player: [ptrToAllComponents]
}