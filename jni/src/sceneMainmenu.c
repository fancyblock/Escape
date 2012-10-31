//
//  sceneMainmenu.c
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include "allScenes.h"
#include "engine.h"

ALLEGRO_DEBUG_CHANNEL("[Scene]")


static ALLEGRO_BITMAP* _imgBg = NULL;



void SceneMainmenu_onEnter()
{
    ALLEGRO_DEBUG("[EnterScene]: SceneMainmenu");
    
    _imgBg = al_load_bitmap( "mainmenuBg.png" );
}


void SceneMainmenu_onFrame( double interval )
{
    (void)interval;
    
    touch* curTouch = GetTouchEvent();
    
    if( curTouch->_type == EVT_UNTOUCH )
    {
        StartScene( SCENE_INGAME );
    }
}


void SceneMainmenu_onRender( double interval )
{
    (void)interval;
    
    al_draw_bitmap_region( _imgBg, 0, 0, 480, 320, 0, 0, 0 );
}


void SceneMainmenu_onLeave()
{
    al_destroy_bitmap( _imgBg );
    
    ALLEGRO_DEBUG("[LeaveScene]: SceneMainmenu");
}


