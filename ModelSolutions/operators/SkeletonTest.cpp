
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "yourheader.hpp"

using namespace CppUnit;
using namespace std;

//--------------------------------------------------------------------------------
class YourTests : public TestFixture {
public:
    void testOkTarget()
        {
            CPPUNIT_ASSERT(false);
        }

    void testEmptyTarget()
        {
            CPPUNIT_ASSERT(false);    
        }

    static Test* suite()
        {
            TestSuite* suite = new TestSuite();
            suite->addTest(new TestCaller<YourTests>("test a normal target", &YourTests::testOkTarget));
            suite->addTest(new TestCaller<YourTests>("test an empty target", &YourTests::testEmptyTarget));
            return suite;
        }
};

//--------------------------------------------------------------------------------
int main()
{
    TextUi::TestRunner runner;
    runner.addTest(YourTests::suite());
    runner.run();
    cout << "Done!" << endl;
}
//--------------------------------------------------------------------------------
