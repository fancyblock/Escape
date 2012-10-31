/*
 * engine.c
 *
 *  Created on: Oct 22, 2012
 *      Author: hejiabin
 */

#include "engine.h"
#include "allScenes.h"


ALLEGRO_DEBUG_CHANNEL("engine")


#define MAX_SCENE       20



// scene depot
static scene g_scenes[MAX_SCENE];
static int g_sceneCount;

// current inputs
static touch g_curTouch;

// current scene index
static int g_curSceneIndex;


//------------------- functions -----------------------


void InitialGame()
{
	ALLEGRO_DEBUG("[Game Initial]");

    g_sceneCount = 0;
    g_curSceneIndex = -1;
    g_curTouch._type = EVT_NOTOUCH;
    
    // add scene
    AddScene( SCENE_LOGO, SceneLogo_onEnter, SceneLogo_onFrame, SceneLogo_onRender, SceneLogo_onLeave );
    AddScene( SCENE_MAINMENU, SceneMainmenu_onEnter, SceneMainmenu_onFrame, SceneMainmenu_onRender, SceneMainmenu_onLeave );
    AddScene( SCENE_INGAME, SceneIngame_onEnter, SceneIngame_onFrame, SceneIngame_onRender, SceneIngame_onLeave );
	//TODO
    
    StartScene( SCENE_MAINMENU );
}


void InjectInputs( touch* touches )
{
	g_curTouch = touches[0];
}


void GameLogic( double interval )
{
	if( g_curSceneIndex >= 0 )
    {
        g_scenes[g_curSceneIndex].onFrame( interval );
    }
}


void GameRender( double interval )
{
	if( g_curSceneIndex >= 0 )
    {
        g_scenes[g_curSceneIndex].onRender( interval );
    }
}


void AddScene( int sceneId, func_once enterFunc, func_update frameFunc, func_update renderFunc, func_once leaveFunc )
{
    if( g_sceneCount == MAX_SCENE )
    {
        return;
    }
    
    scene* newScene = &g_scenes[g_sceneCount];
    
    newScene->_id = sceneId;
    newScene->_state = SCENE_STATE_IDLE;
    
    newScene->onEnter = enterFunc;
    newScene->onFrame = frameFunc;
    newScene->onRender = renderFunc;
    newScene->onLeave = leaveFunc;
    
    g_sceneCount++;
}


void StartScene( int sceneId )
{
    // terminate prior scene
    if( g_curSceneIndex >= 0 )
    {
        g_scenes[g_curSceneIndex].onLeave();
        g_scenes[g_curSceneIndex]._state = SCENE_STATE_IDLE;
    }
    
    g_curSceneIndex = GetSceneIndexById( sceneId );
    
    // initial new scene
    if( g_curSceneIndex >= 0 )
    {
        g_scenes[g_curSceneIndex]._state = SCENE_STATE_RUNNING;
        g_scenes[g_curSceneIndex].onEnter();
    }
}


int GetSceneIndexById( int id )
{
    int i;
    
    for( i = 0; i < MAX_SCENE; i++ )
    {
        if( g_scenes[i]._id == id )
        {
            return i;
        }
    }
    
    return -1;
}


touch* GetTouchEvent()
{
    return &g_curTouch;
}







