
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "EndsWith.hpp"
#include "unary_negate.hpp"

using namespace CppUnit;
using std::endl;
using std::cout;

// The following needs to be looked into
// This should resolve the name clash, but it didn't!
// I was forced to explicitly "using std::cout" and std::endl;
// Or explicitly mention tass:: where ever I use unary_negate
//using namespace tass;
//using tass::unary_negate;

using tass::unary_negate;
using tass::not1;

//--------------------------------------------------------------------------------
class unary_negate_tests : public TestFixture {
public:
    
    void testOkTargetEndsWith()
        {
            unary_negate<EndsWith> neg(EndsWith("foo"));

            CPPUNIT_ASSERT(!neg("foo"));
            CPPUNIT_ASSERT(!neg("afoo"));
            CPPUNIT_ASSERT(neg("boo"));
            CPPUNIT_ASSERT(neg("aboo"));
            CPPUNIT_ASSERT(neg("o"));
            CPPUNIT_ASSERT(neg(""));
        }

    void testEmptyTargetEndsWith()
        {
            auto neg = not1(EndsWith(""));

            CPPUNIT_ASSERT(neg("foo"));
            CPPUNIT_ASSERT(!neg(""));    
        }

    static Test* suite()
        {
            TestSuite* suite = new TestSuite();
            suite->addTest(new TestCaller<unary_negate_tests>("test a normal target", &unary_negate_tests::testOkTargetEndsWith));
            suite->addTest(new TestCaller<unary_negate_tests>("test an empty target", &unary_negate_tests::testEmptyTargetEndsWith));
            return suite;
        }
};

//--------------------------------------------------------------------------------
int main()
{
    TextUi::TestRunner runner;
    runner.addTest(unary_negate_tests::suite());
    runner.run();
    cout << "Done!" << endl;
}
//--------------------------------------------------------------------------------
