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


namespace Ajami {
    [GtkTemplate (ui="/org/ajami/ajami/gtk/compressor.ui")]
    public class Compressor : Gtk.Frame {
        public Compressor() {
            Object();
        }

        public void set_label(string label) {
            (this.label_widget as Label).use_markup = true;
            this.label = label;
        }

        public void set_disabled(bool disabled) {
            base.set_sensitive(!disabled);
        }
    }
}

