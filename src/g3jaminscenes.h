/*
 * This file is part of G3JAMin.
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


#ifndef __G3JAMINSCENES_H
#define __G3JAMINSCENES_H


#include <gtk/gtk.h>


#define G3JAMIN_TYPE_SCENES                  (g3jamin_scenes_get_type ())
#define G3JAMIN_SCENES(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), G3JAMIN_TYPE_SCENES, G3JAMinScenes))
#define G3JAMIN_IS_SCENES(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G3JAMIN_TYPE_SCENES))
#define G3JAMIN_SCENES_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), G3JAMIN_TYPE_SCENES, G3JAMinScenesClass))
#define G3JAMIN_IS_SCENES_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), G3JAMIN_TYPE_SCENES))
#define G3JAMIN_SCENES_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), G3JAMIN_TYPE_SCENES, G3JAMinScenesClass))


typedef struct _G3JAMinScenes         G3JAMinScenes;
typedef struct _G3JAMinScenesClass    G3JAMinScenesClass;
typedef struct _G3JAMinScenesPrivate  G3JAMinScenesPrivate;

struct _G3JAMinScenes
{
    GtkApplicationWindow parent;

    G3JAMinScenesPrivate *priv;
};

struct _G3JAMinScenesClass
{
    GtkApplicationWindowClass parent_class;

    /* Signals */
    void    (* activate)        (G3JAMinScenes *scenes,
                                 GtkWidget     *scene);
    void    (* clear)           (G3JAMinScenes *scenes,
                                 GtkWidget     *scene);
    void    (* popover_menu)    (G3JAMinScenes *scenes,
                                 GtkWidget     *scene);
};


/* Public methods */
GType         g3jamin_scenes_get_type    (void);
GtkWidget    *g3jamin_scenes_new         (void);


#endif /* __G3JAMINSCENES_H */
