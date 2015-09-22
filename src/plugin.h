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


#ifndef PLUGIN_H
#define PLUGIN_H

#include "ladspa.h"

typedef struct {
    void *dl;
    LADSPA_Descriptor *descriptor;
} plugin;


void                plugin_init         (void);
plugin             *plugin_load         (char          *file);
LADSPA_Handle       plugin_instantiate  (plugin        *p,
                                         unsigned long  fs);
static inline void  plugin_connect_port (plugin        *p,
                                         LADSPA_Handle  handle,
                                         unsigned long  port,
                                         LADSPA_Data   *data)
{
    (*p->descriptor->connect_port)(handle, port, data);
}

static inline void  plugin_run           (plugin        *p,
                                         LADSPA_Handle *handle,
                                         unsigned long  sample_count)
{
    (*p->descriptor->run)(handle, sample_count);
}


#endif
