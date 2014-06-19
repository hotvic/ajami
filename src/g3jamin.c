/*
 *  Copyright (C) 2003 Jan C. Depner, Jack O'Quin, Steve Harris
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#include "config.h"

#ifdef HAVE_OSC
#include <lo/lo.h>
#include "constants.h"
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>

#include <gtk/gtk.h>

#include "g3jaminapp.h"
/*#include "main.h"
#include "resource.h"
#include "support.h"
#include "io.h"
#include "geq.h"
#include "hdeq.h"
#include "intrim.h"
#include "io-menu.h"
#include "process.h"
#include "spectrum.h"
#include "stereo.h"
#include "state.h"
#include "scenes.h"
#include "help.h"
#include "preferences.h"
#include "callbacks.h"*/


static gboolean     update_meters              (gpointer data);
static void         set_configuration_files    (void);

#ifdef HAVE_OSC
void                error                      (int          num,
                                                const char  *m,
                                                const char  *path);
int                 scene_handler              (const char  *path,
                                                const char  *types,
                                                lo_arg     **argv,
                                                int          argc,
                                                void        *data,
                                                void        *user_data);
#endif

int main(int argc, char *argv[])
{
    G3JAMinApp *app;
    int         status;


    //bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    //bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    //textdomain (GETTEXT_PACKAGE);


    app = g3jamin_app_new ();

    status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);

    return status;
}