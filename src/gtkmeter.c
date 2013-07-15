/*  
 * Copyright (c) 2013 Victor Aurélio Santos
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "gtkmeter.h"


GtkWidget *
gtk_meter_new(GtkOrientation ori)
{
    GtkWidget * new_meter;

    new_meter = gtk_level_bar_new();
    
    gtk_orientable_set_orientation(GTK_ORIENTABLE (new_meter), ori);

    // set low offset to 0.0 and remove high
    gtk_level_bar_add_offset_value(GTK_LEVEL_BAR (new_meter), "low", 0.0);
    gtk_level_bar_remove_offset_value(GTK_LEVEL_BAR (new_meter), "high");
 
    return new_meter;
}

void
gtk_meter_set_extreme_values(GtkLevelBar * meter,
                             gdouble min,
                             gdouble max)
{
    gtk_level_bar_set_min_value(meter, min);
    gtk_level_bar_set_max_value(meter, max);
}

void
gtk_meter_set_warn_point(GtkLevelBar * meter,
                         gdouble warnpt)
{
    gtk_level_bar_add_offset_value (meter, "warn", warnpt);
}

void
gtk_meter_set_over_point(GtkLevelBar * meter,
                         gdouble overpt)
{
    gtk_level_bar_add_offset_value (meter, "over", overpt);
}
