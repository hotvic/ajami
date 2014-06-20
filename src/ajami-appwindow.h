/*
 * This file is part of AJAMI.
 *
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


#ifndef __AJAMIAPPWINDOW_H
#define __AJAMIAPPWINDOW_H


#include <gtk/gtk.h>

#include "ajami-app.h"


#define AJAMI_APP_WINDOW_TYPE (ajami_app_window_get_type ())
#define AJAMI_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), AJAMI_APP_WINDOW_TYPE, AjamiAppWindow))


typedef struct _AjamiAppWindow         AjamiAppWindow;
typedef struct _AjamiAppWindowClass    AjamiAppWindowClass;
typedef struct _AjamiAppWindowPrivate  AjamiAppWindowPrivate;

struct _AjamiAppWindow
{
    GtkApplicationWindow parent;

    AjamiAppWindowPrivate *priv;
};

struct _AjamiAppWindowClass
{
    GtkApplicationWindowClass parent_class;
};


/* Public methods */
GType         ajami_app_window_get_type    (void);
GtkWidget    *ajami_app_window_new         (AjamiApp       *app);
void          ajami_app_window_open        (AjamiAppWindow *win,
                                            GFile          *file);


#endif /* __AJAMIAPPWINDOW_H */

