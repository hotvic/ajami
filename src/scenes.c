/*
 * Copyright (C) 2015 Victor A. Santos <victoraur.santos@gmail.com>
 * Copyright (C) 2003 Jan C. Depner, Steve Harris
 *
 * This file is part of Ajami.
 *
 * Ajami is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ajami is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ajami.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * A few programmer notes:
 *
 * We're trying to stay away from extern'ed global variables as much as
 * possible (I've been tainted by C++  ;-)  If you need to access a variable
 * that is used here (set or get) write a liitle one line function that
 * returns or sets it.  You can call it scenes_set_... or scenes_get_...  Yes,
 * there is some overhead associated with it but it makes tracking things
 * much easier.
 */


#include <glib.h>
#include "scenes.h"
#include "state.h"
#include "main.h"
#include "support.h"
#include "interface.h"
#include "hdeq.h"
#include "ajamiobjects.h"


static AjamiScenes*      w_scenes;
static int               menu_scene;
static gboolean          scene_loaded[NUM_SCENES];
static s_state           scene_state[NUM_SCENES];


/* Initialize all scene related structures and get the widget addresses. */
void bind_scenes ()
{
    w_scenes = ajami_main_window_get_w_scenes(main_window);

    for (int i = 0 ; i < NUM_SCENES ; i++)
    {
        scene_state[i].description = ajami_scenes_get_scene_name(w_scenes, i);

        scene_loaded[i] = FALSE;

        /*  Initialize the scene states.  */
        for (int j = 0 ; j < S_SIZE ; j++)
            scene_state[i].value[j] = 0.0;

        scene_state[i].value[S_NOTCH_Q(1)] = 5.0;
        scene_state[i].value[S_NOTCH_Q(2)] = 5.0;
        scene_state[i].value[S_NOTCH_Q(3)] = 5.0;

        scene_state[i].value[S_NOTCH_FREQ(0)] = 29.0;
        scene_state[i].value[S_NOTCH_FREQ(1)] = 131.0;
        scene_state[i].value[S_NOTCH_FREQ(2)] = 710.0;
        scene_state[i].value[S_NOTCH_FREQ(3)] = 3719.0;
        scene_state[i].value[S_NOTCH_FREQ(4)] = 16903.0;
    }
}


/* Select one of the scenes as the current scene or pop up the set/clear menu. */
/*
void select_scene (int number, int button)
{
    int             i, j;
    gboolean        warning;


    // Check for modified scene.

    warning = FALSE;
    if (number > 99)
    {
        number -= 100;
        warning = TRUE;
    }


    switch (button)
    {
    // Left button selects the scene.

    case 1:
        if (scene_loaded[number])
        {
            for (i = 0 ; i < NUM_SCENES ; i++)
            {
                /*  The matching scene.

                if (i == number)
                {
                    if (warning)
                    {
                        gtk_image_set_from_pixbuf (l_scene[i], LED_yellow);

                        current_scene = number;
                    }
                    else
                    {
                        current_scene = i;


                        // This is a fix for an earlier screwup that may or
                        // may not exist in some saved .jam files.  Basically,
                        // the default notch frequencies were set to 0.0
                        // which is way wrong and causes problems during
                        // crossfading.  This code just checks them and
                        // resets them to the default if they aren't set
                        // correctly.

                        // *********************************************

                        for (j = 0 ; j < NOTCHES ; j++)
                        {
                            if (scene_state[i].value[(S_NOTCH_FREQ(j))] == 0.0)
                            {
                                scene_state[i].value[S_NOTCH_FREQ(j)] =
                                    //                         hdeq_get_notch_default_freq (j);

                                    scene_state[i].value[S_NOTCH_Q(j)] = 5.0;
                                scene_state[i].value[S_NOTCH_GAIN(j)] = 0.0;

                                if (!j || j == NOTCHES - 1)
                                    scene_state[i].value[S_NOTCH_Q(j)] = 0.0;
                            }
                        }

                        // *********************************************


                        s_crossfade_to_state (&scene_state[i], -1.0f);

                        // set_EQ_curve_values (0, 0.0);

                        s_history_add_state (scene_state[i]);

                        gtk_image_set_from_pixbuf (l_scene[i], LED_green_on);
                    }
                }


                // Non-matching scenes - set to green off or red if not loaded.

                else
                {
                    if (scene_loaded[i])
                    {
                        gtk_image_set_from_pixbuf (l_scene[i], LED_green_off);
                    }
                    else
                    {
                        gtk_image_set_from_pixbuf (l_scene[i], LED_red);
                    }
                }
            }
        }
        break;


    // Middle button is ignored.

    case 2:
        break;


    // Right button pops up the set/clear menu.

    case 3:
        menu_scene = number % 100;
        gtk_menu_popup (scene_menu, NULL, NULL, NULL, NULL, button,
                        gtk_get_current_event_time());
        break;
    }
}*/


/* Returns the current active scene number or -1 if no scene is active. */
int get_current_scene ()
{
    return ajami_scenes_get_current_scene(w_scenes);
}


