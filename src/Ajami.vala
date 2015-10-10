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
using HV;


/* C functions */
extern void io_init(Ajami.Args args);


namespace Ajami {
    /* Directories */
    public string config_dir      = null;
    public string default_session = null;

    void setup_environment() {
        var app_name = Environment.get_application_name().down();

        config_dir = "%s/%s".printf(Environment.get_user_config_dir(), app_name);


        /* default session file detecting */
        var curr_data_session = "examples/default.jam";
        if (File.new_for_path(curr_data_session).query_exists()) {
            default_session = curr_data_session;
        }

        if (default_session == null) {
            var user_data_session = "%s/examples/default.jam".printf(Environment.get_user_data_dir());

            if (File.new_for_path(user_data_session).query_exists()) {
                default_session = curr_data_session;
            }
        }

        if (default_session == null) {
            foreach (string path in Environment.get_system_data_dirs()) {
                var sys_data_session = "%s/examples/default.jam".printf(path);

                if (File.new_for_path(sys_data_session).query_exists()) {
                    default_session = sys_data_session;
                    break;
                }
            }
        }
    }

    public static int main(string[] argsv) {
        Args  args = null;
        Ajami app  = null;

        args = new Args();
        app  = new Ajami();

        args.parse(argsv);

        setup_environment();

        io_init(args);

        var status = app.run();

        // CAjami.IO.cleanup();

        return status;
    }
}
