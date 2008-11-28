
#include "test_url.h"
#include <QtTest/QtTest>
#include <QtDebug>

#include "medialib.h"

#include "compat_p.h"

#if HAVE_CBINDINGS
#if HAVE_XMMSV
#include <xmmsc/xmmsc_value.h>
#else
#include <xmmsclient/xmmsclient.h>
#endif
extern "C" char *_xmmsc_medialib_encode_url (const char *url, int narg,
                                             const char **args);
#endif


using namespace XMMSQt;

// Helper functions for url encoding/decoding tests

// This string should contains Characters that should not be encoded
static const QString dontEncode = "azAZ0123456789:/-._";

inline void
setTestUrls ()
{
	QTest::addColumn<QString>("testurl");

	QTest::newRow ("No encoding necessary") << "file:///Test.ext";
	QTest::newRow ("Whitespaces") << "file:///Test Name.ext";
	QTest::newRow ("Ascii special characters") << "file:///!$\%&/()=?\\.~<>";
	// Those seem to be encoded in unicode....
	QTest::newRow ("Latin1 characters ") << ("ÀÁÂÃÄÅÆàáâãäåæß.€¥");
	QTest::newRow ("Japanese characters") << QString::fromWCharArray (L"漢字とひらがなとカタカナ");
}

#ifdef HAVE_CBINDINGS
inline QString
cDecodeUrl (const QString &url)
{
	QByteArray p_enc = url.toUtf8 ();
	QString ret;
#if HAVE_XMMSV
	xmmsv_t *v_enc = xmmsv_new_string (p_enc.constData ());
	xmmsv_t *p_dec = xmmsv_decode_url (v_enc);
	xmmsv_unref (v_enc);
	const char *p;
	unsigned int p_len;
	xmmsv_get_bin (p_dec, reinterpret_cast<const unsigned char **>(&p), &p_len);
	ret = QString::fromUtf8 (p, p_len);
	xmmsv_unref (p_dec);
#else
	char *p_dec = const_cast<char *> (xmmsc_result_decode_url (NULL, p_enc.constData ()));
	ret = QString::fromUtf8 (p_dec);
	free (p_dec);
#endif
	return ret;
}


inline QString
cEncodeUrl (const QString &url, QStringList args = QStringList ())
{
	QByteArray url_ba = url.toUtf8 ();

	QString ret;
//#if HAVE_XMMSV
//#else
	QList<QByteArray> args_ba;
	int narg = args.size ();
	const char ** c_args = NULL;
	if (narg > 0) {
		c_args = static_cast<const char**> (malloc (narg * (sizeof (char *)+1)));
		c_args[narg] = NULL;
		for (int i = 0; i < narg; i++) {
			args_ba.append (args[i].toUtf8 ());
			// constData gives a pointer to QByteArrays internal data store
			// so I don't have to delete it later
			c_args[i] = args_ba[i].constData ();
		}
	}

	char *p_enc = _xmmsc_medialib_encode_url (url_ba.constData(), narg, c_args);
	free (c_args);
	ret = QString::fromUtf8 (p_enc);
	free (p_enc);
//#endif
	return ret;
}
#endif //HAVE_CBINDINGS


// The tests

void
TestUrl::unchangedCharacters ()
{
	QString encoded = Medialib::encodeUrl (dontEncode);
	QCOMPARE (encoded, dontEncode);
}

void
TestUrl::encodeDecodeUrl_data ()
{
	setTestUrls ();
}

void
TestUrl::encodeDecodeUrl ()
{
	QFETCH (QString, testurl);

	QString encoded = Medialib::encodeUrl (testurl);
	QString retval = Medialib::decodeUrl (encoded);
	QCOMPARE (retval, testurl);
}

void
TestUrl::decodeUrl_data ()
{
	setTestUrls ();
}

void
TestUrl::decodeUrl ()
{
	QFETCH (QString, testurl);
#ifdef HAVE_CBINDINGS
	QString encoded = cEncodeUrl (testurl);
	QString retval = Medialib::decodeUrl (encoded);
	QCOMPARE (retval, testurl);
#else
	QSKIP ("The c-bindings are needed to test url decoding", SkipAll);
#endif

}

void
TestUrl::encodeUrl_data ()
{
	setTestUrls ();
}

void
TestUrl::encodeUrl ()
{
	QFETCH (QString, testurl);
#ifdef HAVE_CBINDINGS
	QString encoded = Medialib::encodeUrl (testurl);
	QString retval = cDecodeUrl (encoded);
	QCOMPARE (retval, testurl);
#else
	QSKIP ("The c-bindings are needed to test url encoding", SkipAll);
#endif
}

// FIXME: still a big todo...
void
TestUrl::encodeUrlWithArguments_data ()
{
	QStringList arguments;

	QTest::addColumn<QStringList>("args");

	QTest::newRow ("Empty") << arguments;

	arguments << "arg1";
	QTest::newRow ("Single argument") << arguments;

	arguments << "arg2";
	QTest::newRow ("Two arguments") << arguments;

	arguments.clear ();
	arguments << "arg1" << "?arg2";
	QTest::newRow ("? in argument") << arguments;

	arguments << "&arg3";
	QTest::newRow ("& in argument") << arguments;
}

void
TestUrl::encodeUrlWithArguments ()
{
	QString testurl = "file:///path/My test_file.ext1&2";
	QFETCH (QStringList, args);
#ifdef HAVE_CBINDINGS
	QString qtEncoded = Medialib::encodeUrl (testurl, args);
	QString cEncoded = cEncodeUrl (testurl, args);
	QCOMPARE (qtEncoded, cEncoded);
#else
	QSKIP ("The c-bindings are needed to test url encoding", SkipAll);
#endif
}
