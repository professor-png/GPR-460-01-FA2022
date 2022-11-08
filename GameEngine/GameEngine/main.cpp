// Add your System.h include file here
#include "System.h"
#include "EngineState.h"
#include "StackAllocator.h"

void runMainLoop(EngineState* engine);
void handleEvents(void* engine);
void frameStep(void* arg);
Uint32 GetTicks();

void FrameAllocator(EngineState* engine, int x);
void CreateGameObjects(EngineState* engine);

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    gpr460::System system;
    system.Init();

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    system.GameStart();

    //StackAllocator stack;
    //Vector2* pt;
    //GameObject* gameO;

    //pt = stack.alloc<Vector2>(5);
    //pt[1] = Vector2(50, 10);

    //gameO = (GameObject*)stack.alloc<GameObject>();
    //gameO = new (gameO) GameObject("Player", Transform(Vector2(0, 100)));
    //std::cout << gameO << "\n";
    ////*gameO = GameObject();
    ////gameO->SetName("player");
    ////gameO = new GameObject("Player", Transform(Vector2(0, 100)));
    ////std::cout << gameO << "\n";
    ////std::cout << gameO->GetTransform()->position.x << std::endl;

    //if (pt == nullptr)
    //    std::cout << "null\n";
    //else
    //{
    //    std::cout << "not null\n";
    //    std::cout << pt[1].x << " " << pt[1].y << std::endl;
    //}

    //if (gameO == nullptr)
    //    std::cout << "not object\n";
    //else
    //{
    //    std::cout << gameO->GetName() << " object\n";
    //    //delete gameO;
    //}
    //stack.clear();

    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = &system;

    CreateGameObjects(&engine);

    runMainLoop(&engine);

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

    engine->gameObjects.clear();
    engine->objectPool.clear();

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
                std::cout << "Exit\n";
            }
        }
    }

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);
    
    FrameAllocator(engine, 50);
    engine->Update(engine);

    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}

void FrameAllocator(EngineState* engine, int x)
{
    //engine->gameObjects.clear();
    //engine->objectPool.clear();

    GameObject* tmpObj;
    RectangleRenderer* tmpRenderer;
    RectangleCollider* tmpCollider;
    CollisionColorChanger* tmpColor;

    x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200;
    int x2 = (SDL_cosf(engine->frame / 100.0f) * 100.0f) + 100;

    /*OBJECT 1*/
    tmpObj = (GameObject*)engine->objectPool.alloc<GameObject>();
    tmpObj = new (tmpObj) GameObject("Obj1", Transform(Vector2(x, 200)));
    engine->gameObjects.push_back(tmpObj);

    tmpRenderer = (RectangleRenderer*)engine->objectPool.alloc<RectangleRenderer>();
    tmpRenderer = new (tmpRenderer) RectangleRenderer(50, 50, Color(255, 0, 0, 255));
    engine->gameObjects[0]->CreateRenderer(tmpRenderer);

    tmpCollider = (RectangleCollider*)engine->objectPool.alloc<RectangleCollider>();
    tmpCollider = new (tmpCollider) RectangleCollider();
    engine->gameObjects[0]->CreateCollider(tmpCollider);

    tmpColor = (CollisionColorChanger*)engine->objectPool.alloc<CollisionColorChanger>();
    tmpColor = new (tmpColor) CollisionColorChanger();
    engine->gameObjects[0]->CreateColliderColorChanger(tmpColor);

    /*OBJECT 2*/
    tmpObj = (GameObject*)engine->objectPool.alloc<GameObject>();
    tmpObj = new (tmpObj) GameObject("Obj2", Transform(Vector2(x2, 200)));
    engine->gameObjects.push_back(tmpObj);

    tmpRenderer = (RectangleRenderer*)engine->objectPool.alloc<RectangleRenderer>();
    tmpRenderer = new (tmpRenderer) RectangleRenderer(50, 50, Color(100, 100, 200, 255));
    engine->gameObjects[1]->CreateRenderer(tmpRenderer);

    tmpCollider = (RectangleCollider*)engine->objectPool.alloc<RectangleCollider>();
    tmpCollider = new (tmpCollider) RectangleCollider();
    engine->gameObjects[1]->CreateCollider(tmpCollider);

    tmpColor = (CollisionColorChanger*)engine->objectPool.alloc<CollisionColorChanger>();
    tmpColor = new (tmpColor) CollisionColorChanger();
    engine->gameObjects[1]->CreateColliderColorChanger(tmpColor);
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

    if (!engine->world.AddCollisionColorChanger(0, CollisionColorChanger()))
    {
        engine->system->ErrorMessage(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
        engine->system->LogToErrorFile(gpr460::MAX_COLLISION_COLOR_CHANGERS_ERROR);
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