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


#include <config.h>
#include <locale.h>
#include <libintl.h>

#include <gtk/gtk.h>

#include "g3jaminapp.h"
#include "g3jaminappwindow.h"

/* Forward declarations */
static void         g3jamin_app_class_init      (G3JAMinAppClass *klass);
static void         g3jamin_app_init            (G3JAMinApp *app);
static void         g3jamin_app_dispose         (GObject *object);
static void         g3jamin_app_startup         (GApplication *application);
static void         g3jamin_app_shutdown        (GApplication *app);
static void         g3jamin_app_activate        (GApplication *application);
G3JAMinApp         *g3jamin_app_new             (void);
/** Utility functions **/
static gboolean     g3jamin_app_has_app_menu    (G3JAMinApp *app);


struct _G3JAMinAppPrivate
{
    GMenuModel         *window_menu;
};

G_DEFINE_TYPE_WITH_PRIVATE (G3JAMinApp, g3jamin_app, GTK_TYPE_APPLICATION);


static void
g3jamin_app_class_init (G3JAMinAppClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

    object_class->dispose = g3jamin_app_dispose;

    app_class->startup = g3jamin_app_startup;
    app_class->activate = g3jamin_app_activate;
    app_class->shutdown = g3jamin_app_shutdown;
}

static void
g3jamin_app_init (G3JAMinApp *app)
{
    app->priv = g3jamin_app_get_instance_private (app);

    g_set_application_name ("g3jamin");
}

static void
g3jamin_app_dispose (GObject *object)
{
    G3JAMinApp *app = G3JAMIN_APP (object);

    G_OBJECT_CLASS (g3jamin_app_parent_class)->dispose (object);
}

static void
g3jamin_app_startup (GApplication *application)
{
    G3JAMinApp *app = G3JAMIN_APP (application);
    GError *error = NULL;
    GtkBuilder *builder;

    G_APPLICATION_CLASS (g3jamin_app_parent_class)->startup (application);

    /* Setup locale/gettext */
    setlocale (LC_ALL, "");

    /* load menu model */
    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_resource (builder,
                                        "/org/g3jamin/ui/menus.ui",
                                        &error))
    {
        g_warning ("loading menu builder file: %s", error->message);
        g_error_free (error);
    } else {
        if (g3jamin_app_has_app_menu (app)) {
            GMenuModel *appmenu;

            appmenu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
            gtk_application_set_app_menu (GTK_APPLICATION (application), appmenu);
        }
    }
    app->priv->window_menu = G_MENU_MODEL (gtk_builder_get_object(builder, "menubar"));

    g_object_unref (builder);
}

static void
g3jamin_app_shutdown (GApplication *app)
{
    G_APPLICATION_CLASS (g3jamin_app_parent_class)->shutdown (app);
}

static void
g3jamin_app_activate (GApplication *application)
{
    GtkWidget *window = NULL;


    window = g3jamin_app_window_new (G3JAMIN_APP (application));
    gtk_widget_show_all(window);


    gtk_window_present (GTK_WINDOW (window));
}

G3JAMinApp *
g3jamin_app_new (void)
{
    return g_object_new (G3JAMIN_TYPE_APP,
                         "application-id", "org.hotvic.g3jamin",
                         NULL);
}

static gboolean
g3jamin_app_has_app_menu (G3JAMinApp *app)
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