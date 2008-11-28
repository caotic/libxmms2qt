
#ifndef __TEST_URL_H__
#define __TEST_URL_H__

#include <QObject>
#include <QtTest/QtTest>

#include "medialib.h"

#include "test_common.h"

// We don't need to connect to the server, so we only inherit from QObject
class TestUrl : public QObject
{
	Q_OBJECT
	public:
		TestUrl () : QObject () {};

	private slots:
		/* Tests */
		void unchangedCharacters ();
		void encodeDecodeUrl ();
		void encodeDecodeUrl_data ();
		void decodeUrl ();
		void decodeUrl_data ();
		void encodeUrl ();
		void encodeUrl_data ();
		void encodeUrlWithArguments ();
		void encodeUrlWithArguments_data ();

	public slots:
		/* Callbacks for async operations */

	private:
};

#endif
