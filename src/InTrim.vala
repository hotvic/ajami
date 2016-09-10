namespace Ajami
{
    public class InTrim
    {
        private double _inmeter_warn_level;
        private double _rmsmeter_warn_level;
        private double _outmeter_warn_level;

        private static double[] _in_gain;
        private static double   _out_gain;
        private static double   _in_trim_gain;
        private static double[] _in_pan_gain;

        public static bool out_meter_peak_pref;
        public static bool rms_meter_peak_pref;

        public double inmeter_warn_level {
            get { return _inmeter_warn_level; }
            set {
                _inmeter_warn_level = value;
                main_window.set_inmeter_warn_point(value);
            }
        }

        public double rmsmeter_warn_level {
            get { return _rmsmeter_warn_level; }
            set {
                _rmsmeter_warn_level = value;
                main_window.set_rmsmeter_warn_point(value);
            }
        }

        public double outmeter_warn_level {
            get { return _outmeter_warn_level; }
            set {
                _outmeter_warn_level = value;
                main_window.set_outmeter_warn_point(value);
            }
        }

        public static double get_in_gain(int chan)
        {
            return _in_gain[chan];
        }

        public static void set_in_gain(int chan, double val)
        {
            _in_gain[chan] = val;
        }

        public static double get_out_gain()
        {
            return _out_gain;
        }

        static construct {
            _in_gain = new double[2];
            _in_pan_gain = new double[2];
            _out_gain = 1.0;
            _in_trim_gain = 1.0;

            for (int i = 0; i < 2; i++)
            {
                _in_gain[i] = 1.0;
                _in_pan_gain[i] = 1.0;
            }
        }

        public InTrim()
        {
            main_window.set_inmeter_value(MeterSide.L, -60.0);
            main_window.set_inmeter_value(MeterSide.R, -60.0);
            main_window.set_outmeter_value(MeterSide.L, -60.0);
            main_window.set_outmeter_value(MeterSide.R, -60.0);
            main_window.set_rmsmeter_value(MeterSide.L, -60.0);
            main_window.set_rmsmeter_value(MeterSide.R, -60.0);

            /* TODO: conditionally? set presets window meter values
            gtk_adjustment_set_value(in_meter_adj[2], -60.0);
            gtk_adjustment_set_value(in_meter_adj[3], -60.0); */

            /* TODO: conditionally? set presets window meter values
            gtk_adjustment_set_value(out_meter_adj[2], -60.0);
            gtk_adjustment_set_value(out_meter_adj[3], -60.0); */

            _state.set_callback(StateFlags.IN_GAIN, in_value_changed);
            _state.set_adjustment(StateFlags.IN_GAIN, main_window.in_gain_adj);
            // _state.set_adjustment(StateFlags.IN_GAIN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_in_trim_scale"))));

            _state.set_callback(StateFlags.OUT_GAIN, out_value_changed);
            _state.set_adjustment(StateFlags.OUT_GAIN, main_window.out_gain_adj);
            // _state_set.adjustment(AJAMI_STATE_FLAGS_OUT_GAIN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_out_trim_scale"))));

            _state.set_callback(StateFlags.IN_PAN, balance_value_changed);
            _state.set_adjustment(StateFlags.IN_PAN, main_window.in_balance_adj);
            // _state_set.adjustment(AJAMI_STATE_FLAGS_IN_PAN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_pan_scale"))));
        }

        public void update_in_meter_value(double[] amps)
        {
            main_window.set_inmeter_value(MeterSide.L, lin2db(amps[MeterSide.L]));
            main_window.set_inmeter_value(MeterSide.R, lin2db(amps[MeterSide.R]));

            /* TODO: conditionally? lookup presets window
            gtk_adjustment_set_value(in_meter_adj[2], lin2db(amps[0]));
            gtk_adjustment_set_value(in_meter_adj[3], lin2db(amps[1])); */

            amps[MeterSide.L] = 0.0f;
            amps[MeterSide.R] = 0.0f;
        }

        public void update_out_meter_value(double[] amps)
        {
            double lamp[2];

            lamp[MeterSide.L] = lin2db(amps[MeterSide.L]);
            lamp[MeterSide.R] = lin2db(amps[MeterSide.R]);

            main_window.set_outmeter_value(MeterSide.L, lin2db(amps[MeterSide.L]));
            main_window.set_outmeter_value(MeterSide.R, lin2db(amps[MeterSide.R]));

            /* TODO: conditionally? lookup presets window
            gtk_adjustment_set_value(out_meter_adj[2], lin2db(amps[0]));
            gtk_adjustment_set_value(out_meter_adj[3], lin2db(amps[1])); */

            if (out_meter_peak_pref)
            {
                lamp[MeterSide.L] = main_window.get_outmeter_peak(MeterSide.L);
                lamp[MeterSide.R] = main_window.get_outmeter_peak(MeterSide.R);
            }
            else
            {
                if (lamp[MeterSide.L] < -60.0) lamp[MeterSide.L] = -60.0;
                if (lamp[MeterSide.R] < -60.0) lamp[MeterSide.R] = -60.0;
            }

            main_window.set_out_text(MeterSide.L, "%.1f".printf(lamp[MeterSide.L]));
            main_window.set_out_text(MeterSide.R, "%.1f".printf(lamp[MeterSide.R]));

            amps[0] = 0.0f;
            amps[1] = 0.0f;
        }

        public void update_rms_meter_value(double[] amps)
        {
            double lamp[2];

            lamp[MeterSide.L] = lin2db(amps[MeterSide.L]);
            lamp[MeterSide.R] = lin2db(amps[MeterSide.R]);

            main_window.set_rmsmeter_value(MeterSide.L, lin2db(amps[MeterSide.L]));
            main_window.set_rmsmeter_value(MeterSide.R, lin2db(amps[MeterSide.R]));

            if (rms_meter_peak_pref)
            {
                lamp[0] = main_window.get_rmsmeter_peak(MeterSide.L);
                lamp[1] = main_window.get_rmsmeter_peak(MeterSide.R);
            }
            else
            {
                if (lamp[MeterSide.L] < -60.0) lamp[MeterSide.L] = -60.0;
                if (lamp[MeterSide.R] < -60.0) lamp[MeterSide.R] = -60.0;
            }

            main_window.set_rmsout_text(MeterSide.L, "%.1f".printf(lamp[MeterSide.L]));
            main_window.set_rmsout_text(MeterSide.R, "%.1f".printf(lamp[MeterSide.R]));

            amps[MeterSide.L] = 0.0f;
            amps[MeterSide.R] = 0.0f;
        }

        public bool update_meters()
        {
            //int glob, eq, comp[3], limiter;

            update_in_meter_value(_limiter.in_peak);
            update_out_meter_value(_limiter.out_peak);

            /* Only update these meters if main window is displayed */
            if (Args.presets_gui == false && Args.daemon_mode == false)
            {
                update_rms_meter_value(_limiter.rms_peak);
                _limiter.meters_update();
                CAjami.Compressor.meters_update();
                //CAjami.Spectrum.timeout_check();
                _state.crossfade_ui();
            }
            /* TODO: wtf is this ?
            status_set_time(main_window); */


            /*  Only update the remaining status once a second.  */

            /* TODO: wtf is this ?
            if (!(count = (count + 1) % 10)) {
                status_update (main_window);
            } */


            /*  Only blink the bypass buttons twice a second when bypass is on.  */

            /* TODO: implement bypass blink
            if (!(count % 5)) {
                process_get_bypass_states (&eq, comp, &limiter, &global);

                if (global) callbacks_blink_bypass_button (GLOBAL_BYPASS, 0);
                if (eq) callbacks_blink_bypass_button (EQ_BYPASS, 0);
                if (comp[0] == BYPASS) callbacks_blink_bypass_button (LOW_COMP_BYPASS, 0);
                if (comp[1] == BYPASS) callbacks_blink_bypass_button (MID_COMP_BYPASS, 0);
                if (comp[2] == BYPASS) callbacks_blink_bypass_button (HIGH_COMP_BYPASS, 0);
                if (limiter) callbacks_blink_bypass_button (LIMITER_BYPASS, 0);
            } */

            return true;
        }

        public static void in_value_changed(int id, double val)
        {
            _in_trim_gain = db2lin(val);
            _in_gain[0] = _in_trim_gain * _in_pan_gain[0];
            _in_gain[1] = _in_trim_gain * _in_pan_gain[1];
        }

        public static void balance_value_changed(int id, double val)
        {
            _in_pan_gain[0] = db2lin(val * -0.5f);
            _in_pan_gain[1] = db2lin(val * 0.5f);
            _in_gain[0] = _in_trim_gain * _in_pan_gain[0];
            _in_gain[1] = _in_trim_gain * _in_pan_gain[1];
        }

        public static void out_value_changed(int id, double val)
        {
            _out_gain = db2lin(val);
        }
    }
}