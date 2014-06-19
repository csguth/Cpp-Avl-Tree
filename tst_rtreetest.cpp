#include <QString>
#include <QtTest>

#include "range_tree.h"
#include <set>
using std::set;

#include <algorithm>
using std::random_shuffle;

#include <cstdlib>

class RtreeTest : public QObject
{
    Q_OBJECT

public:
    RtreeTest();


private:
    Range_Tree createTreeFrom0ToEightK();
    Range_Tree createTreeFrom0To20K();

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

    void checkRootOfAnEmptyTree();

    void findExistentElement();
    void findInexistentElement();

    void insert1000SortedElementsAndFindOne();
    void insert1000NonSortedElementsAndFindOne();

    void removeAboveRange();
    void removeBelowRange();
    void removeFromAEmptyTree();
    void removeRootFromATreeWithASingleElement();
    void removeTheBiggestFromATreeWithTwoElements();
    void removeTheSmallestFromATreeWithTwoElements();
    void removeTheRootFromATreeWithThreeElements();
    void removeTheRootFromATreeWithTwoSubtreesWithThreeElementsEach();


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
    QVERIFY(rtree.root() == Range_Tree::EMPTY_TREE_ROOT);
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
    QVERIFY(rtree.root().first == 100 && rtree.root().second == 300);
}

void RtreeTest::insertLessThanRootWithoutOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(rtree.insert(50, 10));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertLessThanRootWithOverlap()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(!rtree.insert(80, 30));
    QVERIFY(rtree.size() == 1);
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
    QVERIFY(rtree.find(50, 49) == Range_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::checkIfRangeCanBeInsertedAfterRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.find(401, 49) == Range_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::checkIfRangeCannotBeInsertedBeforeRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.find(50, 100).first == 100 && rtree.find(50, 100).second == 300);
}

void RtreeTest::checkIfRangeCannotBeInsertedAfterRoot()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.find(390, 50).first == 100 && rtree.find(390, 50).second == 300);
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
//    rtree.print_tree();

    rtree.insert(30, 9);
//    rtree.print_tree();


    QVERIFY(rtree.root().first == 30);
    rtree.insert(10, 9);

//    rtree.print_tree();

    QVERIFY(rtree.root().first == 30);
    rtree.insert(20, 9);
//    rtree.print_tree();

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

Range_Tree RtreeTest::createTreeFrom0To20K()
{
    int begin = 0;
    int end = 20000;
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
    QVERIFY(rtree.find(80, 100) == Range_Tree::EMPTY_TREE_ROOT);
    QVERIFY(rtree.find(32, 5) == std::make_pair(30, unsigned(9)));
}


void RtreeTest::checkRootOfAnEmptyTree()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.empty());
    QVERIFY(rtree.root() == Range_Tree::EMPTY_TREE_ROOT);
}


void RtreeTest::findExistentElement()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(30, 9);
    std::pair<int, unsigned> result = rtree.find(33, 5);
    QVERIFY(result.first == 30 && result.second == 9);
}

void RtreeTest::findInexistentElement()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> result = rtree.find(30, 5);
    QVERIFY(result == Range_Tree::EMPTY_TREE_ROOT);
}
int myrandom (int i) { return std::rand()%i;}
void RtreeTest::insert1000NonSortedElementsAndFindOne()
{
    std::srand (0);
    std::vector<std::pair<int, unsigned> > mySet;
    Range_Tree rtree = createTreeFrom0To20K();
    for(unsigned i = 0; i < 1000; i++)
        mySet.push_back(make_pair(i*10, 5));
    random_shuffle(mySet.begin(), mySet.end(), myrandom);
    for(unsigned i = 0; i < mySet.size(); i++)
        QVERIFY(rtree.insert(mySet[i].first, mySet[i].second));
    QVERIFY(rtree.size() == mySet.size());
    std::pair<int, unsigned> result = rtree.find(51, 2);
    QVERIFY(result.first == 50 && result.second == 5);
}

void RtreeTest::insert1000SortedElementsAndFindOne()
{
    Range_Tree rtree = createTreeFrom0To20K();
    for(unsigned i = 0; i < 1000; i++)
        QVERIFY(rtree.insert(i*10, 5));
    QVERIFY(rtree.size() == 1000);
    std::pair<int, unsigned> result = rtree.find(51, 2);
    QVERIFY(result.first == 50 && result.second == 5);
}

void RtreeTest::removeAboveRange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> value_removed = rtree.remove(9000);
    QVERIFY(rtree.size() == 3);
    QVERIFY(value_removed == Range_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeBelowRange()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> value_removed = rtree.remove(-5);
    QVERIFY(rtree.size() == 3);
    QVERIFY(value_removed == Range_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeFromAEmptyTree()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.empty());
    std::pair<int, unsigned> value_removed = rtree.remove(10);
    QVERIFY(rtree.empty());
    QVERIFY(value_removed == Range_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeRootFromATreeWithASingleElement()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 300);
    std::pair<int, unsigned> value_removed = rtree.remove(13);
    QVERIFY(rtree.empty());
    QVERIFY(value_removed == std::make_pair(10, unsigned(300)));
}

void RtreeTest::removeTheBiggestFromATreeWithTwoElements()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(400, 300);
    rtree.insert(1000, 300);
    QVERIFY(rtree.size() == 2);
    std::pair<int, unsigned> value_removed = rtree.remove(1100);
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed == std::make_pair(1000, unsigned(300)));
}

void RtreeTest::removeTheSmallestFromATreeWithTwoElements()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(400, 200);
    rtree.insert(1000, 300);
    QVERIFY(rtree.size() == 2);
    std::pair<int, unsigned> value_removed = rtree.remove(500);
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed == std::make_pair(400, unsigned(200)));
}

void RtreeTest::removeTheRootFromATreeWithThreeElements()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(38, 200);
    rtree.insert(1000, 300);
    rtree.insert(4000, 500);
    QVERIFY(rtree.size() == 3);
    std::pair<int, unsigned> value_removed = rtree.remove(1120);
    QVERIFY(rtree.size() == 2);
    QVERIFY(value_removed == std::make_pair(1000, unsigned(300)));
    QVERIFY(rtree.root() == std::make_pair(4000, unsigned(500)));
    QVERIFY(rtree.find(40, 2) == std::make_pair(38, unsigned(200)));
}

void RtreeTest::removeTheRootFromATreeWithTwoSubtreesWithThreeElementsEach()
{
    Range_Tree rtree = createTreeFrom0ToEightK();
    rtree.insert(4000, 50);
    rtree.insert(2000, 25);
    rtree.insert(6000, 25);
    rtree.insert(1000, 25);
    rtree.insert(3000, 25);
    rtree.insert(5000, 25);
    rtree.insert(7000, 25);
    QVERIFY(rtree.size() == 7);
    QVERIFY(rtree.root() == std::make_pair(4000, unsigned(50)));
    std::pair<int, unsigned> value_removed = rtree.remove(4005);
    QVERIFY(rtree.size() == 6);
    QVERIFY(value_removed == std::make_pair(4000, unsigned(50)));
    QVERIFY(rtree.root() == std::make_pair(5000, unsigned(25)));
    QVERIFY(rtree.find(6005, 3) == std::make_pair(6000, unsigned(25)));
}



QTEST_APPLESS_MAIN(RtreeTest)

#include "tst_rtreetest.moc"
