//This file initializes the Oxygine engine.
#include "core/oxygine.h"
#include "Stage.h"

#include "Game.h"
#include "res.h"

using namespace oxygine;

void StartGameLoop()
{
	spGame game = new Game;
	flow::show(game);
	game->StartGameLoop();
}

void tictactoe_destroy()
{
	res::free();
}

void tictactoe_init()
{
	//load resources
	res::load();

	//set background
	spSprite bg = new Sprite;
	bg->setResAnim(res::ui.getResAnim("bg"));

	float scaleFactor = getStage()->getWidth() / (float)bg->getWidth();
	bg->setScale(scaleFactor);
	bg->attachTo(getStage());

	//initialize oxygine_flow
	flow::init();

}

// Application entry point
void run()
{
    ObjectBase::__startTracingLeaks();

    core::init_desc desc;
    desc.title = "TicTacToe";

#if OXYGINE_SDL || OXYGINE_EMSCRIPTEN
    // The initial window size 
    desc.w = 960;
    desc.h = 640;
#endif

    core::init(&desc);

    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    // Initializes our example game. See example.cpp
    tictactoe_init();

    // This is the main game loop.

	StartGameLoop();


    /*
     If we get here, the user has requested the Application to terminate.
     We dump and log all our created objects that have not been freed yet
    */
    ObjectBase::dumpCreatedObjects();

    tictactoe_destroy();

    // Releases all internal components and the stage
    core::release();

    // The dump list should be empty by now,
    // we want to make sure that there aren't any memory leaks, so we call it again.
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
    //end
}



#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
    int main(int argc, char* argv[])
    {

        run();

        return 0;
    }
};
#endif