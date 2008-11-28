#include "test_playlist.h"
#include "test_bindata.h"
#include "test_error.h"
#include "test_coll.h"
#include "test_url.h"

int
main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);
	// ret will count the total number of failed tests
	int ret = 0;

	{
		TestUrl urltest;
		ret += QTest::qExec (&urltest, argc, argv);
	}
	{
		TestError error;
		ret += QTest::qExec (&error, argc, argv);
	}
	{
		TestColl coll;
		ret += QTest::qExec (&coll, argc, argv);
	}
	{
		TestPlaylist playlist;
		ret += QTest::qExec (&playlist, argc, argv);
	}

	{
		TestBindata bindata;
		ret += QTest::qExec (&bindata, argc, argv);
	}

	qDebug () << "Sum of failed tests: " << ret;
	return ret;
}

//QTEST_MAIN(TestBasics);
