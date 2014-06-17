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


#include <gtk/gtk.h>

#include "g3jaminscenes.h"


/* Forward declarations */
static void     g3jamin_scenes_class_init (G3JAMinScenesClass *class);
static void     g3jamin_scenes_init       (G3JAMinScenes      *scenes);
static void     g3jamin_scenes_dispose    (GObject            *object);
GtkWidget      *g3jamin_scenes_new        (void);


struct _G3JAMinScenesPrivate
{

};

G_DEFINE_TYPE_WITH_PRIVATE(G3JAMinScenes, g3jamin_scenes, GTK_TYPE_BOX);


static void
g3jamin_scenes_class_init (G3JAMinScenesClass *class)
{
    G_OBJECT_CLASS (class)->dispose = g3jamin_scenes_dispose;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                                 "/org/g3jamin/ui/scenes.ui");
}

static void
g3jamin_scenes_init (G3JAMinScenes *scenes)
{
    scenes->priv = g3jamin_scenes_get_instance_private (scenes);
    gtk_widget_init_template (GTK_WIDGET (scenes));
}

static void
g3jamin_scenes_dispose (GObject *object)
{
  G3JAMinScenes *scenes;

  scenes = G3JAMIN_SCENES (object);

  G_OBJECT_CLASS (g3jamin_scenes_parent_class)->dispose (object);
}

GtkWidget *
g3jamin_scenes_new (void)
{
  return g_object_new (G3JAMIN_TYPE_SCENES, NULL);
}
