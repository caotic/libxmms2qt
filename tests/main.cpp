#include "testBasics.h"
#include "testBindata.h"

int
main (int argc, char **argv)
{
	QApplication app (argc, argv);

	TestBasics basics;
	QTest::qExec (&basics);

	TestBindata bindata;
	QTest::qExec (&bindata);
}

//QTEST_MAIN(TestBasics);
