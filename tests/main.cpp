#include "test_playlist.h"
#include "test_bindata.h"
#include "test_error.h"
#include "test_coll.h"

int
main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);

	{
		TestPlaylist basics;
		QTest::qExec (&basics, argc, argv);
	}

	{
		TestBindata bindata;
		QTest::qExec (&bindata, argc, argv);
	}
	{
		TestError error;
		QTest::qExec (&error, argc, argv);
	}
	{
		TestColl coll;
		QTest::qExec (&coll, argc, argv);
	}
}

//QTEST_MAIN(TestBasics);
