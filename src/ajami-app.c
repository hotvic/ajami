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


#include "config.h"

#include <locale.h>
#include <libintl.h>

#include <gtk/gtk.h>

#include "ajami-app.h"
#include "ajami-appwindow.h"

/* Forward declarations */
static void         ajami_app_class_init        (AjamiAppClass *klass);
static void         ajami_app_init              (AjamiApp      *app);
static void         ajami_app_dispose           (GObject         *object);
static void         ajami_app_startup           (GApplication    *application);
static void         ajami_app_shutdown          (GApplication    *app);
static void         ajami_app_activate          (GApplication    *application);
AjamiApp           *ajami_app_new               (void);
/* Actions */
static void         activate_global_bypass      (GSimpleAction   *action,
                                                 GVariant        *parameter,
                                                 gpointer         data);
static void         activate_preferences        (GSimpleAction   *action,
                                                 GVariant        *parameter,
                                                 gpointer         data);
static void         activate_help               (GSimpleAction   *action,
                                                 GVariant        *parameter,
                                                 gpointer         data);
static void         activate_about              (GSimpleAction   *action,
                                                 GVariant        *parameter,
                                                 gpointer         data);
static void         activate_quit               (GSimpleAction   *action,
                                                 GVariant        *parameter,
                                                 gpointer         data);
/* Callbacks */
/** Utility functions **/
static gboolean     ajami_app_has_app_menu    (AjamiApp *app);


struct _AjamiAppPrivate
{
    GMenuModel         *window_menu;
};

G_DEFINE_TYPE_WITH_PRIVATE (AjamiApp, ajami_app, GTK_TYPE_APPLICATION);


static void
ajami_app_class_init (AjamiAppClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

    object_class->dispose = ajami_app_dispose;

    app_class->startup = ajami_app_startup;
    app_class->activate = ajami_app_activate;
    app_class->shutdown = ajami_app_shutdown;
}

const GActionEntry app_entries[] = {
    { "global-bypass", activate_global_bypass },
    { "preferences",   activate_preferences   },
    { "help",          activate_help          },
    { "about",         activate_about         },
    { "quit",          activate_quit          }
};

static void
ajami_app_init (AjamiApp *app)
{
    app->priv = ajami_app_get_instance_private (app);

    g_set_application_name ("ajami");

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_entries,
                                     G_N_ELEMENTS (app_entries),
                                     app);
}

static void
ajami_app_dispose (GObject *object)
{
    AjamiApp *app = AJAMI_APP (object);

    G_OBJECT_CLASS (ajami_app_parent_class)->dispose (object);
}

static void
ajami_app_startup (GApplication *application)
{
    AjamiApp *app = AJAMI_APP (application);
    GError *error = NULL;
    GtkBuilder *builder;

    G_APPLICATION_CLASS (ajami_app_parent_class)->startup (application);

    /* Setup locale/gettext */
    setlocale (LC_ALL, "");

    /* load menu model */
    builder = gtk_builder_new_from_resource ("/org/ajami/ui/menus.ui");

    if (ajami_app_has_app_menu (app))
    {
        GMenuModel *appmenu;

        appmenu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
        gtk_application_set_app_menu (GTK_APPLICATION (application), appmenu);
    }

    app->priv->window_menu = G_MENU_MODEL (gtk_builder_get_object(builder, "menubar"));

    g_object_unref (builder);
}

static void
ajami_app_shutdown (GApplication *app)
{
    G_APPLICATION_CLASS (ajami_app_parent_class)->shutdown (app);
}

static void
ajami_app_activate (GApplication *application)
{
    GtkWidget *window = NULL;


    window = ajami_app_window_new (AJAMI_APP (application));
    gtk_widget_show_all (window);


    gtk_window_present (GTK_WINDOW (window));
}

AjamiApp *
ajami_app_new (void)
{
    return g_object_new (AJAMI_TYPE_APP,
                         "application-id", "org.hotvic.ajami",
                         NULL);
}

/* Actions */
static void
activate_global_bypass (GSimpleAction *action,
                        GVariant      *parameter,
                        gpointer       data)
{

}

static void
activate_preferences (GSimpleAction *action,
                      GVariant      *parameter,
                      gpointer       data)
{

}

static void
activate_help (GSimpleAction *action,
               GVariant      *parameter,
               gpointer       data)
{

}

static void
activate_about (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       data)
{

}

static void
activate_quit (GSimpleAction *action,
               GVariant      *parameter,
               gpointer       data)
{
    GList *windows, *scan;

    /* TODO: Check if opened file (if has one) has modified
             and ask to save */

    windows = gtk_application_get_windows (GTK_APPLICATION (data));

    for (scan = windows; scan; scan = scan->next) {
        gtk_widget_destroy (GTK_WIDGET (scan->data));
    }
}


/* Utility functions */
static gboolean
ajami_app_has_app_menu (AjamiApp *app)
{
    GtkSettings *gtk_settings;
    gboolean show_app_menu;
    gboolean show_menubar;

    /* We have three cases:
     * - GNOME 3: show-app-menu true, show-menubar false -> use the app menu
     * - Unity, OSX: show-app-menu and show-menubar true -> use the normal menu
     * - Other WM, Windows: show-app-menu and show-menubar false -> use the normal menu
     */
    gtk_settings = gtk_settings_get_default ();
    g_object_get (G_OBJECT (gtk_settings),
                  "gtk-shell-shows-app-menu", &show_app_menu,
                  "gtk-shell-shows-menubar", &show_menubar,
                  NULL);

    return show_app_menu && !show_menubar;
}