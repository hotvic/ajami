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


/* C functions */
extern void state_init();
extern void preferences_init();
extern void s_clear_history();
extern void bind_geq();
extern void bind_hdeq();
extern void bind_intrim();
extern void bind_limiter();
extern void bind_compressors();
extern void bind_stereo();


namespace Ajami {
    public class Ajami : Gtk.Application {
        public Ajami() {
            Object(application_id: "org.ajami.ajami", flags: 0);

            Environment.set_application_name("Ajami");

            add_actions();
        }

        public static Ajami get_app() {
            return GLib.Application.get_default() as Ajami;
        }

        public override void activate() {
            main_window.show_all();
        }

        public override void startup() {
            base.startup();

            /* Workaround for now */
            Type meter = typeof(HV.Meter);

            main_window = new MainWindow(this);

            state_init();
            preferences_init();

            bind_geq();
            bind_hdeq();
            bind_intrim();
            bind_limiter();
            bind_compressors();
            bind_stereo();

            s_clear_history();
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
    }
}
