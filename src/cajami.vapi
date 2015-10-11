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
        [CCode (cname = "bind_hdeq")]
        public static void bind();

        [CCode (cname = "crossover_init")]
        public static void crossover_init();

        [CCode (cname = "hdeq_low2mid_set")]
        public static void low2mid_set(Gtk.Range range);

        [CCode (cname = "hdeq_mid2high_set")]
        public static void mid2high_set(Gtk.Range range);
    }

    [Compact]
    [CCode (cheader_filename = "geq.h")]
    public class GraphicEQ {
        [CCode (cname = "bind_geq")]
        public static void bind();
    }

    [Compact]
    [CCode (cheader_filename = "intrim.h")]
    public class INTrim {
        [CCode (cname = "bind_intrim")]
        public static void bind();

        [CCode (cname = "update_meters")]
        public static bool update_meters();
    }

    [Compact]
    [CCode (cheader_filename = "limiter-ui.h")]
    public class Limiter {
        [CCode (cname = "bind_limiter")]
        public static void bind();
    }

    [Compact]
    [CCode (cheader_filename = "compressor-ui.h")]
    public class Compressor {
        [CCode (cname = "bind_compressors")]
        public static void bind();
    }

    [Compact]
    [CCode (cheader_filename = "stereo.h")]
    public class Stereo {
        [CCode (cname = "bind_stereo")]
        public static void bind();
    }

    [Compact]
    [CCode (cheader_filename = "scenes.h")]
    public class Scenes {
        [CCode (cname = "bind_scenes")]
        public static void bind();
    }

    [CCode (cname = "s_callback_func", has_target = false, has_type_id = false)]
    public delegate void StateCallback(int id, float val);

    [Compact]
    [CCode (cprefix = "s_", cheader_filename = "state.h")]
    public class State {
        [CCode (cname = "S_IN_GAIN")]
        public static const int IN_GAIN;
        [CCode (cname = "S_LIM_INPUT")]
        public static const int LIM_INPUT;
        [CCode (cname = "S_LIM_TIME")]
        public static const int LIM_TIME;
        [CCode (cname = "S_LIM_LIMIT")]
        public static const int LIM_LIMIT;

        [CCode (cname = "state_init")]
        public static void init();

        [CCode (cname = "s_clear_history")]
        public static void clear_history();

        [CCode (cname = "s_load_session")]
        public static void load_session(string? fname);

        [CCode (cname = "s_set_adjustment")]
        public static void set_adjustment(int id, Gtk.Adjustment adj);

        [CCode (cname = "s_set_callback")]
        public static void set_callback(int id, void* cb);

        [CCode (cname = "s_set_value_ui")]
        public static void set_value_ui(int id, float val);

        [CCode (cname = "s_undo")]
        public static void undo();

        [CCode (cname = "s_redo")]
        public static void redo();
    }

    [Compact]
    [CCode (cprefix = "io_", cheader_filename = "io.h")]
    public class IO {
        [CCode (cname = "io_init")]
        public static void init();

        [CCode (cname = "io_init")]
        public static void activate();

        [CCode (cname = "io_cleanup")]
        public static void cleanup();
    }
}
