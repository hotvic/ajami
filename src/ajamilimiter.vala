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
        private HV.Meter rel_outmeter;

        [GtkChild]
        private HV.Meter outmeter;


        public Limiter() {
            Object();
        }

        public void set_label(string text) {
            frame.label = text;
            (frame.label_widget as Label).use_markup = true;
        }

        public void reset_inmeter_peak() {
            inmeter.reset_peak();
        }

        public void reset_rel_outmeter_peak() {
            rel_outmeter.reset_peak();
        }

        public void reset_outmeter_peak() {
            outmeter.reset_peak();
        }
    }
}
