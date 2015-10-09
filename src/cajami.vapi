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


namespace CAjami {
    [Compact]
    [CCode (cheader_filename = "hdeq.h")]
    public class HDEQ {
        [CCode (cname = "crossover_init")]
        public static void crossover_init();

        [CCode (cname = "hdeq_low2mid_set")]
        public static void low2mid_set(Gtk.Range range);

        [CCode (cname = "hdeq_mid2high_set")]
        public static void mid2high_set(Gtk.Range range);
    }

    [Compact]
    [CCode (cheader_filename = "intrim.h")]
    public class INTrim {
        [CCode (cname = "update_meters")]
        public static bool update_meters();
    }

    [CCode (cprefix = "s_", cheader_filename = "state.h")]
    namespace State {
        [CCode (cname = "s_callback_func", has_target = false, has_type_id = false)]
        public delegate void Callback(int id, float val);

        [CCode (cname = "S_IN_GAIN")]
        public const int IN_GAIN;
        [CCode (cname = "S_LIM_INPUT")]
        public const int LIM_INPUT;
        [CCode (cname = "S_LIM_TIME")]
        public const int LIM_TIME;
        [CCode (cname = "S_LIM_LIMIT")]
        public const int LIM_LIMIT;
        public const int S_BOOST;
        public const int S_LIM_LOGSCALE;
        public const int S_NOTCH_GAIN;
        public const int S_NOTCH_FREQ;
        public const int S_NOTCH_Q;
        public const int S_NOTCH_FLAG;
        public const int S_SIZE;

        [CCode (cname = "s_init")]
        public void init();

        [CCode (cname = "s_clear_history")]
        public void clear_history();

        [CCode (cname = "s_load_session")]
        public void load_session(string? fname);

        [CCode (cname = "s_set_adjustment")]
        public void set_adjustment(int id, Gtk.Adjustment adj);

        [CCode (cname = "s_set_callback")]
        public void set_callback(int id, void* cb);

        [CCode (cname = "s_set_value_ui")]
        public void set_value_ui(int id, float val);

        [CCode (cname = "s_undo")]
        public void undo();

        [CCode (cname = "s_redo")]
        public void redo();
    }

    [Compact]
    [CCode (cprefix = "io_", cheader_filename = "io.h")]
    public class IO {
        [CCode (cname = "io_init")]
        public static void init();
        [CCode (cname = "io_cleanup")]
        public static void cleanup();
    }
}
