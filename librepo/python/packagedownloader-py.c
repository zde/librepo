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

#include <Python.h>
#undef NDEBUG
#include <assert.h>

#include "librepo/librepo.h"

#include "packagedownloader-py.h"
#include "handle-py.h"
#include "packagetarget-py.h"
#include "exception-py.h"
#include "downloader-py.h"
#include "globalstate-py.h" // GIL Hack

PyObject *
py_download_packages(G_GNUC_UNUSED PyObject *self, PyObject *args)
{
    gboolean ret;
    PyObject *py_list;
    int failfast;
    LrPackageDownloadFlag flags = 0;
    GError *tmp_err = NULL;
    PyThreadState *state = NULL;

    if (!PyArg_ParseTuple(args, "O!i:download_packages",
                          &PyList_Type, &py_list, &failfast))
        return NULL;

    // Convert python list to GSList
    GSList *list = NULL;
    Py_ssize_t len = PyList_Size(py_list);
    for (Py_ssize_t x=0; x < len; x++) {
        PyObject *py_packagetarget = PyList_GetItem(py_list, x);
        LrPackageTarget *target = PackageTarget_FromPyObject(py_packagetarget);
        if (!target)
            return NULL;
        PackageTarget_SetThreadState(py_packagetarget, &state);
        list = g_slist_append(list, target);
    }

    Py_XINCREF(py_list);

    if (failfast)
        flags |= LR_PACKAGEDOWNLOAD_FAILFAST;

    // XXX: GIL Hack
    int hack_rc = gil_logger_hack_begin(&state);
    if (hack_rc == GIL_HACK_ERROR)
        return NULL;

    BeginAllowThreads(&state);
    ret = lr_download_packages(list, flags, &tmp_err);
    EndAllowThreads(&state);

    // XXX: GIL Hack
    if (!gil_logger_hack_end(hack_rc))
        return NULL;

    assert((ret && !tmp_err) || (!ret && tmp_err));

    if (!ret && tmp_err->code == LRE_INTERRUPTED) {
        Py_XDECREF(py_list);
        g_error_free(tmp_err);
        PyErr_SetInterrupt();
        PyErr_CheckSignals();
        return NULL;
    }

    Py_XDECREF(py_list);

    if (!ret)
        RETURN_ERROR(&tmp_err, -1, NULL);

    Py_RETURN_NONE;
}
