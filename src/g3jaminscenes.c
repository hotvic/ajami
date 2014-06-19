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
static void     g3jamin_scenes_class_init            (G3JAMinScenesClass *class);
static void     g3jamin_scenes_init                  (G3JAMinScenes      *scenes);
static void     g3jamin_scenes_dispose               (GObject            *object);
GtkWidget      *g3jamin_scenes_new                   (void);
/** Callbacks **/   
gboolean        g3jamin_scenes_button_press_event    (GtkWidget          *widget,
                                                      GdkEvent           *event,
                                                      gpointer           *data);

/* Signals */
enum {
    ACTIVATE,
    CLEAR,
    POPOVER_MENU,

    LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = { 0 };


struct _G3JAMinScenesPrivate
{
    /* Scenes context menu */
    GtkWidget *popover;

    /* Scenes */
    GtkWidget *scene_1;
    GtkWidget *scene_2;
    GtkWidget *scene_3;
    GtkWidget *scene_4;
    GtkWidget *scene_5;
    GtkWidget *scene_6;
    GtkWidget *scene_7;
    GtkWidget *scene_8;
    GtkWidget *scene_9;
    GtkWidget *scene_10;
    GtkWidget *scene_11;
    GtkWidget *scene_12;
    GtkWidget *scene_13;
    GtkWidget *scene_14;
    GtkWidget *scene_15;
    GtkWidget *scene_16;
    GtkWidget *scene_17;
    GtkWidget *scene_18;
    GtkWidget *scene_19;
    GtkWidget *scene_20;
};

G_DEFINE_TYPE_WITH_PRIVATE(G3JAMinScenes, g3jamin_scenes, GTK_TYPE_BOX);


static void
g3jamin_scenes_class_init (G3JAMinScenesClass *kclass)
{
    GObjectClass   *object_class = G_OBJECT_CLASS (kclass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (kclass);

    G_OBJECT_CLASS (kclass)->dispose = g3jamin_scenes_dispose;

    signals[ACTIVATE] =
            g_signal_new ("activate",
                          G_OBJECT_CLASS_TYPE (object_class),
                          G_SIGNAL_RUN_FIRST,
                          G_STRUCT_OFFSET (G3JAMinScenesClass, activate),
                          NULL, NULL,
                          g_cclosure_marshal_VOID__OBJECT,
                          G_TYPE_NONE,
                          2,
                          G3JAMIN_TYPE_SCENES,
                          GTK_TYPE_WIDGET);
    signals[CLEAR] =
            g_signal_new ("clear",
                          G_OBJECT_CLASS_TYPE (object_class),
                          G_SIGNAL_RUN_FIRST,
                          G_STRUCT_OFFSET (G3JAMinScenesClass, clear),
                          NULL, NULL,
                          g_cclosure_marshal_VOID__OBJECT,
                          G_TYPE_NONE,
                          2,
                          G3JAMIN_TYPE_SCENES,
                          GTK_TYPE_WIDGET);
    signals[POPOVER_MENU] =
            g_signal_new ("popover-menu",
                          G_OBJECT_CLASS_TYPE (object_class),
                          G_SIGNAL_RUN_FIRST,
                          G_STRUCT_OFFSET (G3JAMinScenesClass, popover_menu),
                          NULL, NULL,
                          g_cclosure_marshal_VOID__OBJECT,
                          G_TYPE_NONE,
                          2,
                          G3JAMIN_TYPE_SCENES,
                          GTK_TYPE_WIDGET);

    gtk_widget_class_set_template_from_resource (widget_class,
                                                 "/org/g3jamin/ui/scenes.ui");
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_1);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_2);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_3);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_4);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_5);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_6);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_7);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_8);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_9);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_10);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_11);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_12);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_13);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_14);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_15);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_16);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_17);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_18);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_19);
    gtk_widget_class_bind_template_child_private (widget_class, G3JAMinScenes, scene_20);

    gtk_widget_class_bind_template_callback (widget_class, g3jamin_scenes_button_press_event);
}

static void
g3jamin_scenes_init (G3JAMinScenes *scenes)
{
    GMenuModel *model;
    GtkBuilder *builder;

    scenes->priv = g3jamin_scenes_get_instance_private (scenes);
    gtk_widget_init_template (GTK_WIDGET (scenes));

    builder = gtk_builder_new_from_resource ("/org/g3jamin/ui/menus.ui");
    model = G_MENU_MODEL (gtk_builder_get_object (builder, "scene_menu"));
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

void
g3jamin_scenes_activate_scene (G3JAMinScenes *scenes,
                               GtkWidget     *scene)
{
    g_return_if_fail (scenes != NULL);
    g_return_if_fail (scene != NULL);

    gtk_image_set_from_resource (GTK_IMAGE (scene),
                                 "/org/g3jamin/pixmaps/LED_green_on.xpm");
}

void
g3jamin_scenes_popover_scene (G3JAMinScenes *scenes,
                              GtkWidget     *scene)
{
    g_return_if_fail (scenes != NULL);
    g_return_if_fail (scene != NULL);
}


/* Callbacks */
gboolean
g3jamin_scenes_button_press_event (GtkWidget *widget,
                                   GdkEvent  *event,
                                   gpointer  *data)
{
    switch (((GdkEventButton*)event)->button)
    {
    case 1: /* Left button */
        g_signal_emit (G_OBJECT (data),
                       signals[ACTIVATE],
                       0,
                       G3JAMIN_SCENES (data),
                       gtk_bin_get_child (GTK_BIN (widget)));
        g3jamin_scenes_activate_scene (G3JAMIN_SCENES (data),
                                       gtk_bin_get_child (GTK_BIN (widget)));
        break;
    case 2: /* Middle button */
        g_signal_emit (G_OBJECT (data),
                       signals[CLEAR],
                       0,
                       G3JAMIN_SCENES (data),
                       widget);
        break;
    case 3: /* Right button */
        g_signal_emit (G_OBJECT (data),
                       signals[POPOVER_MENU],
                       0,
                       G3JAMIN_SCENES (data),
                       widget);
        g3jamin_scenes_popover_scene (G3JAMIN_SCENES (data),
                                      gtk_bin_get_child (GTK_BIN (widget)));
        break;
    }

    return FALSE;
}