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

        [CCode (cname = "hdeq_set_upper_gain")]
        public static void set_upper_gain(double gain);

        [CCode (cname = "hdeq_set_lower_gain")]
        public static void set_lower_gain(double gain);

        [CCode (cname = "crossover_init")]
        public static void crossover_init();

        [CCode (cname = "hdeq_low2mid_set")]
        public static void low2mid_set(Gtk.Range range);

        [CCode (cname = "hdeq_mid2high_set")]
        public static void mid2high_set(Gtk.Range range);

        [CCode (cname = "set_EQ_curve_values")]
        public static void set_EQ_curve_values(int id, double val);
    }

    [Compact]
    [CCode (cheader_filename = "geq.h")]
    public class GraphicEQ {
        [CCode (cname = "bind_geq")]
        public static void bind();

        [CCode (cname = "geq_set_range")]
        public static void set_range(double min, double max);
    }

    [Compact]
    [CCode (cheader_filename = "limiter-ui.h")]
    public class Limiter {
        [CCode (cname = "bind_limiter")]
        public static void bind();
    }

    [Compact]
    [CCode (cprefix = "compressor_", cheader_filename = "compressor-ui.h")]
    public class Compressor {
        [CCode (cname = "bind_compressors")]
        public static void bind();

        public static void meters_update();
    }

    [Compact]
    [CCode (cheader_filename = "scenes.h")]
    public class Scenes {
        [CCode (cname = "bind_scenes")]
        public static void bind();
    }

    [Compact]
    [CCode (cprefix = "io_", cheader_filename = "io.h")]
    public class IO {
        public static void init();

        public static void activate();

        public static void cleanup();
    }

    [Compact]
    [CCode (cprefix = "process_", cheader_filename = "process.h")]
    public class Process {
        public static void set_spec_mode(int64 mode);

        public static void set_ws_boost(double val);

        public static void set_limiter_logscale(double val);

        public static void set_stereo_balance(int chan, double val);
        
        public static void set_stereo_width(int chan, double val);
    }
}
