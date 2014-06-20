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


#ifndef __AJAMI_APP_H__
#define __AJAMI_APP_H__

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>


G_BEGIN_DECLS

#define G3JAMIN_TYPE_APP              (g3jamin_app_get_type())
#define G3JAMIN_APP(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj),  G3JAMIN_TYPE_APP, G3JAMinApp))
#define G3JAMIN_APP_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST ((obj), G3JAMIN_TYPE_APP, G3JAMinSettings const))
#define G3JAMIN_APP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),   G3JAMIN_TYPE_APP, G3JAMinAppClass))
#define G3JAMIN_IS_APP(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj),  G3JAMIN_TYPE_APP))
#define G3JAMIN_IS_APP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass),  G3JAMIN_TYPE_APP))
#define G3JAMIN_APP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),   G3JAMIN_TYPE_APP, G3JAMinAppClass))

typedef struct _G3JAMinApp        G3JAMinApp;
typedef struct _G3JAMinAppClass   G3JAMinAppClass;
typedef struct _G3JAMinAppPrivate G3JAMinAppPrivate;

struct _G3JAMinApp
{
  GtkApplication parent;

  /*< private > */
  G3JAMinAppPrivate *priv;
};

struct _G3JAMinAppClass
{
  GtkApplicationClass parent_class;

  gboolean (*show_help)                    (G3JAMinApp   *app,
                                            GtkWindow    *parent,
                                            const gchar  *name,
                                            const gchar  *link_id);

  gchar *(*help_link_id)                   (G3JAMinApp   *app,
                                            const gchar  *name,
                                            const gchar  *link_id);
};


/* Public methods */
GType          g3jamin_app_get_type          (void) G_GNUC_CONST;

G3JAMinApp    *g3jamin_app_new               (void);


G_END_DECLS

#endif  /* __AJAMI_APP_H__  */