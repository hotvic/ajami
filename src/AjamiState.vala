/*
 * Copyright (c) 2016 Victor A. Santos <victoraur.santos@gmail.com>
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

namespace Ajami
{
    [CCode (has_target = false)]
    public delegate void StateCallbackFunc(int id, double value);

    [Compact]
    public class StateFlags
    {
        public static const int NONE         = -1;
        public static const int LOAD         = 0;
        public static const int IN_GAIN      = 1;
        public static const int OUT_GAIN     = 2;
        public static const int IN_PAN       = 3;
        public static const int LIM_INPUT    = 1051;
        public static const int LIM_TIME     = 1052;
        public static const int LIM_LIMIT    = 1053;
        public static const int BOOST        = 1054;
        public static const int LIM_LOGSCALE = 1055;
        public static const int SIZE         = 1076;
        public static int EQ_GAIN(int n)      { return 4 + n; }
        public static int XOVER_FREQ(int n)   { return 1028 + n; }
        public static int COMP_ATTACK(int n)  { return 1030 + n; }
        public static int COMP_RELEASE(int n) { return 1033 + n; }
        public static int COMP_THRESH(int n)  { return 1036 + n; }
        public static int COMP_RATIO(int n)   { return 1039 + n; }
        public static int COMP_KNEE(int n)    { return 1042 + n; }
        public static int COMP_MAKEUP(int n)  { return 1045 + n; }
        public static int STEREO_WIDTH(int n) { return 1048 + n; }
        public static int NOTCH_GAIN(int n)   { return 1056 + n; }
        public static int NOTCH_FREQ(int n)   { return 1061 + n; }
        public static int NOTCH_Q(int n)      { return 1066 + n; }
        public static int NOTCH_FLAG(int n)   { return 1071 + n; }

    }

    public class State
    {
        private StateCallbackFunc[] callbacks;
        private double[]            values;
        private double[]            targets;
        private int[]               durations;
        private Gtk.Adjustment?[]   adjustments;
        private bool                suppress_feedback;
        private bool[]              changeds;

        private Scene? last_state ;
        private int    last_changed;

        private static double crossfade_time;

        protected Json.Object root;

        public State()
        {
            callbacks   = new StateCallbackFunc[StateFlags.SIZE];
            values      = new double[StateFlags.SIZE];
            targets     = new double[StateFlags.SIZE];
            durations   = new int[StateFlags.SIZE];
            adjustments = new Gtk.Adjustment[StateFlags.SIZE];
            changeds    = new bool[StateFlags.SIZE];

            suppress_feedback = false;

            last_state   = new Scene();
            last_changed = -1;

            crossfade_time = 1.0;

            for (int i = 0; i < StateFlags.SIZE; i++)
            {
                callbacks[i]   = null;
                adjustments[i] = null;
                values[i]      = 0.0;
                targets[i]     = 0.0;
                durations[i]   = 0;
                changeds[i]    = false;
            }

            values[StateFlags.NOTCH_Q(1)] = 5.0;
            values[StateFlags.NOTCH_Q(2)] = 5.0;
            values[StateFlags.NOTCH_Q(3)] = 5.0;
        }

        public void load_preset(string preset)
        {
            var uri = "resource:///org/ajami/ajami/presets/%s.json".printf(preset);

            load_session(uri);
        }

        public void load_from_file(string fname)
        {
            string uri = "file://%s".printf(fname);
            
            load_session(uri);
        }

        public void load_session(string uri) throws Error
        {
            File file = File.new_for_uri(uri);

            if (!file.query_exists())
                throw new FileError.ACCES("State: Session file doesn't exists...");

            var file_is = file.read();
            var parser = new Json.Parser();

            parser.load_from_stream(file_is);

            root = parser.get_root().get_object();

            var active_scene = get_json_scene((int) root.get_int_member("active_scene"));

            CAjami.Process.set_spec_mode(get_settings_spectrum().get_int_member("mode"));
            Spectrum.set_frequency((int) get_settings_spectrum().get_int_member("frequency"));

            CAjami.HDEQ.set_upper_gain(get_settings_double("eq_upper_gain"));
            CAjami.HDEQ.set_lower_gain(get_settings_double("eq_lower_gain"));
            CAjami.GraphicEQ.set_range(get_settings_double("eq_lower_gain"), get_settings_double("eq_upper_gain"));

            set_crossfade_time(get_settings_crossfade_double("time"));
            _intrim.inmeter_warn_level = get_settings_intrim_int("in_warn_point");
            _intrim.outmeter_warn_level = get_settings_intrim_int("out_warn_point");

            CAjami.HDEQ.set_EQ_curve_values(0, 0.0);
        }

        public Json.Object get_json_scene(int id)
        {
            return root.get_array_member("scenes").get_object_element(id);
        }

        public double get_settings_crossfade_double(string key)
        {
            return (int) root.get_object_member("settings").get_object_member("crossfade").get_double_member(key);
        }

        protected int get_settings_intrim_int(string key)
        {
            return (int) root.get_object_member("settings").get_object_member("intrim").get_int_member(key);
        }

        protected Json.Object get_settings_spectrum()
        {
            return root.get_object_member("settings").get_object_member("spectrum");
        }

        public double get_settings_double(string key)
        {
            return root.get_object_member("settings").get_double_member(key);
        }

        public double get_eq_gain(string band)
        {
            var bands = root.get_object_member("eq_gains");

            return bands.get_double_member(band);
        }

        public double get_value(int id)
        {
            return values[id];
        }

        public void set_adjustment(int id, Gtk.Adjustment adj)
        {
            adjustments[id] = adj;
        }

        public void set_callback(int id, StateCallbackFunc func) {
            assert(id >= 0 && id < StateFlags.SIZE);

            callbacks[id] = func;
        }

        public void set_events(int id, double val)
        {
            if (callbacks[id] != null)
            {
                callbacks[id](id, val);
            }

            if (adjustments[id] != null)
            {
                adjustments[id].value = val;
            }
        }

        public void set_value(int id, double val, int duration)
        {
            this.durations[id] = duration;
            targets[id] = val;

            if (adjustments[id] is Gtk.Adjustment)
                adjustments[id].value = val;
        }

        public void set_value_ns(int id, double val)
        {
            values[id] = val;
        }

        public void set_value_block(double[] vals, int n)
        {
            for (int i = 0; i < values.length; i++)
            {
                values[n + i] = vals[i];
            }
            last_changed = n;
    
            set_events(n, values[values.length]);
        }

        public void set_value_ui(int id, double val)
        {
            values[id] = val;

            if (suppress_feedback)
            {
                return;
            }

            if (last_changed != id)
            {
                history_add("state[%d] = %f".printf(id, values[id]));
            }
            last_state.values[id] = val;

            last_changed = id;

            if (callbacks[id] != null)
            {
                callbacks[id](id, val);
            }
        }

        public void set_value_no_history(int id, double val)
        {
            suppress_feedback = true;
            values[id]  = val;
            targets[id] = val;
            set_events(id, val);
            suppress_feedback = false;
        }

        public static void set_crossfade_time(double ct)
        {
            // We're faking them out here.  0.0 isn't really allowable but most people would rather put in 0.0 instead of 0.001

            if (ct == 0.0)
                ct = 0.001;

            crossfade_time = ct;
        }

        public void history_clear() {
            stdout.printf("State: history_clear: not implemented yet!\n");
        }

        public void history_add(string description) {
            stdout.printf("State: history_add: not implemented yet!\n");
        }

        public void history_add_state(void* state) {
            stdout.printf("State: history_add_state: not implemented yet!\n");
        }

        public void history_undo() {
            stdout.printf("State: history_undo: not implemented yet!\n");
        }

        public void history_redo() {
            stdout.printf("State: history_redo: not implemented yet!\n");
        }

        public void history_set_description(int id, string description)
        {
            stdout.printf("State: history_set_description: not implemented yet!\n");
        }

        public void crossfade(int nframes)
        {
            for (int i = 0; i < StateFlags.SIZE; i++)
            {
                if (durations[i] != 0)
                {
                    durations[i] -= nframes;
            
                    if (durations[i] > nframes)
                    {
                        values[i] += ((float) nframes / (float) durations[i]) * (targets[i] - values[i]);
                    }
                    else
                    {
                        values[i]    = targets[i];
                        durations[i] = 0;
                    }
                    changeds[i] = true;
                }
            }
        }

        public void crossfade_ui()
        {
            suppress_feedback = true;

            for (int i = 0; i < StateFlags.SIZE; i++)
            {
                if (changeds[i])
                {
                    changeds[i] = false;
                    set_events(i, values[i]);
                }
            }

            suppress_feedback = false;
        }

        public void suppress_push()
        {
            suppress_feedback = true;
        }

        public void suppress_pop()
        {
            suppress_feedback = false;
        }
    }
}