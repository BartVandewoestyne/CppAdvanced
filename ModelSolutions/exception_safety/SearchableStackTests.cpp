
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "SearchableStack.hpp"

using namespace CppUnit;
using namespace std;

//--------------------------------------------------------------------------------
class SearchableStackTests : public TestFixture {
public:

    void testEmpty()
        {
            SearchableStack<int> ss;
            CPPUNIT_ASSERT_THROW(ss.top(), SearchableStack<int>::Empty);
            CPPUNIT_ASSERT(!ss.contains(42));
        }

  void testPushPop()
        {
            SearchableStack<int> ss;
            ss.push(42);
            CPPUNIT_ASSERT_EQUAL(42, ss.top());
            CPPUNIT_ASSERT(ss.contains(42));
            CPPUNIT_ASSERT(!ss.contains(666));

            ss.push(666);
            CPPUNIT_ASSERT(ss.contains(42));
            CPPUNIT_ASSERT(ss.contains(666));
            CPPUNIT_ASSERT_EQUAL(666, ss.top());
 
            ss.pop();
            CPPUNIT_ASSERT_EQUAL(42, ss.top());
            CPPUNIT_ASSERT(ss.contains(42));
            CPPUNIT_ASSERT(!ss.contains(666));          

            ss.pop();
            CPPUNIT_ASSERT_THROW(ss.top(), SearchableStack<int>::Empty);
            CPPUNIT_ASSERT(!ss.contains(42));
            CPPUNIT_ASSERT(!ss.contains(666));
        }

    void testAssignment()
        {
            SearchableStack<int> ss;
            ss.push(42);

            // Copy has to contain one element == 42
            SearchableStack<int> sc;

            sc = ss;
            CPPUNIT_ASSERT_EQUAL(42, sc.top());
            sc.pop();
            CPPUNIT_ASSERT_THROW(sc.top(), SearchableStack<int>::Empty);
        }

    static Test* suite()
        {
            TestSuite* suite = new TestSuite();
            suite->addTest(new TestCaller<SearchableStackTests>("test top and contains for an empty container", &SearchableStackTests::testEmpty));
            suite->addTest(new TestCaller<SearchableStackTests>("test Pushing of an element, popping it and asserting intermediate states with top and contains", &SearchableStackTests::testPushPop));

            suite->addTest(new TestCaller<SearchableStackTests>("test assignment", &SearchableStackTests::testAssignment));

            return suite;
        }
};

//--------------------------------------------------------------------------------
int main()
{
    TextUi::TestRunner runner;
    runner.addTest(SearchableStackTests::suite());
    runner.run();
    cout << "Done!" << endl;
}
//--------------------------------------------------------------------------------
