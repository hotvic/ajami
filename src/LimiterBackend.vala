namespace Ajami
{
    public struct LimSettings {
        float ingain;
        float limit;
        float release;
        float attenuation;
        float latency;
        float logscale;
        void* handle;
    }

    public enum LimiterFlags
    {
        INGAIN,
        LIMIT,
        RELEASE,
        ATTENUATION,
        IN_1,
        IN_2,
        OUT_1,
        OUT_2,
        LATENCY,
        LOGSCALE
    }

    public enum LimiterPeakFlags
    {
        IN,
        OUT
    }

    public class LimiterBackend
    {
        public static LimSettings limiter[2];
        public static int limiter_plugin;
        public double[] lim_peak;
        public double[] in_peak;
        public double[] rms_peak;
        public double[] out_peak;

        public LimiterBackend()
        {
            limiter_plugin = 0;

            lim_peak = new double[2];
            in_peak  = new double[2];
            rms_peak = new double[2];
            out_peak = new double[2];

            _state.set_callback(StateFlags.LIM_INPUT, li_changed);
            _state.set_callback(StateFlags.LIM_TIME, lh_changed);
            _state.set_callback(StateFlags.LIM_LIMIT, ll_changed);

            _state.set_adjustment(StateFlags.LIM_TIME, get_limiter_widget().adj_rel);
            _state.set_adjustment(StateFlags.LIM_LIMIT, get_limiter_widget().adj_lim);

            _state.set_value(StateFlags.LIM_INPUT, 0.0f, 0);
            _state.set_value(StateFlags.LIM_TIME, 0.05f, 0);
            _state.set_value(StateFlags.LIM_LIMIT, 0.0f, 0);
        }

        public void meters_update()
        {
            double peak_in = lin2db(lim_peak[LimiterPeakFlags.IN]);
            double peak_out = lin2db(lim_peak[LimiterPeakFlags.OUT]);
            double atten = -limiter[limiter_plugin].attenuation;
            lim_peak[LimiterPeakFlags.IN] = 0.0f;
            lim_peak[LimiterPeakFlags.OUT] = 0.0f;

            get_limiter_widget().adj_inmeter.value = peak_in;
            get_limiter_widget().adj_outmeter.value = atten;
            get_limiter_widget().adj_relmeter.value = peak_out;
        }


        public static void li_changed(int id, double val)
        {
            limiter[limiter_plugin].ingain = (float) val;
        }

        public static void lh_changed(int id, double val)
        {
            string text;

            float pval = Math.powf(10.0f, (float) val);
            if (pval >= 100.0f)
            {
                text = "%.3g s".printf(pval * 0.001f);
            }
            else
            {
                text = "%.4g ms".printf(pval);
            }
            get_limiter_widget().set_rel_label(text);

            limiter[limiter_plugin].release = Math.powf(10.0f, (float) val - 3.0f);
        }

        public static void ll_changed(int id, double val)
        {
            limiter[limiter_plugin].limit = (float) val;

            get_limiter_widget().set_lim_label("%.1f dB".printf(val));
        }

        public static void boost_changed(int id, double val)
        {
            CAjami.Process.set_ws_boost(val);
        }

        public static void logscale_changed(int id, double val)
        {
            CAjami.Process.set_limiter_logscale(val);
        }

        public static void limiter_inmeter_reset_peak()
        {
            get_limiter_widget().reset_inmeter_peak();
        }

        public static void limiter_outmeter_reset_peak()
        {
            get_limiter_widget().reset_relmeter_peak();
            get_limiter_widget().reset_outmeter_peak();
        }

        public static void limiter_set_label(int limiter_plugin)
        {
            if (get_limiter_widget() != null)
            {
                get_limiter_widget().set_label(limiter_plugin);
            }
        }

        public static void limiter_logscale_set_state(bool state)
        {
            if (get_limiter_widget() != null)
            {
                //gtk_widget_set_sensitive (GTK_WIDGET (l_logscale_label), state);
                //gtk_widget_set_sensitive (GTK_WIDGET (l_logscale_scale), state);
            }
        }
    }
}