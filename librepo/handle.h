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

#ifndef LR_HANDLE_H
#define LR_HANDLE_H

#include <glib.h>

#include "result.h"

G_BEGIN_DECLS

/** \defgroup   handle    Librepo Handle
 *  \addtogroup handle
 *  @{
 */

/** Handle object containing configration for repository metadata and
 * package downloading.
 */
typedef struct _LrHandle LrHandle;

/** LRO_FASTESTMIRRORMAXAGE default value */
#define LRO_FASTESTMIRRORMAXAGE_DEFAULT     2592000 // 30 days

/** LRO_FASTESTMIRRORMAXAGE minimal allowed value */
#define LRO_FASTESTMIRRORMAXAGE_MIN         0

/** LRO_PROXYPORT default value */
#define LRO_PROXYPORT_DEFAULT               1080

/** LRO_PROXYTYPE default value */
#define LRO_PROXYTYPE_DEFAULT               LR_PROXY_HTTP

/** LRO_MAXSPEED default value (0 == unlimited speed) */
#define LRO_MAXSPEED_DEFAULT                0

/** LRO_CONNECTTIMEOUT default value */
#define LRO_CONNECTTIMEOUT_DEFAULT          30

/** LRO_MAXMIRRORTRIES default value */
#define LRO_MAXMIRRORTRIES_DEFAULT          0

/** LRO_MAXMIRRORTRIES minimal allowed value */
#define LRO_MAXMIRRORTRIES_MIN              0

/** LRO_MAXPARALLELDOWNLOADS default value */
#define LRO_MAXPARALLELDOWNLOADS_DEFAULT    3

/** LRO_MAXPARALLELDOWNLOADS minimal allowed value */
#define LRO_MAXPARALLELDOWNLOADS_MIN        1

/** LRO_MAXPARALLELDOWNLOADS maximal allowed value */
#define LRO_MAXPARALLELDOWNLOADS_MAX        20

/** LRO_MAXDOWNLOADSPERMIRROR default value */
#define LRO_MAXDOWNLOADSPERMIRROR_DEFAULT   2

/** LRO_MAXDOWNLOADSPERMIRROR minimal allowed value */
#define LRO_MAXDOWNLOADSPERMIRROR_MIN       1

/** LRO_LOWSPEEDTIME minimal allowed value */
#define LRO_LOWSPEEDTIME_MIN                0

/** LRO_LOWSPEEDTIME default value */
#define LRO_LOWSPEEDTIME_DEFAULT            10

/** LRO_LOWSPEEDLIMIT minimal allowed value */
#define LRO_LOWSPEEDLIMIT_MIN               0

/** LRO_LOWSPEEDLIMIT default value */
#define LRO_LOWSPEEDLIMIT_DEFAULT           1000

