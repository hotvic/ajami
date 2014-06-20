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


#define G3JAMIN_APP_WINDOW_TYPE (g3jamin_app_window_get_type ())
#define G3JAMIN_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), G3JAMIN_APP_WINDOW_TYPE, G3JAMinAppWindow))


typedef struct _G3JAMinAppWindow         G3JAMinAppWindow;
typedef struct _G3JAMinAppWindowClass    G3JAMinAppWindowClass;
typedef struct _G3JAMinAppWindowPrivate  G3JAMinAppWindowPrivate;

struct _G3JAMinAppWindow
{
    GtkApplicationWindow parent;

    G3JAMinAppWindowPrivate *priv;
};

struct _G3JAMinAppWindowClass
{
    GtkApplicationWindowClass parent_class;
};


/* Public methods */
GType         g3jamin_app_window_get_type    (void);
GtkWidget    *g3jamin_app_window_new         (G3JAMinApp        *app);
void          g3jamin_app_window_open        (G3JAMinAppWindow *win,
                                              GFile             *file);


#endif /* __AJAMIAPPWINDOW_H */

