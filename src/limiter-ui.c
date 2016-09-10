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
#include "db.h"
#include "process.h"
#include "limiter-ui.h"
#include "state.h"
#include "ajamiobjects.h"

void li_changed(int id, double value);
void lh_changed(int id, double value);
void ll_changed(int id, double value);
void boost_changed(int id, double value);
void logscale_changed (int id, double value);

static AjamiLimiter *w_limiter;
static GtkAdjustment *lh_adj, *ll_adj;
static GtkLabel *lh_label, *ll_label, *l_limiterlabel = NULL, *l_logscale_label = NULL;

static GtkAdjustment *in_meter_adj, *att_meter_adj, *out_meter_adj;
static GtkScale *l_logscale_scale = NULL;


void bind_limiterrr()
{

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
    ajami_state_set_adjustment(ajami_get_state(), AJAMI_STATE_FLAGS_LIM_LOGSCALE, gtk_range_get_adjustment (GTK_RANGE (GTK_WIDGET (l_logscale_scale))));
    ajami_state_set_callback(ajami_get_state(), AJAMI_STATE_FLAGS_LIM_LOGSCALE, logscale_changed); */

    // Handle waveshaper boost stuff
    // scale = lookup_widget(main_window, "boost_scale");
    // ajami_state_set_adjustment(ajami_get_state(), AJAMI_STATE_FLAGS_BOOST, gtk_range_get_adjustment(GTK_RANGE(scale)));
    // ajami_state_set_callback(ajami_get_state(), AJAMI_STATE_FLAGS_BOOST, boost_changed); */
}



/* vi:set ts=8 sts=4 sw=4: */
