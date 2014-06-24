#include <QString>
#include <QtTest>

#include "range_tree.h"
#include <set>
using std::set;

#include <algorithm>
using std::random_shuffle;

#include <cstdlib>

#include "interval.h"

class RtreeTest : public QObject
{
    Q_OBJECT

public:
    RtreeTest();


private:
    AVL_Tree<NonOverlappingInterval> createTreeFrom0ToEightK();
    AVL_Tree<NonOverlappingInterval> createTreeFrom0To20K();

private Q_SLOTS:
    void CreateAValidInterval();
    void CompareTwoIntervals();


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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.begin() == 0);
    QVERIFY(rtree.end() == 8000);
    QVERIFY(rtree.empty());
//    QVERIFY(rtree.root() == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::insertAboveRange()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(!rtree.insert(7800, 300));
}

void RtreeTest::insertBelowRange()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(!rtree.insert(-5, 300));
}

void RtreeTest::insertValidRange()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(!rtree.empty());
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkNumberOfNodes()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.size() == 0);
    rtree.insert(100, 300);
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.root().first == 100 && rtree.root().second == 300);
}

void RtreeTest::insertLessThanRootWithoutOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(rtree.insert(50, 10));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertLessThanRootWithOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.insert(100, 300));
    QVERIFY(!rtree.insert(80, 30));
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::insertGreatherThanRootWithoutOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.insert(401, 30));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertGreatherThanRootWithOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(!rtree.insert(390, 30));
    QVERIFY(rtree.size() != 2);
}

void RtreeTest::checkIfRangeCanBeInsertedBeforeRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
//    QVERIFY(rtree.find(50, 49) == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::checkIfRangeCanBeInsertedAfterRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
//    QVERIFY(rtree.find(401, 49) == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::checkIfRangeCannotBeInsertedBeforeRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.find(50, 100).first == 100 && rtree.find(50, 100).second == 300);
}

void RtreeTest::checkIfRangeCannotBeInsertedAfterRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(100, 300);
    QVERIFY(rtree.find(390, 50).first == 100 && rtree.find(390, 50).second == 300);
}


void RtreeTest::rootChangeWithLeftRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(0, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(20, 9);
    QVERIFY(rtree.root().first == 0);
    rtree.insert(10, 9);
    QVERIFY(rtree.root().first == 10);
}

void RtreeTest::rootChangeWithDoubleRightRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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

AVL_Tree<NonOverlappingInterval> RtreeTest::createTreeFrom0ToEightK()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    rtree.insert(numeric_limits<int>::min(), unsigned(numeric_limits<int>::max()));
    return rtree;
}

AVL_Tree<NonOverlappingInterval> RtreeTest::createTreeFrom0To20K()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    rtree.insert(numeric_limits<int>::min(), unsigned(20000+numeric_limits<int>::max()));
    return rtree;
}


void RtreeTest::CreateAValidInterval()
{
    const NonOverlappingInterval interval(120, 10);
    QVERIFY(interval.begin() == 120);
    QVERIFY(interval.end() == 129);
    QVERIFY(interval.size() == 10);
}

void RtreeTest::CompareTwoIntervals()
{

}

void RtreeTest::insertSixDowntoZero()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(60, 9);
    rtree.insert(50, 9);
    rtree.insert(40, 9);
    rtree.insert(30, 9);
    rtree.insert(20, 9);
    rtree.insert(10, 9);
    rtree.insert(0, 9);
//    QVERIFY(rtree.find(80, 100) == AVL_Tree::EMPTY_TREE_ROOT);
    QVERIFY(rtree.find(32, 5) == std::make_pair(30, unsigned(9)));
}


void RtreeTest::checkRootOfAnEmptyTree()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.empty());
//    QVERIFY(rtree.root() == AVL_Tree::EMPTY_TREE_ROOT);
}


void RtreeTest::findExistentElement()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(30, 9);
    std::pair<int, unsigned> result = rtree.find(33, 5);
    QVERIFY(result.first == 30 && result.second == 9);
}

void RtreeTest::findInexistentElement()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> result = rtree.find(30, 5);
//    QVERIFY(result == AVL_Tree::EMPTY_TREE_ROOT);
}
int myrandom (int i) { return std::rand()%i;}
void RtreeTest::insert1000NonSortedElementsAndFindOne()
{
    std::srand (0);
    std::vector<std::pair<int, unsigned> > mySet;
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0To20K();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0To20K();
    for(unsigned i = 0; i < 1000; i++)
        QVERIFY(rtree.insert(i*10, 5));
    QVERIFY(rtree.size() == 1000);
    std::pair<int, unsigned> result = rtree.find(51, 2);
    QVERIFY(result.first == 50 && result.second == 5);
}

void RtreeTest::removeAboveRange()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> value_removed = rtree.remove(9000);
    QVERIFY(rtree.size() == 3);
//    QVERIFY(value_removed == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeBelowRange()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 9);
    rtree.insert(20, 9);
    rtree.insert(40, 9);
    std::pair<int, unsigned> value_removed = rtree.remove(-5);
    QVERIFY(rtree.size() == 3);
//    QVERIFY(value_removed == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeFromAEmptyTree()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    QVERIFY(rtree.empty());
    std::pair<int, unsigned> value_removed = rtree.remove(10);
    QVERIFY(rtree.empty());
//    QVERIFY(value_removed == AVL_Tree::EMPTY_TREE_ROOT);
}

void RtreeTest::removeRootFromATreeWithASingleElement()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(10, 300);
    std::pair<int, unsigned> value_removed = rtree.remove(13);
    QVERIFY(rtree.empty());
    QVERIFY(value_removed == std::make_pair(10, unsigned(300)));
}

void RtreeTest::removeTheBiggestFromATreeWithTwoElements()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(400, 300);
    rtree.insert(1000, 300);
    QVERIFY(rtree.size() == 2);
    std::pair<int, unsigned> value_removed = rtree.remove(1100);
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed == std::make_pair(1000, unsigned(300)));
}

void RtreeTest::removeTheSmallestFromATreeWithTwoElements()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
    rtree.insert(400, 200);
    rtree.insert(1000, 300);
    QVERIFY(rtree.size() == 2);
    std::pair<int, unsigned> value_removed = rtree.remove(500);
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed == std::make_pair(400, unsigned(200)));
}

void RtreeTest::removeTheRootFromATreeWithThreeElements()
{
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
    AVL_Tree<NonOverlappingInterval> rtree = createTreeFrom0ToEightK();
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
