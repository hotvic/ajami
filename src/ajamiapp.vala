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
    /* Helpers */
    public MainWindow get_main_window() {
        return Ajami.get_app().get_main_window();
    }

    public class Ajami : Gtk.Application {
        private MainWindow window = null;


        public Ajami() {
            Object(application_id: "org.ajami.ajami", flags: 0);

            Environment.set_application_name("Ajami");

            add_actions();
        }

        public static Ajami get_app() {
            return GLib.Application.get_default() as Ajami;
        }

        public override void activate() {
            window = new MainWindow(this);

            window.show_all();
        }

        public void add_actions() {
            var quit = new SimpleAction("quit", null);
            var preferences = new SimpleAction("preferences", null);

            quit.activate.connect(() => {
                this.quit();
            });

            this.add_action(quit);
            this.add_action(preferences);
        }

        public MainWindow? get_main_window() {
            if (window != null && window is MainWindow)
                return window;

            return null;
        }
    }
}
