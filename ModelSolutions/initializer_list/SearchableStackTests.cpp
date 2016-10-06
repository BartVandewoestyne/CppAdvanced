
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

    /**
     * @brief To avoid duplicate testing wrt move semantics
     * Uses hard coded values, making it very tight with testMoveCtor and testMoveAssignment, as those values are pushed there
     */
    void moveHelper(SearchableStack<int>& original, SearchableStack<int>& newOne)
        {
            // Original Ss should be empty now
            CPPUNIT_ASSERT_THROW(original.top(), SearchableStack<int>::Empty);

            // New one should contain original data
            CPPUNIT_ASSERT_EQUAL(44, newOne.top());
            newOne.pop();
            CPPUNIT_ASSERT_EQUAL(42, newOne.top());
            newOne.pop();
            CPPUNIT_ASSERT_THROW(newOne.top(), SearchableStack<int>::Empty);
        }

    void testMoveCtor()
        {
            SearchableStack<int> ss;
            ss.push(42);
            ss.push(44);

            SearchableStack<int> sm(std::move(ss));

            moveHelper(ss, sm);
        }

    void testMoveAssignment()
        {
            SearchableStack<int> ss;
            ss.push(42);
            ss.push(44);

            SearchableStack<int> sm = std::move(ss);

            moveHelper(ss, sm);
        }


    void testSequenceConstructor()
        {
            SearchableStack<int> ss {42, 44};
            
            CPPUNIT_ASSERT(ss.contains(42));
            CPPUNIT_ASSERT(ss.contains(44));
            CPPUNIT_ASSERT(!ss.contains(666));

            CPPUNIT_ASSERT_EQUAL(44, ss.top());
            ss.pop();
            CPPUNIT_ASSERT_EQUAL(42, ss.top());
            ss.pop();
            CPPUNIT_ASSERT_THROW(ss.top(), SearchableStack<int>::Empty);           
        }

    static Test* suite()
        {
            TestSuite* suite = new TestSuite();
            suite->addTest(new TestCaller<SearchableStackTests>("test top and contains for an empty container", &SearchableStackTests::testEmpty));
            suite->addTest(new TestCaller<SearchableStackTests>("test Pushing of an element, popping it and asserting intermediate states with top and contains", &SearchableStackTests::testPushPop));

            suite->addTest(new TestCaller<SearchableStackTests>("test assignment", &SearchableStackTests::testAssignment));
            suite->addTest(new TestCaller<SearchableStackTests>("test move constructor", &SearchableStackTests::testMoveCtor));
            suite->addTest(new TestCaller<SearchableStackTests>("test move assignment", &SearchableStackTests::testMoveAssignment));
            suite->addTest(new TestCaller<SearchableStackTests>("test sequence constructor", &SearchableStackTests::testSequenceConstructor));

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
