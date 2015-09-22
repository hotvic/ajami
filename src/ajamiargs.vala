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
    public class Args : Object {
        private OptionContext context;
        private OptionGroup advanced_group;

        public static bool version           = false;
        public static bool not_connect_ports = false;
        public static bool use_iir           = false;
        public static int update_frequency   = 10;
        public static int crossfade_time     = 0;
        public static int limiter            = 0;
        public static string? session_file   = null;
        public static string? server_name    = null;
        public static string? client_name    = null;

        /* Advanced Options */
        public static bool dummy          = false;
        public static bool fatal_errors   = false;
        public static bool trace_buffer   = false;
        public static bool single_thread  = false;
        public static bool presets_gui    = false;
        public static bool daemon_mode    = false;

        public Args() {
            advanced_group = new OptionGroup("advanced", "Advanced options", "Advanced options");
            context = new OptionContext("- AJAMI (Another JACK Audio Mastering Interface)");

            create_entries();

            context.set_help_enabled(true);
            context.add_group((owned) advanced_group);
        }

        public void create_entries() {
            context.add_main_entries({
                OptionEntry() {
                    long_name = "version", short_name = 'V',
                    arg_data = &version, arg = OptionArg.NONE,
                    description = "Display version number",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "not-connect", short_name = 'p',
                    arg_data = &not_connect_ports, arg = OptionArg.NONE,
                    description = "Do not automatically connect JACK output ports",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "use-iir", short_name = 'i',
                    arg_data = &use_iir, arg = OptionArg.NONE,
                    description = "Use IIR crossover instead of FFT",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "frquency", short_name = 's',
                    arg_data = &update_frequency, arg = OptionArg.INT,
                    description = "Set spectrum update frequency",
                    arg_description = "hz"
                },
                OptionEntry() {
                    long_name = "time", short_name = 'c',
                    arg_data = &crossfade_time, arg = OptionArg.DOUBLE,
                    description = "Set crossfade time",
                    arg_description = "FLOAT"
                },
                OptionEntry() {
                    long_name = "limiter", short_name = 'l',
                    arg_data = &limiter, arg = OptionArg.INT,
                    description = "Use fast-lookahead limiter(0) or foo-limiter(1)",
                    arg_description = "limiter"
                },
                OptionEntry() {
                    long_name = "file", short_name = 'f',
                    arg_data = &session_file, arg = OptionArg.STRING,
                    description = "Session file to load on startup",
                    arg_description = "FILE"
                },
                OptionEntry() {
                    long_name = "sname", short_name = 'j',
                    arg_data = &server_name, arg = OptionArg.STRING,
                    description = "JACK server name",
                    arg_description = "string"
                },
                OptionEntry() {
                    long_name = "cname", short_name = 'n',
                    arg_data = &client_name, arg = OptionArg.STRING,
                    description = "JACK client name",
                    arg_description = "string"
                }, OptionEntry()
            }, null);

            advanced_group.add_entries({
                OptionEntry() {
                    long_name = "dummy", short_name = 'd',
                    arg_data = &dummy, arg = OptionArg.NONE,
                    description = "Dummy mode (don't connect to JACK)",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "fatal", short_name = 'F',
                    arg_data = &fatal_errors, arg = OptionArg.NONE,
                    description = "Treat all errors as fatal",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "trace", short_name = 'T',
                    arg_data = &trace_buffer, arg = OptionArg.NONE,
                    description = "Print trace buffer",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "single-thread", short_name = 't',
                    arg_data = &single_thread, arg = OptionArg.NONE,
                    description = "Don't start separate DSP thread",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "presets-gui", short_name = 'g',
                    arg_data = &presets_gui, arg = OptionArg.NONE,
                    description = "Display Presets gui at startup",
                    arg_description = null
                },
                OptionEntry() {
                    long_name = "daemon", short_name = 'D',
                    arg_data = &daemon_mode, arg = OptionArg.NONE,
                    description = "Run in Daemon mode",
                    arg_description = null
                }, OptionEntry()
            });
        }

        public void parse(string[] argv) {
            try {
                context.parse(ref argv);
            } catch (OptionError e) {
                stdout.printf("%s error: %s", Environment.get_application_name(), e.message);
                usage();
            }
        }

        private void usage() {
            stdout.printf("%s", context.get_help(true, null));
            Process.exit(Posix.EXIT_FAILURE);
        }
    }
}
