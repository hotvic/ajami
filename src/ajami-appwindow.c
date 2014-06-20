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


#include <gtk/gtk.h>

#include "ajami-app.h"
#include "ajami-appwindow.h"
#include "ajami-scenes.h"
#include "gtkmeter.h"


/* Forward declarations */
static void     ajami_app_window_class_init (AjamiAppWindowClass *kclass);
static void     ajami_app_window_init       (AjamiAppWindow      *win);
static void     ajami_app_window_dispose    (GObject             *object);
GtkWidget      *ajami_app_window_new        (AjamiApp            *app);
/** Action callbacks */
static void     activate_new_preset         (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_open_preset        (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_save_preset        (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_save_as_preset     (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_undo               (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_redo               (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_set_scene          (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_clear_scene        (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_name_scene         (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);
static void     activate_help_scene         (GSimpleAction       *action,
                                             GVariant            *parameter,
                                             gpointer             data);


struct _AjamiAppWindowPrivate
{
    GSettings     *settings;
    GtkMenuButton *gears;
    GtkWidget     *search;
    GtkWidget     *searchbar;
};

G_DEFINE_TYPE_WITH_PRIVATE(AjamiAppWindow, ajami_app_window, GTK_TYPE_APPLICATION_WINDOW);


static void
ajami_app_window_class_init (AjamiAppWindowClass *kclass)
{
    GType ts, tm;
    G_OBJECT_CLASS (kclass)->dispose = ajami_app_window_dispose;

    /* Work around */
    ts = G3JAMIN_TYPE_SCENES;
    tm = GTK_TYPE_METER;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (kclass),
                                                 "/org/ajami/ui/appwindow.ui");

    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (kclass), AjamiAppWindow, gears);
}

const GActionEntry win_entries[] = {
    { "new-preset",     activate_new_preset     },
    { "open-preset",    activate_open_preset    },
    { "save-preset",    activate_save_preset    },
    { "save-as-preset", activate_save_as_preset },
    { "undo",           activate_undo           },
    { "redo",           activate_redo           },
    { "set-scene",      activate_set_scene      },
    { "clear-scene",    activate_clear_scene    },
    { "name-scene",     activate_name_scene     },
    { "help-scene",     activate_help_scene     }
};

static void
ajami_app_window_init (AjamiAppWindow *win)
{
    GMenuModel *gearsmenu;
    GtkBuilder *builder;

    win->priv = ajami_app_window_get_instance_private (win);
    gtk_widget_init_template (GTK_WIDGET (win));

    g_action_map_add_action_entries (G_ACTION_MAP (win),
                                     win_entries,
                                     G_N_ELEMENTS (win_entries),
                                     NULL);

    builder = gtk_builder_new_from_resource ("/org/ajami/ui/menus.ui");
    
    gearsmenu = G_MENU_MODEL (gtk_builder_get_object (builder, "gearsmenu"));
    gtk_menu_button_set_menu_model (win->priv->gears, gearsmenu);

    g_object_unref (builder);
}

static void
ajami_app_window_dispose (GObject *object)
{
    AjamiAppWindow *win;

    win = AJAMI_APP_WINDOW (object);

    G_OBJECT_CLASS (ajami_app_window_parent_class)->dispose (object);
}


GtkWidget *
ajami_app_window_new (AjamiApp *app)
{
    return g_object_new (AJAMI_APP_WINDOW_TYPE, "application", app, NULL);
}

/* Action callbacks */
static void
activate_new_preset (GSimpleAction      *action,
                     GVariant           *parameter,
                     gpointer            data)
{

}

static void
activate_open_preset (GSimpleAction      *action,
                      GVariant           *parameter,
                      gpointer            data)
{

}

static void
activate_save_preset (GSimpleAction      *action,
                      GVariant           *parameter,
                      gpointer            data)
{

}

static void
activate_save_as_preset (GSimpleAction      *action,
                         GVariant           *parameter,
                         gpointer            data)
{

}

static void
activate_undo (GSimpleAction      *action,
               GVariant           *parameter,
               gpointer            data)
{

}

static void
activate_redo (GSimpleAction      *action,
               GVariant           *parameter,
               gpointer            data)
{

}

static void
activate_set_scene (GSimpleAction *action,
                    GVariant      *param,
                    gpointer       data)
{

}

static void
activate_clear_scene (GSimpleAction *action,
                      GVariant      *param,
                      gpointer       data)
{

}

static void
activate_name_scene (GSimpleAction *action,
                     GVariant      *param,
                     gpointer       data)
{

}

static void
activate_help_scene (GSimpleAction *action,
                     GVariant      *param,
                     gpointer       data)
{

}