import unittest
import librepo

def foo_cb(data, total_to_download, downloaded):
    pass

class TestCaseHandle(unittest.TestCase):
    def test_handle_setopt_getinfo(self):
        """No exception should be raised."""
        h = librepo.Handle()

        self.assertFalse(h.getinfo(librepo.LRI_UPDATE))
        h.setopt(librepo.LRO_UPDATE,  True)
        self.assertTrue(h.getinfo(librepo.LRI_UPDATE))
        h.setopt(librepo.LRO_UPDATE,  False)
        self.assertFalse(h.getinfo(librepo.LRI_UPDATE))
        h.setopt(librepo.LRO_UPDATE,  1)
        self.assertTrue(h.getinfo(librepo.LRI_UPDATE))
        h.setopt(librepo.LRO_UPDATE,  0)
        self.assertFalse(h.getinfo(librepo.LRI_UPDATE))

        self.assertEqual(h.getinfo(librepo.LRI_URLS), [])
        h.setopt(librepo.LRO_URLS, ["http://foo"])
        self.assertEqual(h.getinfo(librepo.LRI_URLS), ["http://foo"])
        h.setopt(librepo.LRO_URLS, [""])
        self.assertEqual(h.getinfo(librepo.LRI_URLS), [""])
        h.setopt(librepo.LRO_URLS, None)
        self.assertEqual(h.getinfo(librepo.LRI_URLS), [])

        self.assertEqual(h.getinfo(librepo.LRI_MIRRORLIST), None)
        h.setopt(librepo.LRO_MIRRORLIST, "http://ml")
        self.assertEqual(h.getinfo(librepo.LRI_MIRRORLIST), "http://ml")
        h.setopt(librepo.LRO_MIRRORLIST, "")
        self.assertEqual(h.getinfo(librepo.LRI_MIRRORLIST), "")
        h.setopt(librepo.LRO_MIRRORLIST, None)
        self.assertEqual(h.getinfo(librepo.LRI_MIRRORLIST), None)

        self.assertFalse(h.getinfo(librepo.LRI_LOCAL))
        h.setopt(librepo.LRO_LOCAL,  1)
        self.assertTrue(h.getinfo(librepo.LRI_LOCAL))
        h.setopt(librepo.LRO_LOCAL,  0)
        self.assertFalse(h.getinfo(librepo.LRI_LOCAL))

        self.assertFalse(h.getinfo(librepo.LRI_PROGRESSCB))
        h.setopt(librepo.LRO_PROGRESSCB, foo_cb)
        self.assertEqual(h.getinfo(librepo.LRI_PROGRESSCB), foo_cb)
        h.setopt(librepo.LRO_PROGRESSCB, None)
        self.assertFalse(h.getinfo(librepo.LRI_PROGRESSCB))

        data = {'a':'foo'}

        self.assertFalse(h.getinfo(librepo.LRI_PROGRESSDATA))
        h.setopt(librepo.LRO_PROGRESSDATA, data)
        self.assertEqual(h.getinfo(librepo.LRI_PROGRESSDATA), data)
        h.setopt(librepo.LRO_PROGRESSDATA, None)
        self.assertFalse(h.getinfo(librepo.LRI_PROGRESSDATA))

        self.assertEqual(h.getinfo(librepo.LRI_DESTDIR), None)
        h.setopt(librepo.LRO_DESTDIR,  "foodir")
        self.assertEqual(h.getinfo(librepo.LRI_DESTDIR), "foodir")
        h.setopt(librepo.LRO_DESTDIR,  None)
        self.assertEqual(h.getinfo(librepo.LRI_DESTDIR), None)
        h.setopt(librepo.LRO_DESTDIR,  "")
        self.assertEqual(h.getinfo(librepo.LRI_DESTDIR), "")

        self.assertEqual(h.getinfo(librepo.LRI_USERAGENT), None)
        h.setopt(librepo.LRO_USERAGENT,  "librepo/0.0")
        self.assertEqual(h.getinfo(librepo.LRI_USERAGENT), "librepo/0.0")
        h.setopt(librepo.LRO_USERAGENT,  None)
        self.assertEqual(h.getinfo(librepo.LRI_USERAGENT), None)
        h.setopt(librepo.LRO_USERAGENT,  "")
        self.assertEqual(h.getinfo(librepo.LRI_USERAGENT), "")

        self.assertEqual(h.getinfo(librepo.LRI_YUMDLIST), None)
        h.setopt(librepo.LRO_YUMDLIST,  ["primary", "other"])
        self.assertEqual(h.getinfo(librepo.LRI_YUMDLIST), ["primary", "other"])
        h.setopt(librepo.LRO_YUMDLIST,  [])
        self.assertEqual(h.getinfo(librepo.LRI_YUMDLIST), [])
        h.setopt(librepo.LRO_YUMDLIST,  [None])
        self.assertEqual(h.getinfo(librepo.LRI_YUMDLIST), [])
        h.setopt(librepo.LRO_YUMDLIST,  None)
        self.assertEqual(h.getinfo(librepo.LRI_YUMDLIST), None)

        self.assertEqual(h.getinfo(librepo.LRI_YUMBLIST), None)
        h.setopt(librepo.LRO_YUMBLIST,  ["primary", "other"])
        self.assertEqual(h.getinfo(librepo.LRI_YUMBLIST), ["primary", "other"])
        h.setopt(librepo.LRO_YUMBLIST,  [])
        self.assertEqual(h.getinfo(librepo.LRI_YUMBLIST), [])
        h.setopt(librepo.LRO_YUMBLIST,  [None])
        self.assertEqual(h.getinfo(librepo.LRI_YUMBLIST), [])

        self.assertEqual(h.getinfo(librepo.LRI_MAXMIRRORTRIES), 0)
        h.setopt(librepo.LRO_MAXMIRRORTRIES, 1)
        self.assertEqual(h.getinfo(librepo.LRI_MAXMIRRORTRIES), 1)
        h.setopt(librepo.LRO_MAXMIRRORTRIES, None)
        self.assertEqual(h.getinfo(librepo.LRI_MAXMIRRORTRIES), 0)

        self.assertEqual(h.getinfo(librepo.LRI_VARSUB), None)
        h.setopt(librepo.LRO_VARSUB, [("bar", "foo")])
        self.assertEqual(h.getinfo(librepo.LRI_VARSUB), [("bar", "foo")])
        h.setopt(librepo.LRO_VARSUB, None)
        self.assertEqual(h.getinfo(librepo.LRI_VARSUB), None)

        self.assertEqual(h.getinfo(librepo.LRI_FASTESTMIRROR), False)
        h.setopt(librepo.LRO_FASTESTMIRROR, True)
        self.assertEqual(h.getinfo(librepo.LRI_FASTESTMIRROR), True)
        h.setopt(librepo.LRO_FASTESTMIRROR, False)
        self.assertEqual(h.getinfo(librepo.LRI_FASTESTMIRROR), False)

    def test_handle_setget_attr(self):
        """No exception should be raised."""
        h = librepo.Handle()

        self.assertFalse(h.update)
        h.update = True
        self.assertTrue(h.update)
        h.update = False
        self.assertFalse(h.update)
        h.update = 1
        self.assertTrue(h.update)
        h.update = 0
        self.assertFalse(h.update)

        self.assertEqual(h.urls, [])
        h.urls = "http://foo"
        self.assertEqual(h.urls, ["http://foo"])
        h.urls = ""
        self.assertEqual(h.urls, [""])
        h.urls = None
        self.assertEqual(h.urls, [])

        self.assertEqual(h.mirrorlist, None)
        h.mirrorlist = "http://ml"
        self.assertEqual(h.mirrorlist, "http://ml")
        h.mirrorlist = ""
        self.assertEqual(h.mirrorlist, "")
        h.mirrorlist = None
        self.assertEqual(h.mirrorlist, None)

        self.assertFalse(h.local)
        h.local =  1
        self.assertTrue(h.local)
        h.local =  0
        self.assertFalse(h.local)

        self.assertFalse(h.progresscb)
        h.progresscb = foo_cb
        self.assertEqual(h.progresscb, foo_cb)
        h.progresscb = None
        self.assertFalse(h.progresscb)

        data = {'a':'foo'}

        self.assertFalse(h.progressdata)
        h.progressdata = data
        self.assertEqual(h.progressdata, data)
        h.progressdata = None
        self.assertFalse(h.progressdata)

        self.assertEqual(h.destdir, None)
        h.destdir =  "foodir"
        self.assertEqual(h.destdir, "foodir")
        h.destdir =  None
        self.assertEqual(h.destdir, None)
        h.destdir =  ""
        self.assertEqual(h.destdir, "")

        self.assertEqual(h.useragent, None)
        h.useragent =  "librepo/0.0"
        self.assertEqual(h.useragent, "librepo/0.0")
        h.useragent =  None
        self.assertEqual(h.useragent, None)
        h.useragent =  ""
        self.assertEqual(h.useragent, "")

        self.assertEqual(h.yumdlist, None)
        h.yumdlist =  ["primary", "other"]
        self.assertEqual(h.yumdlist, ["primary", "other"])
        h.yumdlist =  []
        self.assertEqual(h.yumdlist, [])
        h.yumdlist =  [None]
        self.assertEqual(h.yumdlist, [])

        self.assertEqual(h.yumblist, None)
        h.yumblist =  ["primary", "other"]
        self.assertEqual(h.yumblist, ["primary", "other"])
        h.yumblist =  []
        self.assertEqual(h.yumblist, [])
        h.yumblist =  [None]
        self.assertEqual(h.yumblist, [])

        self.assertEqual(h.maxmirrortries, 0)
        h.maxmirrortries = 1
        self.assertEqual(h.maxmirrortries, 1)
        h.maxmirrortries = None
        self.assertEqual(h.maxmirrortries, 0)

        self.assertEqual(h.varsub, None)
        h.varsub = [("foo", "bar")]
        self.assertEqual(h.varsub, [("foo", "bar")])
        h.varsub = None
        self.assertEqual(h.varsub, None)

        self.assertEqual(h.fastestmirror, False)
        h.fastestmirror = True
        self.assertEqual(h.fastestmirror, True)
        h.fastestmirror = False
        self.assertEqual(h.fastestmirror, False)

    def test_handle_setopt_none_value(self):
        """Using None in setopt."""
        h = librepo.Handle()

        h.setopt(librepo.LRO_LOCAL, None)
        h.local = None
        h.setopt(librepo.LRO_HTTPAUTH, None)
        h.httpauth = None
        h.setopt(librepo.LRO_USERPWD, None)
        h.userpwd = None
        h.setopt(librepo.LRO_PROXY, None)
        h.proxy = None
        h.setopt(librepo.LRO_PROXYPORT, None)       # None sets default value
        h.proxyport = None
        h.setopt(librepo.LRO_PROXYTYPE, None)
        h.proxytype = None
        h.setopt(librepo.LRO_PROXYAUTH, None)
        h.proxyauth = None
        h.setopt(librepo.LRO_PROXYUSERPWD, None)
        h.proxyuserpwd = None
        h.setopt(librepo.LRO_PROGRESSDATA, None)
        h.progressdata = None
        h.setopt(librepo.LRO_MAXSPEED, None)        # None sets default value
        h.maxspeed = None
        h.setopt(librepo.LRO_CONNECTTIMEOUT, None)  # None sets default value
        h.connecttimeout = None
        h.setopt(librepo.LRO_IGNOREMISSING, None)
        h.ignoremissing = None
        h.setopt(librepo.LRO_INTERRUPTIBLE, None)
        h.interruptible = None
        h.setopt(librepo.LRO_USERAGENT, None)
        h.useragent = None
        h.setopt(librepo.LRO_FETCHMIRRORS, None)
        h.fetchmirrors = None
        h.setopt(librepo.LRO_MAXMIRRORTRIES, None)
        h.maxmirrortries = None
        h.setopt(librepo.LRO_VARSUB, None)
        h.varsub = None
        h.setopt(librepo.LRO_FASTESTMIRROR, None)
        h.fastestmirror = None
        h.setopt(librepo.LRO_FASTESTMIRRORCACHE, None)
        h.fastestmirrorcache = None
        h.setopt(librepo.LRO_FASTESTMIRRORMAXAGE, None)
        h.fastestmirrormaxage = None
        h.setopt(librepo.LRO_FASTESTMIRRORDATA, None)
        h.fastestmirrordata = None
        h.setopt(librepo.LRO_LOWSPEEDTIME, None)
        h.lowspeedtime = None
        h.setopt(librepo.LRO_LOWSPEEDLIMIT, None)
        h.lowspeedlimit = None
        h.setopt(librepo.LRO_GPGCHECK, None)
        h.gpgcheck = None
        h.setopt(librepo.LRO_CHECKSUM, None)
        h.checksum = None
        h.setopt(librepo.LRO_LOWSPEEDTIME, None)
        h.lowspeedtime = None
        h.setopt(librepo.LRO_LOWSPEEDLIMIT, None)
        h.lowspeedlimit = None

        def callback(data, total_to_download, downloaded):
            pass
        h.setopt(librepo.LRO_PROGRESSCB, None)
        h.progresscb = None
        h.setopt(librepo.LRO_PROGRESSCB, callback)
        h.progresscb = callback
        h.setopt(librepo.LRO_PROGRESSCB, None)
        h.progresscb = None

        def fmcallback(userdata, stage, data):
            pass
        h.setopt(librepo.LRO_FASTESTMIRRORCB, None)
        h.fastestmirrorcb = None
        h.setopt(librepo.LRO_FASTESTMIRRORCB, fmcallback)
        h.fastestmirrorcb = fmcallback
        h.setopt(librepo.LRO_FASTESTMIRRORCB, None)
        h.fastestmirror = None