/** Handle options for the ::lr_handle_setopt function. */
typedef enum {

    LRO_UPDATE,  /*!< (long 1 or 0)
        Update existing repo in ::LrResult. Update means download missing
        (previously omitted) metadata file(s). */

    LRO_URLS,  /*!< (char ** NULL-terminated)
        List of base repo URLs */

    LRO_MIRRORLIST,  /*!< (char *)
        Mirrorlist or metalink url. This option is DEPRECATED */

    LRO_MIRRORLISTURL, /*!< (char *)
        Mirrorlist url */

    LRO_METALINKURL, /*!< (char *)
        Metalink url */

    LRO_LOCAL,  /*!< (long 1 or 0)
        Do not duplicate local metadata, just locate the old one */

    LRO_HTTPAUTH,  /*!< (long 1 or 0)
        Enable all supported method of HTTP authentification. */

    LRO_USERPWD,  /*!< (char *)
        User and password for http authetification in format user:password */

    LRO_PROXY,  /*!< (char *)
        Address of proxy server eg. "proxy-host.com:8080" */

    LRO_PROXYPORT,  /*!< (long)
        Set port number for proxy separately. Default port is 1080. */

    LRO_PROXYTYPE,  /*!< (LrProxyType)
        Type of the proxy used. */

    LRO_PROXYAUTH,  /*!< (long 1 or 0)
        Enable all supported method for proxy authentification */

    LRO_PROXYUSERPWD,  /*!< (char *)
        User and password for proxy in format user:password */

    LRO_PROGRESSCB,  /*!< (LrProgressCb)
        Progress callback */

    LRO_PROGRESSDATA,  /*!< (void *)
        Progress callback user data */

    LRO_MAXSPEED,  /*!< (gint64)
        Maximum download speed in bytes per second. Default is 0 = unlimited
        download speed. */

    LRO_DESTDIR,  /*!< (char *)
        Where to save downloaded files */

    LRO_REPOTYPE,  /*!< (LrRepotype)
        Type of downloaded repo, currently only supported is LR_YUMREPO. */

    LRO_CONNECTTIMEOUT,  /*!< (long)
        Max time in sec for connection phase. default timeout
        is 300 seconds. */

    LRO_IGNOREMISSING,  /*!< (long 1 or 0)
        If you want to localise (LRO_LOCAL is enabled) a incomplete local
        repository (eg. only primary and filelists are present) you could
        use LRO_YUMDLIST and specify only file that are present, or use this
        option. */

    LRO_INTERRUPTIBLE,  /*!< (long 1 or 0)
        If true, Librepo setups its own signal handler for SIGTERM and stops
        downloading if SIGTERM is catched. In this case current operation
        could return any kind of error code. Handle which operation was
        interrupted shoud never be used again! */

    LRO_USERAGENT,  /*!< (char *)
        String for  User-Agent: header in the http request sent to
        the remote server */

    LRO_FETCHMIRRORS,  /*!< (long 1 or 0)
        If true - do not download anything, except mirrorlist or metalink
        (during lr_handle_perform()).*/

    LRO_MAXMIRRORTRIES,  /*!< (long)
        If download fails try at most the specified number of mirrors.
        0 means try all available mirrors. */

    LRO_MAXPARALLELDOWNLOADS,  /*!< (long)
        Maximum number of parallel downloads. */

    LRO_MAXDOWNLOADSPERMIRROR,  /*!< (long)
        Maximum number of parallel downloads per mirror. */

    LRO_VARSUB,  /*!< (LrUrlVars *)
        Variables and its substitutions for repo URL.
        [{"releasever", "f18"}], ...;
        (e.g.: http://foo/$releasever => http://foo/f18)
        LrUrlVars has to be constructed by the ::lr_urlvars_set() function.
        After set the list to the handle, it has not to be freed! Handle
        itself takes care about freeing the list. */

    LRO_FASTESTMIRROR, /*!< (long 1 or 0)
        Sort the internal mirrorlist, after it is constructed, by the
        determined connection speed.
        Disabled by default. */

    LRO_FASTESTMIRRORCACHE, /*!< (char *)
        Path to the fastestmirror's cache file.
        Used when LRO_FASTESTMIRROR is enabled.
        If it doesn't exists, it will be created. */

    LRO_FASTESTMIRRORMAXAGE, /*< (long)
        Maximum age of a record in cache (seconds).
        Default: 2592000 (30 days). */

    LRO_FASTESTMIRRORCB, /* (LrFastestMirrorCb)
        Fastest mirror status callback */

    LRO_FASTESTMIRRORDATA, /* (void *)
        User data for LRO_FASTESTMIRRORCB */

    LRO_LOWSPEEDTIME, /*< (long)
        The time in seconds that the transfer should be below the
        LRO_LOWSPEEDLIMIT for the library to consider it too slow
        and abort. */

    LRO_LOWSPEEDLIMIT, /*< (long)
        The transfer speed in bytes per second that the transfer
        should be below during LRO_LOWSPEEDTIME seconds for
        the library to consider it too slow and abort. */

    /* Repo common options */

    LRO_GPGCHECK,   /*!< (long 1 or 0)
        Check GPG signature if available */

    LRO_CHECKSUM,  /*!< (long 1 or 0)
        Check files checksum if available */

    /* LR_YUMREPO specific options */

    LRO_YUMDLIST,  /*!< (char ** NULL-terminated)
        Download only specified records from repomd (e.g. ["primary",
        "filelists", NULL]).
        Note: Last element of the list must be NULL! */

    LRO_YUMBLIST,  /*!< (char ** NULL-terminated)
        Do not download this specified records from repomd (blacklist).
        Note: Last element of the list must be NULL! */

    LRO_SENTINEL,    /*!< Sentinel */

} LrHandleOption; /*!< Handle config options */

