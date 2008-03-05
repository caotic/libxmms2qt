#include "test_playlist.h"
#include "test_bindata.h"
#include "test_error.h"

int
main (int argc, char **argv)
{
	QApplication app (argc, argv);

	{
		TestPlaylist basics;
		QTest::qExec (&basics);
	}

	{
		TestBindata bindata;
		QTest::qExec (&bindata);
	}
	{
		TestError error;
		QTest::qExec (&error);
	}
}

//QTEST_MAIN(TestBasics);
