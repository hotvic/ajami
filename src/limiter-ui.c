/*
 *  Copyright (C) 2003 Steve Harris
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  $Id: limiter-ui.c,v 1.19 2007/07/01 15:33:18 jdepner Exp $
 */

#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>

#include "process.h"
#include "support.h"
#include "main.h"
#include "state.h"
#include "db.h"
#include "process.h"
#include "limiter-ui.h"
#include "ajamiobjects.h"


void li_changed(int id, float value);
void lh_changed(int id, float value);
void ll_changed(int id, float value);
void boost_changed(int id, float value);
void logscale_changed (int id, float value);

static AjamiLimiter *w_limiter;
static GtkAdjustment *lh_adj, *ll_adj;
static GtkLabel *lh_label, *ll_label, *l_limiterlabel = NULL, *l_logscale_label = NULL;

static char limiter_text[2][42] = {"<b>Fast-lookahead-limiter (Harris)</b>", "<b>Foo-limiter (Savolainen)</b>"};

static GtkAdjustment *in_meter_adj, *att_meter_adj, *out_meter_adj;
static GtkScale *l_logscale_scale = NULL;


void bind_limiter()
{
    GtkWidget *scale;

    w_limiter = ajami_get_limiter_widget();

    ajami_limiter_set_label(w_limiter, limiter_text[process_get_limiter_plugin()]);

    /* TODO: add support to logscale in FOO plugin
    l_logscale_label = GTK_LABEL (lookup_widget (main_window, "logscale_label"));
    l_logscale_scale = GTK_SCALE (lookup_widget (main_window, "logscale_scale"));
    if (process_get_limiter_plugin () == FOO)
    {
        limiter_logscale_set_state (TRUE);
    }
    else
    {
        limiter_logscale_set_state (FALSE);
    }
    s_set_adjustment (S_LIM_LOGSCALE, gtk_range_get_adjustment (GTK_RANGE (GTK_WIDGET (l_logscale_scale))));
    s_set_callback (S_LIM_LOGSCALE, logscale_changed); */


    s_set_callback(S_LIM_INPUT, li_changed);


    scale  = ajami_limiter_get_w_s_rel(w_limiter);
    lh_adj = gtk_range_get_adjustment(GTK_RANGE(scale));

    s_set_adjustment(S_LIM_TIME, lh_adj);
    s_set_callback(S_LIM_TIME, lh_changed);

    scale  = ajami_limiter_get_w_s_lim(w_limiter);
    ll_adj = gtk_range_get_adjustment(GTK_RANGE(scale));

    s_set_adjustment(S_LIM_LIMIT, ll_adj);
    s_set_callback(S_LIM_LIMIT, ll_changed);

    s_set_value(S_LIM_INPUT, 0.0f, 0);
    s_set_value(S_LIM_TIME,  0.05f, 0);
    s_set_value(S_LIM_LIMIT, 0.0f, 0);

    in_meter_adj  = ajami_limiter_get_w_adj_inmeter(w_limiter);
    att_meter_adj = ajami_limiter_get_w_adj_relmeter(w_limiter);
    out_meter_adj = ajami_limiter_get_w_adj_outmeter(w_limiter);

    // Handle waveshaper boost stuff
    // scale = lookup_widget(main_window, "boost_scale");
    // s_set_adjustment(S_BOOST, gtk_range_get_adjustment(GTK_RANGE(scale)));
    // s_set_callback(S_BOOST, boost_changed); */
}

void li_changed(int id, float value)
{
    limiter[limiter_plugin].ingain = value;
}

void lh_changed(int id, float value)
{
    char text[256];

    const float val = powf(10.0f, value);
    if (val >= 100.0f)
    {
        snprintf(text, 255, _("%.3g s"), val * 0.001f);
    }
    else
    {
        snprintf(text, 255, _("%.4g ms"), val);
    }
    ajami_limiter_set_rel_label(w_limiter, text);

    limiter[limiter_plugin].release = powf(10.0f, value - 3.0f);
}

void ll_changed(int id, float value)
{
    char text[256];

    limiter[limiter_plugin].limit = value;

    snprintf(text, 255, _("%.1f dB"), value);
    ajami_limiter_set_lim_label(w_limiter, text);
}

void boost_changed(int id, float value)
{
    process_set_ws_boost(value);
}

void logscale_changed(int id, float value)
{
    process_set_limiter_logscale (value);
}

void limiter_meters_update()
{
    float peak_in = lin2db(lim_peak[LIM_PEAK_IN]);
    float peak_out = lin2db(lim_peak[LIM_PEAK_OUT]);
    float atten = -limiter[limiter_plugin].attenuation;
    lim_peak[LIM_PEAK_IN] = 0.0f;
    lim_peak[LIM_PEAK_OUT] = 0.0f;

    gtk_adjustment_set_value(in_meter_adj, peak_in);
    gtk_adjustment_set_value(att_meter_adj, atten);
    gtk_adjustment_set_value(out_meter_adj, peak_out);
}

void limiter_inmeter_reset_peak ()
{
    ajami_limiter_reset_inmeter_peak(ajami_get_limiter_widget());
}

void limiter_outmeter_reset_peak ()
{
    ajami_limiter_reset_relmeter_peak(ajami_get_limiter_widget());
    ajami_limiter_reset_outmeter_peak(ajami_get_limiter_widget());
}

void limiter_set_label (int limiter_plugin)
{
    if (l_limiterlabel)
    {
        ajami_limiter_set_label(w_limiter, limiter_text[limiter_plugin]);
    }
}

void limiter_logscale_set_state (gboolean state)
{
    if (l_logscale_label)
    {
        gtk_widget_set_sensitive (GTK_WIDGET (l_logscale_label), state);
        gtk_widget_set_sensitive (GTK_WIDGET (l_logscale_scale), state);
    }
}

/* vi:set ts=8 sts=4 sw=4: */
