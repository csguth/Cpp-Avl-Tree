#include <QString>
#include <QtTest>

#include "range_tree.h"

class RtreeTest : public QObject
{
    Q_OBJECT

public:
    RtreeTest();


private:
    Range_Tree createTreeFrom0ToEightK();

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

    void rootChangeWithDoubleLeftRotation();
    void rootChangeWithDoubleRightRotation();

    void insertZeroToSix();
    void insertSixDowntoZero();

    void findingAValue();

    void printingATree();

};

RtreeTest::RtreeTest()
{
}

void RtreeTest::createAEmptyTreeWithARange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.begin() == 0);
    QVERIFY(rtree.end() == 8000);
    QVERIFY(rtree.empty());
    QVERIFY(rtree._root == NULL);
}

void RtreeTest::insertAboveRange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(!rtree.insert(7800, 300));
}

void RtreeTest::insertBelowRange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(!rtree.insert(-5, 300));
}

void RtreeTest::insertValidRange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(!rtree.empty());
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkNumberOfNodes()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.size() == 0);
    rtree.insert(100, 300);
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree._root != NULL);
}

void RtreeTest::insertLessThanRootWithoutOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.insert(50, 10));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertLessThanRootWithOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(!rtree.insert(80, 30));
    QVERIFY(rtree.size() != 2);
}

void RtreeTest::insertGreatherThanRootWithoutOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.insert(401, 30));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertGreatherThanRootWithOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(!rtree.insert(390, 30));
    QVERIFY(rtree.size() != 2);
}

void RtreeTest::checkIfRangeCanBeInsertedBeforeRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.check(50, 49));
}

void RtreeTest::checkIfRangeCanBeInsertedAfterRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.check(401, 50));
}

void RtreeTest::checkIfRangeCannotBeInsertedBeforeRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(!rtree.check(50, 100));
}

void RtreeTest::checkIfRangeCannotBeInsertedAfterRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(!rtree.check(390, 50));
}


void RtreeTest::rootChangeWithLeftRotation()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 10);
    rtree.insert(30, 9);
    QVERIFY(rtree.root().first == 10);
}

void RtreeTest::rootChangeWithRightRotation()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(30, 9);
    QVERIFY(rtree.root().first == 30);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 30);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 20);
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 20);
}

void RtreeTest::rootChangeWithDoubleLeftRotation()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 10);
}

void RtreeTest::rootChangeWithDoubleRightRotation()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.print_tree();

    rtree.insert(30, 9);
    rtree.print_tree();


    QVERIFY(rtree.root().first == 30);
    rtree.insert(10, 9);

    rtree.print_tree();

    QVERIFY(rtree.root().first == 30);
    rtree.insert(20, 9);
    rtree.print_tree();

    QVERIFY(rtree.root().first == 20);



}

void RtreeTest::insertZeroToSix()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 10);
    rtree.insert(30, 9);
    QVERIFY(rtree.root().first == 10);
    rtree.insert(40, 9);
    QVERIFY(rtree.root().first == 10);
    rtree.insert(50, 9);
    QVERIFY(rtree.root().first == 30);
    rtree.insert(60, 9);
    QVERIFY(rtree.root().first == 30);
}

Range_Tree RtreeTest::createTreeFrom0ToEightK()
{
    int begin = 0;
    int end = 8000;
    Range_Tree rtree(begin, end);
    return rtree;
}

void RtreeTest::insertSixDowntoZero()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(60, 9);
    QVERIFY(rtree.root().first == 60);
    rtree.insert(50, 9);
    QVERIFY(rtree.root().first == 60);
    rtree.insert(40, 9);
    QVERIFY(rtree.root().first == 50);
    rtree.insert(30, 9);
    QVERIFY(rtree.root().first == 50);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 50);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 30);
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 30);

}

void RtreeTest::findingAValue()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(60, 9);
    rtree.insert(50, 9);
    rtree.insert(40, 9);
    rtree.insert(30, 9);
    rtree.insert(20, 9);
    rtree.insert(10, 9);
    rtree.insert(0, 9);
    QVERIFY(rtree.check(80, 100));
    QVERIFY(!rtree.check(32, 5));
}

void RtreeTest::printingATree()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(60, 9);
    rtree.insert(50, 9);
    rtree.insert(40, 9);
    rtree.insert(30, 9);
    rtree.insert(20, 9);
    rtree.insert(10, 9);
    rtree.insert(0, 9);

    rtree.print_tree();

    QVERIFY(true);
}


QTEST_APPLESS_MAIN(RtreeTest)

#include "tst_rtreetest.moc"
