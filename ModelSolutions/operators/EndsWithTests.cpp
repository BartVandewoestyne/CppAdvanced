
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "EndsWith.hpp"

using namespace CppUnit;
using namespace std;

//--------------------------------------------------------------------------------
class EndsWithTests : public TestFixture {
public:
    void testOkTarget()
        {
            EndsWith ew("foo");

            CPPUNIT_ASSERT(ew("foo"));
            CPPUNIT_ASSERT(ew("afoo"));
            CPPUNIT_ASSERT(!ew("boo"));
            CPPUNIT_ASSERT(!ew("aboo"));
            CPPUNIT_ASSERT(!ew("o"));
            CPPUNIT_ASSERT(!ew(""));
        }

    void testEmptyTarget()
        {
            EndsWith ew("");

            CPPUNIT_ASSERT(!ew("foo"));
            CPPUNIT_ASSERT(ew(""));    
        }

    static Test* suite()
        {
            TestSuite* suite = new TestSuite();
            suite->addTest(new TestCaller<EndsWithTests>("test a normal target", &EndsWithTests::testOkTarget));
            suite->addTest(new TestCaller<EndsWithTests>("test an empty target", &EndsWithTests::testEmptyTarget));
            return suite;
        }
};

//--------------------------------------------------------------------------------
int main()
{
    TextUi::TestRunner runner;
    runner.addTest(EndsWithTests::suite());
    runner.run();
    cout << "Done!" << endl;
}
//--------------------------------------------------------------------------------
