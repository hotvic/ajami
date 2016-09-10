using Gtk;


namespace Ajami
{
    [GtkTemplate (ui="/org/ajami/ajami/gtk/limiter.ui")]
    public class Limiter : Gtk.Box {
        [GtkChild]
        private Adjustment _adj_in;

        [GtkChild]
        private Adjustment _adj_lim;

        [GtkChild]
        private Adjustment _adj_rel;

        [GtkChild]
        private Adjustment _adj_inmeter;

        [GtkChild]
        private Adjustment _adj_outmeter;

        [GtkChild]
        private Adjustment _adj_relmeter;

        [GtkChild]
        private Frame frame;

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

        public Adjustment adj_in { get { return _adj_in; } }
        public Adjustment adj_lim { get { return _adj_lim; } }
        public Adjustment adj_rel { get { return _adj_rel; } }
        public Adjustment adj_inmeter { get { return _adj_inmeter; } }
        public Adjustment adj_outmeter { get { return _adj_outmeter; } }
        public Adjustment adj_relmeter { get { return _adj_relmeter; } }

        public Adjustment w_adj_inmeter {
            get { return inmeter.adjustment; }
        }

        public Adjustment w_adj_relmeter {
            get { return relmeter.adjustment; }
        }

        public Adjustment w_adj_outmeter {
            get { return outmeter.adjustment; }
        }

        public void set_label(int id)
        {
            frame.label = id == 0 ? "<b>Foo-limiter (Savolainen)</b>" : "<b>Fast-lookahead-limiter (Harris)</b>";
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

        public void logscale_set_state(bool state)
        {
            stdout.printf("Limiter: logscale_set_state: not implemented yet!\n");
        }

        [GtkCallback]
        public void in_changed()
        {
            _state.set_value_ui(StateFlags.LIM_INPUT, _adj_in.value);

            // Value label update
            _adj_in.value_changed.connect(() => {
                lbl_in_val.label = "%.1f dB".printf(_adj_in.value);
            });
        }

        [GtkCallback]
        public void lim_changed()
        {
            _state.set_value_ui(StateFlags.LIM_LIMIT, _adj_lim.value);
        }

        [GtkCallback]
        public void rel_changed()
        {
            _state.set_value_ui(StateFlags.LIM_TIME, _adj_lim.value);
        }
    }
}
