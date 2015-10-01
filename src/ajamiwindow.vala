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
using HV;


/* Pointer to Main Window */
public Ajami.MainWindow main_window;


namespace Ajami {
    /* Widgets helpers */
    public Scenes get_scenes_widget() {
        return Ajami.get_app().get_main_window().get_scenes_widget();
    }

    public Limiter get_limiter_widget() {
        return Ajami.get_app().get_main_window().get_limiter_widget();
    }

    public Spectrum get_spectrum_widget() {
        return Ajami.get_app().get_main_window().get_spectrum_widget();
    }

    public Compressor? get_comp_widget(CompID id) {
        return Ajami.get_app().get_main_window().get_comp_widget(id);
    }

    public enum MeterSide {
        METER_L,
        METER_R
    }

    [GtkTemplate (ui="/org/ajami/ajami/gtk/appwindow.ui")]
    public class MainWindow : ApplicationWindow {
        [GtkChild]
        private Scenes scenes;

        [GtkChild]
        private Limiter limiter;

        [GtkChild]
        private Spectrum spectrum;

        [GtkChild]
        private Compressor compressor_low;

        [GtkChild]
        private Compressor compressor_mid;

        [GtkChild]
        private Compressor compressor_high;

        [GtkChild]
        private Scale in_amp_scale;

        [GtkChild]
        private Scale in_stereo_scale;

        [GtkChild]
        private Meter inmeter_l;

        [GtkChild]
        private Meter inmeter_r;

        [GtkChild]
        private Meter outmeter_l;

        [GtkChild]
        private Meter outmeter_r;

        [GtkChild]
        private Meter rmsmeter_l;

        [GtkChild]
        private Meter rmsmeter_r;

        [GtkChild]
        private Scale cross_low_scale;

        [GtkChild]
        private Scale cross_high_scale;


        public MainWindow(Gtk.Application app) {
            Object(application: app);

            add_actions();
        }

        public Scenes get_scenes_widget() {
            return scenes;
        }

        public Limiter get_limiter_widget() {
            return limiter;
        }

        public Spectrum get_spectrum_widget() {
            return spectrum;
        }

        public Compressor get_comp_widget(CompID id) {
            switch (id) {
            case CompID.COMP_LOW:
                return compressor_low;
            case CompID.COMP_MID:
                return compressor_mid;
            case CompID.COMP_HIGH:
                return compressor_high;
            }

            return null;
        }

        public Gtk.Widget get_widget(Type type, string name) {
            return this.get_template_child(type, name) as Gtk.Widget;
        }

        public void add_actions() {
            var new_preset = new SimpleAction("new-preset", null);
            var open_preset = new SimpleAction("open-preset", null);
            var save_preset = new SimpleAction("save-preset", null);
            var save_as_preset = new SimpleAction("save-as-preset", null);
            var undo = new SimpleAction("undo", null);
            var redo = new SimpleAction("redo", null);

            this.add_action(new_preset);
            this.add_action(open_preset);
            this.add_action(save_preset);
            this.add_action(save_as_preset);
            this.add_action(undo);
            this.add_action(redo);
        }

        /* INTRIM */
        public void set_inmeter_value(MeterSide side, double value) {
            if (side == MeterSide.METER_L) {
                this.inmeter_l.adjustment.set_value(value);
            } else {
                this.inmeter_r.adjustment.set_value(value);
            }
        }

        public void set_outmeter_value(MeterSide side, double value) {
            if (side == MeterSide.METER_L) {
                this.outmeter_l.adjustment.set_value(value);
            } else {
                this.outmeter_r.adjustment.set_value(value);
            }
        }

        public void set_rmsmeter_value(MeterSide side, double value) {
            if (side == MeterSide.METER_L) {
                this.rmsmeter_l.adjustment.set_value(value);
            } else {
                this.rmsmeter_r.adjustment.set_value(value);
            }
        }

        public float get_inmeter_peak(MeterSide side) {
            return 0f;
        }

        public float get_outmeter_peak(MeterSide side) {
            return 0f;
        }

        public float get_rmsmeter_peak(MeterSide side) {
            return 0f;
        }

        public void reset_inmeter_peak() {

        }

        public void reset_outmeter_peak() {

        }

        public void reset_rmsmeter_peak() {

        }

        public void set_inmeter_warn_point(float point) {

        }

        public void set_outmeter_warn_point(float point) {

        }

        public void set_rmsmeter_warn_point(float point) {

        }

        /* Crossover */
        public void set_cross_low_label(string label) {

        }

        public void set_cross_high_label(string label) {

        }
    }
}
