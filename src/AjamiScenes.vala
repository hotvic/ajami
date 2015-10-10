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
    [GtkTemplate (ui="/org/ajami/ajami/gtk/scenes.ui")]
    public class Scenes : Gtk.Box {
        private Gtk.EventBox scenes[20];
        private int _current_scene;

        public int current_scene {
            get { return _current_scene; }
            set { _current_scene = value; }
        }

        construct {
            for (int i = 0; i < 20; i++) {
                var icn_scene = new Gtk.Image.from_resource("/org/ajami/ajami/pixmaps/LED_red.xpm");

                this.scenes[i] = new Gtk.EventBox();
                this.scenes[i].add(icn_scene);

                this.pack_start(this.scenes[i], true, true, 0);
            }
        }

        public void scene_set_tooltip(int scene, string text) {

        }

        public void scene_set_active(int scene) {
            (this.scenes[scene].get_child() as Gtk.Image).resource = "/org/ajami/ajami/pixmaps/LED_green_on.xpm";
        }

        public void scene_set_warning(int scene) {
            (this.scenes[scene].get_child() as Gtk.Image).resource = "/org/ajami/ajami/pixmaps/LED_yellow.xpm";
        }

        public void scene_set_unused(int scene) {
            (this.scenes[scene].get_child() as Gtk.Image).resource = "/org/ajami/ajami/pixmaps/LED_green_off.xpm";
        }

        public void scene_set_disabled(int scene) {
            (this.scenes[scene].get_child() as Gtk.Image).resource = "/org/ajami/ajami/pixmaps/LED_red.xpm";
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
