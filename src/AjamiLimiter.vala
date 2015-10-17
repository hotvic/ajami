using Gtk;


namespace Ajami {
    [GtkTemplate (ui="/org/ajami/ajami/gtk/limiter.ui")]
    public class Limiter : Gtk.Box {
        [GtkChild]
        private Frame frame;

        [GtkChild]
        private Scale in_scale;

        [GtkChild]
        private Scale lim_scale;

        [GtkChild]
        private Scale rel_scale;

        [GtkChild]
        private HV.Meter inmeter;

        [GtkChild]
        private HV.Meter relmeter;

        [GtkChild]
        private HV.Meter outmeter;

        [GtkChild]
        private Label lbl_in_val;
        [GtkChild]
        private Label lbl_lim_val;
        [GtkChild]
        private Label lbl_rel_val;

        public Scale w_s_in {
            get { return in_scale; }
        }

        public Scale w_s_lim {
            get { return lim_scale; }
        }

        public Scale w_s_rel {
            get { return rel_scale; }
        }

        public Adjustment w_adj_inmeter {
            get { return inmeter.adjustment; }
        }

        public Adjustment w_adj_relmeter {
            get { return relmeter.adjustment; }
        }

        public Adjustment w_adj_outmeter {
            get { return outmeter.adjustment; }
        }

        public void set_label(string text) {
            frame.label = text;
            (frame.label_widget as Label).use_markup = true;
        }

        public void set_lim_label(string label) {
            lbl_lim_val.label = label;
        }

        public void set_rel_label(string label) {
            lbl_rel_val.label = label;
        }

        public void reset_inmeter_peak() {
            inmeter.reset_peak();
        }

        public void reset_relmeter_peak() {
            relmeter.reset_peak();
        }

        public void reset_outmeter_peak() {
            outmeter.reset_peak();
        }

        [GtkCallback]
        public void in_changed() {
            CAjami.State.set_value_ui(CAjami.State.LIM_INPUT, (float) in_scale.adjustment.value);

            /* Value label update */
            in_scale.value_changed.connect(() => {
                lbl_in_val.label = "%.1f dB".printf(in_scale.adjustment.value);
            });
        }

        [GtkCallback]
        public void lim_changed() {
            CAjami.State.set_value_ui(CAjami.State.LIM_LIMIT, (float) lim_scale.adjustment.value);
        }

        [GtkCallback]
        public void rel_changed() {
            CAjami.State.set_value_ui(CAjami.State.LIM_TIME, (float) rel_scale.adjustment.value);
        }
    }
}
