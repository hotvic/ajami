/*
 * Copyright (c) 2015 Victor A. Santos <victoraur.santos@gmail.com>
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

using Gtk;


/* Pointer to Main Window's Scenes widget */
public Ajami.Scenes w_scenes;


namespace Ajami {
    public enum SceneState {
        NONE,
        ON,
        OFF,
        WARNING,
        UNUSED,
        LAST
    }

    public class Scene {
        public int        id;
        public bool       loaded;
        public string     name;
        public SceneState state;
        public EventBox   ev;
        public Image      img;
        public double[]   values;

        public Scene()
        {
            values = new double[StateFlags.SIZE];
        }
    }

    [GtkTemplate (ui="/org/ajami/ajami/gtk/scenes.ui")]
    public class Scenes : Gtk.Box {
        private Scene scenes[20];

        public int current_scene {
            get; set; default = -1;
        }

        public int prev_scene {
            get; set; default = -1;
        }

        construct {
            for (int i = 0; i < 20; i++) {
                scenes[i] = new Scene();

                scenes[i].id     = i;
                scenes[i].loaded = false;
                scenes[i].name   = "Scene %d".printf(i + 1);
                scenes[i].state  = SceneState.UNUSED;
                scenes[i].img    = new Gtk.Image.from_resource("/org/ajami/ajami/pixmaps/LED_red.xpm");
                scenes[i].ev     = new Gtk.EventBox();

                /* initialize values */
                for (int j = 0 ; j < StateFlags.SIZE ; j++) {
                    scenes[i].values[j] = 0.0;
                }
                scenes[i].values[StateFlags.NOTCH_Q(1)]    = 5.0;
                scenes[i].values[StateFlags.NOTCH_Q(2)]    = 5.0;
                scenes[i].values[StateFlags.NOTCH_Q(3)]    = 5.0;
                scenes[i].values[StateFlags.NOTCH_FREQ(0)] = 29.0;
                scenes[i].values[StateFlags.NOTCH_FREQ(1)] = 131.0;
                scenes[i].values[StateFlags.NOTCH_FREQ(2)] = 710.0;
                scenes[i].values[StateFlags.NOTCH_FREQ(3)] = 3719.0;
                scenes[i].values[StateFlags.NOTCH_FREQ(4)] = 16903.0;

                scenes[i].ev.add(scenes[i].img);

                this.pack_start(scenes[i].ev, true, true, 0);
            }
        }

        public Scene get_scene(int id) {
            return scenes[id];
        }

        public void set_scene_tooltip(int scene, string text) {
            this.scenes[scene].ev.set_tooltip_markup(text);
        }

        public SceneState get_scene_state(int id) {
            if (id < 0 || id > 20) return SceneState.NONE;

            return scenes[id].state;
        }

        public void set_scene_state(int id, SceneState state) {
            if (id < 0 || id > 20) return;
            if (state < SceneState.NONE || state > SceneState.LAST) return;
            if (state == SceneState.ON && get_scene_state(id) == SceneState.UNUSED) return;

            scenes[id].state = state;

            switch (state) {
            case SceneState.ON:
                scenes[id].img.resource = "/org/ajami/ajami/pixmaps/LED_green_on.xpm";
                break;
            case SceneState.OFF:
                scenes[id].img.resource = "/org/ajami/ajami/pixmaps/LED_green_off.xpm";
                break;
            case SceneState.WARNING:
                scenes[id].img.resource = "/org/ajami/ajami/pixmaps/LED_yellow.xpm";
                break;
            case SceneState.UNUSED:
                scenes[id].img.resource = "/org/ajami/ajami/pixmaps/LED_red.xpm";
                break;
            }

            if (state == SceneState.ON) current_scene = id;
        }

        public string get_scene_name(int id) {
            return scenes[id].name;
        }

        public void set_scene_name(int id, string? name = null) {
            string str = name;

            if (str == null) str = "Scene %d".printf(id + 1);

            scenes[id].name = str;
        }

        public void set_scene(int id) {
            if (id != -1) {
                prev_scene    = current_scene;
                current_scene = id;
            }

            /* Grab the current state. */
            for (int i = 0 ; i < StateFlags.SIZE; i++)
                scenes[current_scene].values[i] = _state.get_value(i);

            scenes[current_scene].loaded = true;

            /* Change the selected icon to green. */
            for (int i = 0; i < 20; i++) {
                /* Matching scene. */
                if (i == current_scene) {
                    this.set_scene_state(i, SceneState.ON);
                } else {
                    if (scenes[i].loaded) {
                        this.set_scene_state(i, SceneState.OFF);
                    } else {
                        this.set_scene_state(i, SceneState.UNUSED);
                    }
                }
            }

             /* Set the tooltip to the full name. */
            this.set_scene_tooltip(current_scene, scenes[current_scene].name);
        }

        public void clear_scene(int id) {
            if (id >= 0) current_scene = id;

            this.set_scene_tooltip(id, "Scene %d, right click for menu".printf(current_scene + 1));


            /* Set the button to red. */
            this.set_scene_state(id, SceneState.UNUSED);

            scenes[id].loaded = false;


            /* Reset the scene name to the default. */
            this.set_scene_name(id);
        }

        public void unset_scene_buttons() {
            current_scene = -1;

            for (int i = 0 ; i < 20; i++) {
                this.set_scene_state(i, SceneState.UNUSED);

                scenes[i].loaded = false;

                this.set_scene_name(i);
            }
        }

        public void current_set_warning() {
            prev_scene = current_scene;

            this.set_scene_state(current_scene, SceneState.WARNING);
        }

        public void set_scene_button(int id) {
            /* Change the selected icon to green/yes. */
            for (int i = 0 ; i < 20; i++) {
                if (i == id) {
                    this.set_scene_state(i, SceneState.ON);
                    current_scene = i;
                } else {
                    if (scenes[i].loaded) {
                        this.set_scene_state(i, SceneState.OFF);
                    } else {
                        this.set_scene_state(i, SceneState.UNUSED);
                    }
                }
            }
        }

        public bool scene_button_press(Gdk.EventButton event) {
            return true;
        }
    }
}
