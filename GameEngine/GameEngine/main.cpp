// Add your System.h include file here
#include "System.h"
#include "EngineState.h"
#include "StackAllocator.h"
#include "EditorGui.h"

void runMainLoop(EngineState* engine);
void handleEvents(void* engine);
void frameStep(void* arg);
Uint32 GetTicks();

void FrameAllocator(EngineState* engine);
void CreateGameObjects(EngineState* engine);

int main(int argc, char* argv[])
{
    const int WIDTH = 1280;
    const int HEIGHT = 960;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    gpr460::System system;
    system.Init();

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.InitGui(window, renderer);
    system.GameStart();

    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = &system;

    engine.world.LoadLevel("level0.dat");
    
    runMainLoop(&engine);

    //save the game to a file.
    engine.world.SaveLevel("level0.dat");

    engine.world.ShutDown();
    engine.ShutDown();
    
    system.ShutDown();
    system.GameEnd();

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
        engine->PollGuiEvents(event);

        if (event.type == SDL_QUIT)
        {
            engine->quit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
                std::cout << "Exit\n";
            }
        }
    }

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);
    
    FrameAllocator(engine);
    engine->Update(engine);

    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}

void FrameAllocator(EngineState* engine)
{
    engine->objectPool.clear();

    int i, numCollisions = 0, j = 0;

    for (i = 0; i < engine->world.numActiveRectangleColliders; i++)
        if (engine->world.rectangleColliders[i].GetColliding())
            numCollisions++;

    if (numCollisions == 0)
        return;

    RectangleCollider* collidersColliding = engine->objectPool.alloc<RectangleCollider>(numCollisions);

    Vector2* collidingPositions = engine->objectPool.alloc<Vector2>(numCollisions);

    for (i = 0; i < engine->world.numActiveRectangleColliders; i++)
        if (engine->world.rectangleColliders[i].GetColliding())
        {
            collidersColliding[j] = engine->world.rectangleColliders[i];
            collidingPositions[j] = engine->world.rectangleColliders[i].owner->GetTransform()->position;
            j++;
        }

    for (i = 0; i < numCollisions; i++)
        std::cout << collidingPositions[i].x << " " << collidingPositions[i].y << std::endl;
}

/* Using Structure of Arrays all components end up next to eachother in memory*/

void CreateGameObjects(EngineState* engine)
{
    // Each create compnent allocates _some_ memory
    //  Memory consumption probably isnt a concern -- but
    //  where do each of our new allocations 

    /******** Player *********/
    if (!engine->world.CreateGameObject("Player", Transform(Vector2(300, 300))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddPlayerController(0, PlayerController()))
    {
        engine->system->ErrorMessage(gpr460::MAX_PLAYER_CONTROLLERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_PLAYER_CONTROLLERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(0, RectangleRenderer(50, 50, Color(0, 255, 255, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(0, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(0, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }
    /******** Player *********/

    /******** Collider *********/
    if (!engine->world.CreateGameObject("Collided", Transform(Vector2(100, 0))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(1, RectangleRenderer(50, 50, Color(100, 0, 255, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(1, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(1, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }
    /******** Collider *********/

    /******** Background *********/
    if (!engine->world.CreateGameObject("BackGround", Transform(Vector2(200, 300))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(2, RectangleRenderer(100, 100, Color(100, 255, 100, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }
    /******** Background *********/

    /******** Extra Objs ********/
    if (!engine->world.CreateGameObject("Obj1", Transform(Vector2(100, 200))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(3, RectangleRenderer(50, 50, Color(255, 0, 0, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(3, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(3, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.CreateGameObject("Obj2", Transform(Vector2(25, 200))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(4, RectangleRenderer(50, 50, Color(100, 255, 50, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(4, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(4, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.CreateGameObject("Obj3", Transform(Vector2(100, 275))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(5, RectangleRenderer(50, 50, Color(255, 0, 0, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(5, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(5, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.CreateGameObject("Obj4", Transform(Vector2(25, 275))))
    {
        engine->system->ErrorMessage(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_GAME_OBJECTS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleRenderer(6, RectangleRenderer(50, 50, Color(100, 255, 50, 255))))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_RENDERERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddRectangleCollider(6, RectangleCollider()))
    {
        engine->system->ErrorMessage(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_RECTANGLE_COLLIDERS_ERROR);
        engine->quit = true;
        return;
    }

    if (!engine->world.AddCollisionColorChanger(6, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->quit = true;
        return;
    }

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