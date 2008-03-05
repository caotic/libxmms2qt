#include "test_playlist.h"
#include "test_bindata.h"

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
}

//QTEST_MAIN(TestBasics);