/* Returns the requested scene state or NULL if that scene is not loaded. */
s_state *get_scene (int number)
{
    if (!scene_loaded[number]) return NULL;

    return &scene_state[number];
}

void scene_init()
{
    memset(scene_state, 0, sizeof(s_state) * NUM_SCENES);
}


/* Set the scene state from the current settings. Get the scene name from
 * the scene widget. If scene_num is -1 use the last pressed scene button number (menu_scene).
 */
void set_scene (int scene_num)
{
    /* Only save the scene settings if we're going from the current settings.
     * That is, scene_num = -1.  Otherwise we may be in the middle of
     * crossfading to a new state.
     */

    if (scene_num >= 0) {
        menu_scene = scene_num;
        ajami_scenes_set_prev_scene(w_scenes, scene_num);
    }


    /* Grab the current state. */
    for (int i = 0 ; i < S_SIZE ; i++)
        scene_state[menu_scene].value[i] = s_get_value(i);

    scene_state[menu_scene].description = ajami_scenes_get_scene_name(w_scenes, scene_num);


    /* Set the scene loaded flag. */
    scene_loaded[menu_scene] = TRUE;


    /* Change the selected icon to green. */
    for (int i = 0 ; i < NUM_SCENES ; i++)
    {
        /* Matching scene. */
        if (i == menu_scene)
        {
            ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_ON);
            ajami_scenes_set_current_scene(w_scenes, i);
        }
        else
        {
            if (scene_loaded[i])
            {
                ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_OFF);
            }
            else
            {
                ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_UNUSED);
            }
        }
    }

    /* Set the tooltip to the full name. */
    ajami_scenes_set_scene_tooltip(w_scenes, menu_scene, scene_state[menu_scene].description);
}


/* Gets the scene name for scene "number". */
const char *get_scene_name (int number)
{
    if (!scene_loaded[number]) return NULL;

    return ajami_scenes_get_scene_name(w_scenes, number);
}


/* Set the scene name. If the scene_name passed in is null get the name
 * from the scene widget. This is called from callbacks.c
 * on a change to the scene widget. */
void set_scene_name (int number, const char *scene_name)
{
    /* If we are trying to modify the name without anything loaded, bypass this. */
    if (menu_scene < 0) return;

    if (scene_name != NULL)
        ajami_scenes_set_scene_name(w_scenes, number, scene_name);

    scene_state[number].description = g_strdup(scene_name);

    /* Set the tooltip to the name. */
    ajami_scenes_set_scene_tooltip(w_scenes, menu_scene, scene_state[menu_scene].description);
}


/* Clear the scene state. If scene_num is -1 use the last pressed scene button number. */
void clear_scene (int scene_num)
{
    if (scene_num >= 0) menu_scene = scene_num;


    ajami_scenes_set_scene_tooltip(w_scenes, menu_scene, g_strdup_printf ("Scene %d, right click for menu", menu_scene + 1));


    /* Set the button to red. */
    ajami_scenes_set_scene_state(w_scenes, menu_scene, AJAMI_SCENE_STATE_UNUSED);

    scene_loaded[menu_scene] = FALSE;


    /* Reset the scene name to the default. */
    ajami_scenes_set_scene_name(w_scenes, menu_scene, NULL);
}


/* Set all of the buttons to unselected state. This should be done whenever there is a state change. */
void unset_scene_buttons ()
{
    ajami_scenes_set_current_scene(w_scenes, -1);

    for (int i = 0 ; i < NUM_SCENES; i++)
    {
        ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_UNUSED);

        scene_loaded[i] = FALSE;

        ajami_scenes_set_scene_name(w_scenes, i, NULL);
    }
}


/* This is used in state.c to find out if we need to undo/redo. */
int get_previous_scene_num ()
{
    return ajami_scenes_get_prev_scene(w_scenes);
}


/* Set the current scene button to a warning. This is done whenever any
 * state changes are made while a scene is active. */
void set_scene_warning_button ()
{
    int cur = ajami_scenes_get_current_scene(w_scenes);

    ajami_scenes_set_prev_scene(w_scenes, cur);
    ajami_scenes_set_scene_state(w_scenes, cur, AJAMI_SCENE_STATE_WARNING);
}


/* Set the specified scene button to active. Only done on undo/redo. */
void set_scene_button (int scene)
{
    /* Change the selected icon to green/yes. */
    for (int i = 0 ; i < NUM_SCENES; i++)
    {
        if (i == scene)
        {
            ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_ON);
            ajami_scenes_set_current_scene(w_scenes, i);
        }
        else
        {
            if (scene_loaded[i])
            {
                ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_OFF);
            }
            else
            {
                ajami_scenes_set_scene_state(w_scenes, i, AJAMI_SCENE_STATE_UNUSED);
            }
        }
    }
}

/* Set a specific scene button to a warning. Only done on load. */
void set_num_scene_warning_button (int scene)
{
    ajami_scenes_set_scene_state(w_scenes, scene, AJAMI_SCENE_STATE_WARNING);
}
