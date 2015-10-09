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

extern float sample_rate;

namespace Ajami {
    private static int BINS = 2048;


    public class Spectrum : Gtk.Box {
        private static bool timeout_ret      = true;
        private static int timeout_countdown = 0;
        private static int frequency         = 10;
        private Adjustment[] adjustments;
        private float[] band_freq;
        private float[] band_bin_count;
        private int[] bin_bands;
        private long[] band_bin;

        private static string[] bands = {
            "25.0", "31.5", "40.0", "50.0", "63.0", "80.0", "100", "125",
            "160", "200", "250",  "315",  "400",  "500",  "630",  "800",
            "1k",  "1k25", "1k6", "2k", "2k5",  "3k1",  "4k",   "5k",
            "6k3",  "8k",   "10k", "10k2", "16k", "20k"
        };

        public Spectrum() {
            Object(orientation: Gtk.Orientation.HORIZONTAL);

            foreach (string band in bands) {
                var vbox = new Box(Gtk.Orientation.VERTICAL, 1);
                this.pack_start(vbox, true, true, 0);

                adjustments += new Adjustment(0.0, -60.0, 3.0, 0.0, 0.0, 0.0);

                var meter = new Meter(Gtk.Orientation.VERTICAL, adjustments[-1]);
                vbox.pack_start(meter, true, true, 0);

                var label = new Label(band);
                vbox.pack_start(label, false, true, 0);
            }

            for (int band = 0; band < bands.length; band++) {
                band_freq += 1000.0f * Math.powf(10.0f, (band - 16) * 0.1f);
                // stdout.printf("band %d is at %f Hz\n", band, band_freq[band]);
                band_bin_count += 0;
            }

            for (int bin = 0; bin < BINS / 2; bin++) {
                float bin_freq = (bin + 0.5f) * sample_rate / BINS;
                int nearest_band = 0;
                float nearest_dist = 9999999.0f;

                for (int band = 0; band < bands.length; band++) {
                    if (Math.fabs(bin_freq - band_freq[band]) < nearest_dist) {
                        nearest_band = band;
                        nearest_dist = Math.fabsf(bin_freq - band_freq[band]);
                    }
                }
                bin_bands += nearest_band;
                //stdout.printf("bin %d (%f Hz) is nearest band %d (%f Hz)\n", bin, bin_freq, nearest_band, band_freq[nearest_band]);
                band_bin_count[nearest_band]++;
            }

            for (int band = 0; band < bands.length; band++) {
                if (band_bin_count[band] == 0) {
                    band_bin += Math.lroundf(band_freq[band]) * BINS / Math.lround(sample_rate);
                    // stdout.printf("band %d is unassigned, use bin %d\n", band, band_bin[band]);
                } else {
                    /* Mark for no reverse lookup */
                    band_bin += -1;
                }
            }

            this.show_all();
        }

        public static void set_frequency(int freq) {
            timeout_ret = false;
            timeout_countdown = 11;
            frequency = freq;
        }

        public static int get_frequency() {
            return frequency;
        }

        public bool update() {
            return timeout_ret;
        }
    }
}
