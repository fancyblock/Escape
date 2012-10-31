//
//  allScenes.h
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#ifndef Escape_allScenes_h
#define Escape_allScenes_h

//--------------- scene id define ---------------

#define SCENE_LOGO      1
#define SCENE_MAINMENU  2
#define SCENE_INGAME    3
#define SCENE_GAMEEND   4

//--------------- scene functoins ---------------


// logo scene
void SceneLogo_onEnter();
void SceneLogo_onFrame( double interval );
void SceneLogo_onRender( double interval );
void SceneLogo_onLeave();

// main menu scene
void SceneMainmenu_onEnter();
void SceneMainmenu_onFrame( double interval );
void SceneMainmenu_onRender( double interval );
void SceneMainmenu_onLeave();

// game scene
void SceneIngame_onEnter();
void SceneIngame_onFrame( double interval );
void SceneIngame_onRender( double interval );
void SceneIngame_onLeave();

// game end scene
//TODO 


#endif
