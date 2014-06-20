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

#include "g3jaminapp.h"
#include "g3jaminappwindow.h"
#include "g3jaminscenes.h"
#include "gtkmeter.h"


/* Forward declarations */
static void     g3jamin_app_window_class_init (G3JAMinAppWindowClass *class);
static void     g3jamin_app_window_init       (G3JAMinAppWindow      *win);
static void     g3jamin_app_window_dispose    (GObject               *object);
GtkWidget      *g3jamin_app_window_new        (G3JAMinApp            *app);
/** Action callbacks */
static void     activate_new_preset           (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_open_preset          (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_save_preset          (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_save_as_preset       (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_undo                 (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_redo                 (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_set_scene            (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_clear_scene          (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_name_scene           (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);
static void     activate_help_scene           (GSimpleAction      *action,
                                               GVariant           *parameter,
                                               gpointer            data);


struct _G3JAMinAppWindowPrivate
{
    GSettings     *settings;
    GtkMenuButton *gears;
    GtkWidget     *search;
    GtkWidget     *searchbar;
};

G_DEFINE_TYPE_WITH_PRIVATE(G3JAMinAppWindow, g3jamin_app_window, GTK_TYPE_APPLICATION_WINDOW);


static void
g3jamin_app_window_class_init (G3JAMinAppWindowClass *class)
{
    GType ts, tm;
    G_OBJECT_CLASS (class)->dispose = g3jamin_app_window_dispose;

    /* Work around */
    ts = G3JAMIN_TYPE_SCENES;
    tm = GTK_TYPE_METER;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                                 "/org/g3jamin/ui/appwindow.ui");

    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), G3JAMinAppWindow, gears);
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
g3jamin_app_window_init (G3JAMinAppWindow *win)
{
    GMenuModel *gearsmenu;
    GtkBuilder *builder;

    win->priv = g3jamin_app_window_get_instance_private (win);
    gtk_widget_init_template (GTK_WIDGET (win));

    g_action_map_add_action_entries (G_ACTION_MAP (win),
                                     win_entries,
                                     G_N_ELEMENTS (win_entries),
                                     NULL);

    builder = gtk_builder_new_from_resource ("/org/g3jamin/ui/menus.ui");
    
    gearsmenu = G_MENU_MODEL (gtk_builder_get_object (builder, "gearsmenu"));
    gtk_menu_button_set_menu_model (win->priv->gears, gearsmenu);

    g_object_unref (builder);
}

static void
g3jamin_app_window_dispose (GObject *object)
{
    G3JAMinAppWindow *win;

    win = G3JAMIN_APP_WINDOW (object);

    G_OBJECT_CLASS (g3jamin_app_window_parent_class)->dispose (object);
}


GtkWidget *
g3jamin_app_window_new (G3JAMinApp *app)
{
    return g_object_new (G3JAMIN_APP_WINDOW_TYPE, "application", app, NULL);
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