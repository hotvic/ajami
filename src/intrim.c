/*
 * This file is part of AJAMI.
 *
 * Copyright (C) 2003 Steve Harris
 * Copyright (C) 2014 Victor A. Santos <victoraur.santos@gmail.com>
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include "io.h"
#include "main.h"
#include "compressor-ui.h"
#include "limiter-ui.h"
#include "process.h"
#include "support.h"
#include "intrim.h"
#include "state.h"
#include "db.h"
#include "ajamiobjects.h"


static float inmeter_warn_level, outmeter_warn_level, rmsmeter_warn_level;
static gboolean out_meter_peak_pref = TRUE, rms_meter_peak_pref = TRUE;

void intrim_cb(int id, float value);
void outtrim_cb(int id, float value);
void inpan_cb(int id, float value);

float in_gain[2] = {1.0f, 1.0f};
float out_gain = 1.0f;
float in_trim_gain = 1.0f;
float in_pan_gain[2] = {1.0f, 1.0f};

void bind_intrim()
{
    GtkScale *in_gain, *out_gain, *in_stereo;

    in_gain   = ajami_main_window_get_w_in_amp(main_window);
    out_gain  = ajami_main_window_get_w_in_stereo(main_window);
    in_stereo = ajami_main_window_get_w_out_amp(main_window);

    ajami_main_window_set_inmeter_value(main_window, AJAMI_METER_SIDE_METER_L, -60.0);
    ajami_main_window_set_inmeter_value(main_window, AJAMI_METER_SIDE_METER_R, -60.0);
    ajami_main_window_set_outmeter_value(main_window, AJAMI_METER_SIDE_METER_L, -60.0);
    ajami_main_window_set_outmeter_value(main_window, AJAMI_METER_SIDE_METER_R, -60.0);
    ajami_main_window_set_rmsmeter_value(main_window, AJAMI_METER_SIDE_METER_L, -60.0);
    ajami_main_window_set_rmsmeter_value(main_window, AJAMI_METER_SIDE_METER_R, -60.0);

    /* TODO: conditionally? set presets window meter values
    gtk_adjustment_set_value(in_meter_adj[2], -60.0);
    gtk_adjustment_set_value(in_meter_adj[3], -60.0); */

    /* TODO: conditionally? set presets window meter values
    gtk_adjustment_set_value(out_meter_adj[2], -60.0);
    gtk_adjustment_set_value(out_meter_adj[3], -60.0); */

    s_set_callback(S_IN_GAIN, intrim_cb);
    s_set_adjustment(S_IN_GAIN, gtk_range_get_adjustment(GTK_RANGE(in_gain)));
    //s_set_adjustment(S_IN_GAIN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_in_trim_scale"))));

    s_set_callback(S_OUT_GAIN, outtrim_cb);
    s_set_adjustment(S_OUT_GAIN, gtk_range_get_adjustment(GTK_RANGE(out_gain)));
    //s_set_adjustment(S_OUT_GAIN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_out_trim_scale"))));

    s_set_callback(S_IN_PAN, inpan_cb);
    s_set_adjustment(S_IN_PAN, gtk_range_get_adjustment(GTK_RANGE(in_stereo)));
    //s_set_adjustment(S_IN_PAN, gtk_range_get_adjustment(GTK_RANGE(lookup_widget(presets_window, "presets_pan_scale"))));
}

void intrim_cb(int id, float value)
{
    in_trim_gain = db2lin(value);
    in_gain[0] = in_trim_gain * in_pan_gain[0];
    in_gain[1] = in_trim_gain * in_pan_gain[1];
}

void outtrim_cb(int id, float value)
{
    out_gain = db2lin(value);
}

void inpan_cb(int id, float value)
{
    in_pan_gain[0] = db2lin(value * -0.5f);
    in_pan_gain[1] = db2lin(value * 0.5f);
    in_gain[0] = in_trim_gain * in_pan_gain[0];
    in_gain[1] = in_trim_gain * in_pan_gain[1];
}

void in_meter_value(float amp[])
{
    ajami_main_window_set_inmeter_value(main_window, AJAMI_METER_SIDE_METER_L, lin2db(amp[0]));
    ajami_main_window_set_inmeter_value(main_window, AJAMI_METER_SIDE_METER_R, lin2db(amp[1]));

    /* TODO: conditionally? lookup presets window
    gtk_adjustment_set_value(in_meter_adj[2], lin2db(amp[0]));
    gtk_adjustment_set_value(in_meter_adj[3], lin2db(amp[1])); */

    amp[0] = 0.0f;
    amp[1] = 0.0f;
}

