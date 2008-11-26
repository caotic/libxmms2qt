#include <QtTest/QtTest>

using namespace XMMSQt;

#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#define TVERIFY(statement, description) \
do {\
    if (statement) {\
        if (!QTest::qVerify(true, #statement, (description), __FILE__, __LINE__)) {\
			waitDone ();\
            return true;\
		}\
    } else {\
        if (!QTest::qVerify(false, #statement, (description), __FILE__, __LINE__)) {\
			waitDone ();\
            return true;\
		}\
    }\
} while (0)

#endif
