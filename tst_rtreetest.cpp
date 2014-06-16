#include <QString>
#include <QtTest>

#include "range_tree.h"

class RtreeTest : public QObject
{
    Q_OBJECT

public:
    RtreeTest();

private:
    Range_Tree createATreeFromZeroToEightK();

private Q_SLOTS:
    void createAEmptyTreeWithARange();
    void insertAboveRange();
    void insertBelowRange();
    void insertValidRange();
    void checkNumberOfNodes();
    void checkRoot();

    void insertLessThanRootWithoutOverlap();
    void insertLessThanRootWithOverlap();
    void insertGreatherThanRootWithoutOverlap();
    void insertGreatherThanRootWithOverlap();

    void checkIfRangeCanBeInsertedBeforeRoot();
    void checkIfRangeCanBeInsertedAfterRoot();
    void checkIfRangeCannotBeInsertedBeforeRoot();
    void checkIfRangeCannotBeInsertedAfterRoot();

    void rootChangeWithLeftRotation();
    void rootChangeWithRightRotation();

    void insertOneToSix();

    void printTree();

};

RtreeTest::RtreeTest()
{
}




void RtreeTest::createAEmptyTreeWithARange()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    QVERIFY2(rtree.begin() == begin, "Failure");
    QVERIFY2(rtree.end() == end, "Failure");
    QVERIFY2(rtree.empty(), "Failure");
    QVERIFY(rtree.root() == NULL);
}

void RtreeTest::insertAboveRange()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    QVERIFY(!rtree.insert(7800, 300));
}

void RtreeTest::insertBelowRange()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    QVERIFY(!rtree.insert(-5, 300));
}

void RtreeTest::insertValidRange()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(!rtree.empty());
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkNumberOfNodes()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    QVERIFY(rtree.size() == 0);
    rtree.insert(100, 300);
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkRoot()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    const Range_Tree::Node * root = rtree.root();
    QVERIFY(root != NULL);
}

void RtreeTest::insertLessThanRootWithoutOverlap()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(rtree.insert(50, 10));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertLessThanRootWithOverlap()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(!rtree.insert(80, 30));
    QVERIFY(rtree.size() != 2);
}

void RtreeTest::insertGreatherThanRootWithoutOverlap()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(rtree.insert(401, 30));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertGreatherThanRootWithOverlap()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(!rtree.insert(390, 30));
    QVERIFY(rtree.size() != 2);
}

void RtreeTest::checkIfRangeCanBeInsertedBeforeRoot()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(rtree.check(50, 49));
}

void RtreeTest::checkIfRangeCanBeInsertedAfterRoot()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(rtree.check(401, 50));
}

void RtreeTest::checkIfRangeCannotBeInsertedBeforeRoot()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(!rtree.check(50, 100));
}

void RtreeTest::checkIfRangeCannotBeInsertedAfterRoot()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(100, 300);
    QVERIFY(!rtree.check(390, 50));
}


void RtreeTest::rootChangeWithLeftRotation()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(1500, 299);
    const Range_Tree::Node * r = rtree.root();
    rtree.insert(1800, 100);
    QVERIFY(r == rtree.root());
    rtree.insert(2000, 300);
    QVERIFY(r != rtree.root());
    const Range_Tree::Node * newr = rtree.root();
    QVERIFY(newr->value() == make_pair(1800, 100));
    rtree.insert(2500, 250);
    QVERIFY(newr == rtree.root());
}

void RtreeTest::rootChangeWithRightRotation()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(2500, 250);
    const Range_Tree::Node * r = rtree.root();
    rtree.insert(2000, 300);
    QVERIFY(r == rtree.root());
    rtree.insert(1800, 100);
    QVERIFY(r != rtree.root());
    const Range_Tree::Node * newr = rtree.root();
    QVERIFY(newr->value() == make_pair(2000, 300));
    QVERIFY(newr == rtree.root());
    rtree.insert(1500, 299);
}

void RtreeTest::insertOneToSix()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(1, 9);
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(30, 9);
    rtree.insert(40, 9);
    rtree.insert(50, 9);
    rtree.insert(60, 9);
    QVERIFY(rtree.root()->value().first == 40);
}

void RtreeTest::printTree()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    rtree.insert(2500, 250);
    const Range_Tree::Node * r = rtree.root();
    rtree.insert(2000, 300);
    QVERIFY(r == rtree.root());
    rtree.insert(1800, 100);
    QVERIFY(r != rtree.root());
    const Range_Tree::Node * newr = rtree.root();
    QVERIFY(newr->value() == make_pair(2000, 300));
    QVERIFY(newr == rtree.root());
    rtree.insert(1500, 299);
    rtree.print_tree();
}

QTEST_APPLESS_MAIN(RtreeTest)

#include "tst_rtreetest.moc"
