/*
 * This file is part of AJAMI.
 *
 * Copyright (C) 2003 Steve Harris
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <ladspa.h>

#include "plugin.h"

static char *plugin_path;

void plugin_init()
{
    if (getenv("LADSPA_PATH")) {
        plugin_path = getenv("LADSPA_PATH");
    } else {
        plugin_path = "/usr/local/lib/ladspa:" LIBDIR "/ladspa";
    }
}

plugin *plugin_load(char *file)
{
    char *dir;
    char *path_tok;
    char path[512];
    void *dl;

    path_tok = strdup(plugin_path);
    for (dir = strtok(path_tok, ":"); dir; dir = strtok(NULL, ":")) {
        snprintf(path, 511, "%s/%s", dir, file);
        if ((dl = dlopen(path, RTLD_LAZY))) {
            plugin *ret = malloc(sizeof(plugin));
            LADSPA_Descriptor *(*d)(unsigned long);

            ret->dl = dl;
            d = dlsym(dl, "ladspa_descriptor");
            ret->descriptor = (*d)(0);

            return ret;
        }
    }
    fprintf(stderr, "Cannot find plugin '%s'\n", file);
    free(path_tok);

    return NULL;
}

LADSPA_Handle plugin_instantiate(plugin *p, unsigned long fs)
{
    if (p->descriptor->instantiate) {
        return (*p->descriptor->instantiate)(p->descriptor, fs);
    } else {
        fprintf(stderr, "Cannot find instantiate function for %s\n", p->descriptor->Label);
    }

    return NULL;
}
