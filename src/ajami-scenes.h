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


#ifndef __AJAMISCENES_H
#define __AJAMISCENES_H


#include <gtk/gtk.h>


#define AJAMI_TYPE_SCENES                  (ajami_scenes_get_type ())
#define AJAMI_SCENES(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), AJAMI_TYPE_SCENES, AjamiScenes))
#define AJAMI_IS_SCENES(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), AJAMI_TYPE_SCENES))
#define AJAMI_SCENES_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), AJAMI_TYPE_SCENES, AjamiScenesClass))
#define AJAMI_IS_SCENES_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), AJAMI_TYPE_SCENES))
#define AJAMI_SCENES_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), AJAMI_TYPE_SCENES, AjamiScenesClass))


typedef struct _AjamiScenes         AjamiScenes;
typedef struct _AjamiScenesClass    AjamiScenesClass;
typedef struct _AjamiScenesPrivate  AjamiScenesPrivate;

struct _AjamiScenes
{
    GtkApplicationWindow parent;

    AjamiScenesPrivate *priv;
};

struct _AjamiScenesClass
{
    GtkApplicationWindowClass parent_class;

    /* Signals */
    void    (* activate)        (AjamiScenes *scenes,
                                 GtkWidget     *scene);
    void    (* clear)           (AjamiScenes *scenes,
                                 GtkWidget     *scene);
    void    (* popover_menu)    (AjamiScenes *scenes,
                                 GtkWidget     *scene);
};


/* Public methods */
GType         ajami_scenes_get_type    (void);
GtkWidget    *ajami_scenes_new         (void);


#endif /* __AJAMISCENES_H */