void out_meter_value(float amp[])
{
    char tmp[256];
    float lamp[2];

    lamp[0] = lin2db (amp[0]);
    lamp[1] = lin2db (amp[1]);

    ajami_main_window_set_outmeter_value(main_window, AJAMI_METER_SIDE_METER_L, lin2db(amp[0]));
    ajami_main_window_set_outmeter_value(main_window, AJAMI_METER_SIDE_METER_R, lin2db(amp[1]));

    /* TODO: conditionally? lookup presets window
    gtk_adjustment_set_value(out_meter_adj[2], lin2db(amp[0]));
    gtk_adjustment_set_value(out_meter_adj[3], lin2db(amp[1])); */

    if (out_meter_peak_pref)
    {
        lamp[0] = ajami_main_window_get_outmeter_peak(main_window, AJAMI_METER_SIDE_METER_L);
        lamp[1] = ajami_main_window_get_outmeter_peak(main_window, AJAMI_METER_SIDE_METER_R);
    }
    else
    {
        if (lamp[0] < -60.0) lamp[0] = -60.0;
        if (lamp[1] < -60.0) lamp[1] = -60.0;
    }

    snprintf (tmp, 255, "%.1f", lamp[0]);
    ajami_main_window_set_out_text(main_window, 0, tmp);
    snprintf (tmp, 255, "%.1f", lamp[1]);
    ajami_main_window_set_out_text(main_window, 1, tmp);

    amp[0] = 0.0f;
    amp[1] = 0.0f;
}

void rms_meter_value(float amp[])
{
    char tmp[256];
    float lamp[2];

    lamp[0] = lin2db (amp[0]);
    lamp[1] = lin2db (amp[1]);

    ajami_main_window_set_rmsmeter_value(main_window, AJAMI_METER_SIDE_METER_L, lamp[0]);
    ajami_main_window_set_rmsmeter_value(main_window, AJAMI_METER_SIDE_METER_R, lamp[1]);

    if (rms_meter_peak_pref)
    {
        lamp[0] = ajami_main_window_get_rmsmeter_peak(main_window, AJAMI_METER_SIDE_METER_L);
        lamp[1] = ajami_main_window_get_rmsmeter_peak(main_window, AJAMI_METER_SIDE_METER_R);
    }
    else
    {
        if (lamp[0] < -60.0) lamp[0] = -60.0;
        if (lamp[1] < -60.0) lamp[1] = -60.0;
    }

    snprintf (tmp, 255, "%.1f", lamp[0]);
    ajami_main_window_set_rmsout_text(main_window, 0, tmp);
    snprintf (tmp, 255, "%.1f", lamp[1]);
    ajami_main_window_set_rmsout_text(main_window, 1, tmp);

    amp[0] = 0.0f;
    amp[1] = 0.0f;
}

gboolean update_meters() {
    int glob, eq, comp[3], limiter;


    in_meter_value(in_peak);
    out_meter_value(out_peak);

    /* Only update these meters if main window is displayed */
    if (gui_mode == 0) {
        rms_meter_value(rms_peak);
        limiter_meters_update();
        compressor_meters_update();
        // spectrum_timeout_check();
        s_crossfade_ui();
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

    return TRUE;
}

void intrim_set_out_meter_peak_pref (gboolean pref)
{
    out_meter_peak_pref = pref;
}

gboolean intrim_get_out_meter_peak_pref ()
{
    return (out_meter_peak_pref);
}

void intrim_set_rms_meter_peak_pref (gboolean pref)
{
    rms_meter_peak_pref = pref;
}

gboolean intrim_get_rms_meter_peak_pref ()
{
    return (rms_meter_peak_pref);
}

void intrim_inmeter_reset_peak ()
{
    ajami_main_window_reset_inmeter_peak(main_window);
}

void intrim_outmeter_reset_peak ()
{
    ajami_main_window_reset_outmeter_peak(main_window);
}

void intrim_rmsmeter_reset_peak ()
{
    ajami_main_window_reset_rmsmeter_peak(main_window);
}

void intrim_inmeter_set_warn (float level)
{
    inmeter_warn_level = level;

    ajami_main_window_set_inmeter_warn_point(main_window, level);
}

void intrim_outmeter_set_warn (float level)
{
    outmeter_warn_level = level;

    ajami_main_window_set_outmeter_warn_point(main_window, level);
}

void intrim_rmsmeter_set_warn (float level)
{
    rmsmeter_warn_level = level;

    ajami_main_window_set_rmsmeter_warn_point(main_window, level);
}

float intrim_inmeter_get_warn ()
{
    return (inmeter_warn_level);
}

float intrim_outmeter_get_warn ()
{
    return (outmeter_warn_level);
}

float intrim_rmsmeter_get_warn ()
{
    return (rmsmeter_warn_level);
}