/** Handle options for the ::lr_handle_getinfo function. */
typedef enum {
    LRI_UPDATE,                 /*!< (long *) */
    LRI_URLS,                   /*!< (char ***)
        NOTE: Returned list must be freed as well as all its items!
        You could use g_strfreev() function. */
    LRI_MIRRORLIST,             /*!< (char **) */
    LRI_MIRRORLISTURL,          /*!< (char **) */
    LRI_METALINKURL,            /*!< (char **) */
    LRI_LOCAL,                  /*!< (long *) */
    LRI_PROGRESSCB,             /*!< (void *) */
    LRI_PROGRESSDATA,           /*!< (LrProgressCb) */
    LRI_DESTDIR,                /*!< (char **) */
    LRI_REPOTYPE,               /*!< (long *) */
    LRI_USERAGENT,              /*!< (char **) */
    LRI_YUMDLIST,               /*!< (char ***)
        NOTE: Returned list must be freed as well as all its items!
        You could use g_strfreev() function. */
    LRI_YUMBLIST,               /*!< (char ***)
        NOTE: Returned list must be freed as well as all its items!
        You could use g_strfreev() function. */
    LRI_FETCHMIRRORS,           /*!< (long *) */
    LRI_MAXMIRRORTRIES,         /*!< (long *) */
    LRI_VARSUB,                 /*!< (LrUrlVars **) */
    LRI_MIRRORS,                /*!< (char ***)
        Mirrorlist associated with the repository.

        If LRO_MIRRORLIST was specified, then content of this list is
        created from the specified mirrorlist.
        If no LRO_MIRRORLIST was specified and repository is on a local
        filesystem and contains a mirrorlist then the mirrorlist is
        automatically loaded.

        Mirrors from this list are used for downloading only if the
        mirrorlist was specified by LRO_MIRRORLIST option! Automatically
        loaded mirrorlist from a local repository is not implicitly
        used for downloading!

        NOTE: Returned list must be freed as well as all its items!
        You could use g_strfreev() function. */
    LRI_METALINK,               /*!< (LrMetalink *) */
    LRI_FASTESTMIRROR,          /*!< (long *) */
    LRI_FASTESTMIRRORCACHE,     /*!< (char **) */
    LRI_FASTESTMIRRORMAXAGE,    /*!< (long *) */
    LRI_SENTINEL,
} LrHandleInfoOption; /*!< Handle info options */

/** Return new handle.
 * @return              New allocated handle.
 */
LrHandle *
lr_handle_init();

/** Frees handle and its content.
 * @param handle        Handle.
 */
void
lr_handle_free(LrHandle *handle);

/** Set option (::LrHandleOption) of the handle.
 * @param handle        Handle.
 * @param err           GError **
 * @param option        Option from ::LrHandleOption enum.
 * @param ...           Value for the option.
 * @return              TRUE if everything is ok, FALSE if err is set.
 */
gboolean
lr_handle_setopt(LrHandle *handle,
                 GError **err,
                 LrHandleOption option,
                 ...);

/** Get information from handle.
 * Most of returned pointers point directly to the handle internal
 * values and therefore you should assume that they are only valid until
 * any manipulation (lr_handle_setopt, lr_handle_perform, ...)
 * with handle occurs.
 * NOTE: You should not free or modify the memory returned by this
 * function unless it is explicitly mentioned!
 * @param handle        Librepo handle.
 * @param err           GError **
 * @param option        Option from ::LrHandleInfoOption enum.
 * @param ...           Apropriate variable fro the selected option.
 * @return              TRUE if everything is ok, FALSE if err is set.
 */
gboolean
lr_handle_getinfo(LrHandle *handle,
                  GError **err,
                  LrHandleInfoOption option,
                  ...);

/** Perform repodata download or location.
 * @param handle        Librepo handle.
 * @param result        Librepo result.
 * @param err           GError **
 * @return              TRUE if everything is ok, FALSE if err is set.
 */
gboolean
lr_handle_perform(LrHandle *handle, LrResult *result, GError **err);

/** @} */

G_END_DECLS

#endif
