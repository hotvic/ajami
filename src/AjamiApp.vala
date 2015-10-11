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
extern void preferences_init();


namespace Ajami {
    public class Ajami : Gtk.Application {
        private uint _to_count = 1;

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
            main_window.destroy.connect(() => {
                this.quit();
            });
        }

        public override void startup() {
            base.startup();

            /* Workaround for now */
            Type meter = typeof(HV.Meter);
            Type geg   = typeof(GraphicEQ);

            main_window = new MainWindow(this);

            CAjami.State.init();
            preferences_init();

            CAjami.GraphicEQ.bind();
            CAjami.HDEQ.bind();
            CAjami.INTrim.bind();
            CAjami.Limiter.bind();
            CAjami.Compressor.bind();
            CAjami.Stereo.bind();
            CAjami.Scenes.bind();

            CAjami.State.clear_history();

            CAjami.IO.activate();

            CAjami.State.load_session(null);

            Timeout.add(40, CAjami.INTrim.update_meters);
        }

        public override void shutdown() {
            base.shutdown();

            CAjami.IO.cleanup();
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
