#include <QtTest/QtTest>

#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#define TVERIFY(statement, description) \
do {\
    if (statement) {\
        if (!QTest::qVerify(true, #statement, (description), __FILE__, __LINE__)) {\
			m_loop.exit();\
            return true;\
		}\
    } else {\
        if (!QTest::qVerify(false, #statement, (description), __FILE__, __LINE__)) {\
			m_loop.exit();\
            return true;\
		}\
    }\
} while (0)

#endif