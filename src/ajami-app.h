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

#define AJAMI_TYPE_APP              (ajami_app_get_type())
#define AJAMI_APP(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj),  AJAMI_TYPE_APP, AjamiApp))
#define AJAMI_IS_APP(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj),  AJAMI_TYPE_APP))
#define AJAMI_APP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),   AJAMI_TYPE_APP, AjamiAppClass))
#define AJAMI_IS_APP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass),  AJAMI_TYPE_APP))
#define AJAMI_APP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),   AJAMI_TYPE_APP, AjamiAppClass))


typedef struct _AjamiApp        AjamiApp;
typedef struct _AjamiAppClass   AjamiAppClass;
typedef struct _AjamiAppPrivate AjamiAppPrivate;

struct _AjamiApp
{
  GtkApplication parent;

  /*< private > */
  AjamiAppPrivate *priv;
};

struct _AjamiAppClass
{
  GtkApplicationClass parent_class;
};


/* Public methods */
GType          ajami_app_get_type          (void);

AjamiApp      *ajami_app_new               (void);


G_END_DECLS

#endif  /* __AJAMI_APP_H__  */