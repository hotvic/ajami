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


namespace Ajami {
    public enum SceneState {
        NONE,
        ON,
        OFF,
        WARNING,
        UNUSED,
        LAST
    }

    public struct Scene {
        public int        id;
        public string     name;
        public SceneState state;
        public EventBox   ev;
        public Image      img;
    }

    [GtkTemplate (ui="/org/ajami/ajami/gtk/scenes.ui")]
    public class Scenes : Gtk.Box {
        private Scene scenes[20];

        public int current_scene {
            get; set; default = 0;
        }

        construct {
            for (int i = 0; i < 20; i++) {
                scenes[i].id    = i;
                scenes[i].name  = "Scene %d".printf(i + 1);
                scenes[i].state = SceneState.UNUSED;
                scenes[i].img   = new Gtk.Image.from_resource("/org/ajami/ajami/pixmaps/LED_red.xpm");
                scenes[i].ev    = new Gtk.EventBox();

                scenes[i].ev.add(scenes[i].img);

                this.pack_start(scenes[i].ev, true, true, 0);
            }
        }

        public void scene_set_tooltip(int scene, string text) {
            this.scenes[scene].ev.set_tooltip_markup(text);
        }

        public void set_scene_state() {

        }

        public void scene_set_active(int scene) {
            scenes[scene].img.resource = "/org/ajami/ajami/pixmaps/LED_green_on.xpm";
        }

        public void scene_set_warning(int scene) {
            scenes[scene].img.resource = "/org/ajami/ajami/pixmaps/LED_yellow.xpm";
        }

        public void scene_set_unused(int scene) {
            scenes[scene].img.resource = "/org/ajami/ajami/pixmaps/LED_red.xpm";
        }

        public void scene_set_disabled(int scene) {
            scenes[scene].img.resource = "/org/ajami/ajami/pixmaps/LED_green_off.xpm";
        }

        public string scene_get_name(int scene) {
            return "";
        }

        public void scene_set_name(int scene, string name) {

        }

        public bool scene_button_press(Gdk.EventButton event) {

            return true;
        }
    }
}
