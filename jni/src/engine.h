/*
 * engine.h
 *
 *  Created on: Oct 22, 2012
 *      Author: hejiabin
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_android.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>


#define SCENE_STATE_IDLE        0
#define SCENE_STATE_RUNNING     1

#define EVT_NOTOUCH   0
#define EVT_TOUCH     1
#define EVT_UNTOUCH   2
#define EVT_MOVE      3



typedef void (*func_once)();
typedef void (*func_update)( double elapsed );


// touch struct
typedef struct
{
    int     _type;
    double  _x;
    double  _y;
    
}touch;


// scene struct
typedef struct
{
	int _id;
	int _state;

	func_once onEnter;
	func_update onFrame;
	func_update onRender;
	func_once onLeave;
    
}scene;


// initial the game , add scene & preload sound & etc
void InitialGame();

// inject touch events
void InjectInputs( touch* touches );

// update game logic
void GameLogic( double interval );

// update render
void GameRender( double interval );

// add scene to the engine
void AddScene( int sceneId, func_once enterFunc, func_update frameFunc, func_update renderFunc, func_once leaveFunc );

// start a scene & stop prior scene
void StartScene( int sceneId );

// return the scene index via scene ID
int GetSceneIndexById( int id );

// return the current touch event ( for now only support one touch in one time )
touch* GetTouchEvent();


#endif /* ENGINE_H_ */
