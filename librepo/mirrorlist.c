/* librepo - A library providing (libcURL like) API to downloading repository
 * Copyright (C) 2012  Tomas Mlcoch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#define _POSIX_SOURCE

#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "rcodes.h"
#include "util.h"
#include "mirrorlist.h"

#define BUF_LEN 4096

LrMirrorlist *
lr_mirrorlist_init()
{
    return lr_malloc0(sizeof(LrMirrorlist));
}

void
lr_mirrorlist_free(LrMirrorlist *mirrorlist)
{
    if (!mirrorlist)
        return;

    g_slist_free_full(mirrorlist->urls, (GDestroyNotify)lr_free);
    lr_free(mirrorlist);
}

gboolean
lr_mirrorlist_parse_file(LrMirrorlist *mirrorlist, int fd, GError **err)
{
    FILE *f;
    int fd_dup;
    char buf[BUF_LEN], *p;

    assert(mirrorlist);
    assert(fd >= 0);
    assert(!err || *err == NULL);


    fd_dup = dup(fd);
    if (fd_dup == -1) {
        g_set_error(err, LR_MIRRORLIST_ERROR, LRE_IO,
                    "dup(%d) error: %s", fd, strerror(errno));
        return FALSE;
    }

    f = fdopen(fd_dup, "r");
    if (!f) {
        g_debug("%s: Cannot fdopen(mirrorlist_fd): %s", __func__, strerror(errno));
        g_set_error(err, LR_MIRRORLIST_ERROR, LRE_IO,
                    "fdopen(%d, \"r\") error: %s", fd_dup, strerror(errno));
        return FALSE;
    }

    while ((p = fgets(buf, BUF_LEN, f))) {
        int l;

        /* Skip leading white characters */
        while (*p == ' ' || *p == '\t')
            p++;

        if (!*p || *p == '#')
            continue;  /* End of string or comment */

        l = strlen(p);
        /* Remove trailing white characters */
        while (l > 0 && (p[l-1] == ' ' || p[l-1] == '\n' || p[l-1] == '\t'))
            l--;
        p[l] = '\0';

        if (!l)
            continue;

        /* Append URL */
        if (p[0] != '\0' && (strstr(p, "://") || p[0] == '/'))
            mirrorlist->urls = g_slist_append(mirrorlist->urls, g_strdup(p));
    }

    fclose(f);

    return TRUE;
}
