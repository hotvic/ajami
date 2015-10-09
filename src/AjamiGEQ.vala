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
    public class GraphicEQ : Gtk.Box {
        private Scale bands[31];

        construct {
            var bands_box = new Box(Orientation.HORIZONTAL, 0);
            for (int i = 0; i < 31; i ++) {
                var scale_box = new Box(Orientation.VERTICAL, 0);

                bands[i] = new Scale.with_range(Orientation.VERTICAL, -12, 12, 0.1);
                bands[i].inverted = true;
                scale_box.pack_start(bands[i], true, true, 0);

                bands_box.pack_start(scale_box, true, true, 0);
            }
            this.pack_start(bands_box, true, true, 0);

            this.show_all();
        }

        public GraphicEQ() {
            Object(orientation: Orientation.VERTICAL);
        }

        public Scale get_w_eq_band(int num) {
            return bands[num];
        }
    }
}
