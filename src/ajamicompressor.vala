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


/* C functions */
extern void s_set_callback(int state_id, void *cb);
extern void s_set_adjustment(int state_id, Adjustment adj);
extern void at_changed(int id, float value);
extern void re_changed(int id, float value);
extern void th_changed(int id, float value);
extern void ra_changed(int id, float value);
extern void kn_changed(int id, float value);
extern void ma_changed(int id, float value);
extern void adj_cb(Adjustment adj, void *data);


namespace Ajami {
    public enum CompID {
        COMP_LOW,
        COMP_MID,
        COMP_HIGH
    }

    [GtkTemplate (ui="/org/ajami/ajami/gtk/compressor.ui")]
    public class Compressor : Gtk.Frame {
        protected int _comp_id;

        public int comp_id {
            get { return _comp_id; }
            set { _comp_id = value; }
        }

        [GtkChild]
        private Adjustment adj_at;

        [GtkChild]
        private Adjustment adj_re;

        [GtkChild]
        private Adjustment adj_th;

        [GtkChild]
        private Adjustment adj_ra;

        [GtkChild]
        private Adjustment adj_kn;

        [GtkChild]
        private Adjustment adj_ma;

        [GtkChild]
        private Scale attack_scale;

        [GtkChild]
        private Scale release_scale;

        [GtkChild]
        private Scale threshold_scale;

        [GtkChild]
        private Scale ratio_scale;

        [GtkChild]
        private Scale knee_scale;

        [GtkChild]
        private Scale makeup_scale;

        [GtkChild]
        private ToggleButton makeup_auto;

        [GtkChild]
        private Meter comp_le;

        [GtkChild]
        private Meter comp_ga;

        construct {
        }

        public void set_text(string label) {
            (this.label_widget as Label).use_markup = true;
            this.label = label;
        }

        public void set_disabled(bool disabled) {
            base.set_sensitive(!disabled);
        }

        public void block_at() {
            SignalHandler.block_by_func(adj_at, (void *) at_changed, this);
        }

        public void unblock_at() {
            SignalHandler.unblock_by_func(adj_at, (void *) at_changed, this);
        }

        public void block_re() {
            SignalHandler.block_by_func(adj_re, (void *) re_changed, this);
        }

        public void unblock_re() {
            SignalHandler.unblock_by_func(adj_re, (void *) re_changed, this);
        }

        public void block_th() {
            SignalHandler.block_by_func(adj_th, (void *) th_changed, this);
        }

        public void unblock_th() {
            SignalHandler.unblock_by_func(adj_th, (void *) th_changed, this);
        }

        public void block_ra() {
            SignalHandler.block_by_func(adj_ra, (void *) ra_changed, this);
        }

        public void unblock_ra() {
            SignalHandler.unblock_by_func(adj_ra, (void *) ra_changed, this);
        }

        public void block_kn() {
            SignalHandler.block_by_func(adj_kn, (void *) kn_changed, this);
        }

        public void unblock_kn() {
            SignalHandler.unblock_by_func(adj_kn, (void *) kn_changed, this);
        }

        public void block_ma() {
            SignalHandler.block_by_func(adj_ma, (void *) ma_changed, this);
        }

        public void unblock_ma() {
            SignalHandler.unblock_by_func(adj_ma, (void *) ma_changed, this);
        }

        public void le_set_value(float val) {
            comp_le.adjustment.set_value(val);
        }

        public void ga_set_value(float val) {
            comp_ga.adjustment.set_value(val);
        }

        public void le_set_warn_point(float wp) {

        }

        public void ga_set_warn_point(float wp) {

        }

        public void set_auto_ma_label(string text) {
            makeup_auto.set_label(text);
        }

        public ulong connect_at(int state_id) {
            s_set_callback(state_id, (void *) at_changed);
            s_set_adjustment(state_id, adj_at);
            return Signal.connect(adj_at, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }

        public ulong connect_re(int state_id) {
            s_set_callback(state_id, (void *) re_changed);
            s_set_adjustment(state_id, adj_re);
            return Signal.connect(adj_re, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }

        public ulong connect_th(int state_id) {
            s_set_callback(state_id, (void *) th_changed);
            s_set_adjustment(state_id, adj_th);
            return Signal.connect(adj_th, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }

        public ulong connect_ra(int state_id) {
            s_set_callback(state_id, (void *) ra_changed);
            s_set_adjustment(state_id, adj_ra);
            return Signal.connect(adj_ra, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }

        public ulong connect_kn(int state_id) {
            s_set_callback(state_id, (void *) kn_changed);
            s_set_adjustment(state_id, adj_kn);
            return Signal.connect(adj_kn, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }

        public ulong connect_ma(int state_id) {
            s_set_callback(state_id, (void *) ma_changed);
            s_set_adjustment(state_id, adj_ma);
            return Signal.connect(adj_ma, "value-changed", (GLib.Callback) adj_cb, state_id.to_pointer());
        }
    }
}

