#include <QString>
#include <QtTest>

#include "avl_tree.h"

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
private Q_SLOTS:
    void CreateAValidInterval();
    void CompareTwoIntervals();
    void checkNumberOfNodes();
    void checkRoot();
    void insertLessThanRootWithoutOverlap();
    void insertLessThanRootWithOverlap();
    void insertGreatherThanRootWithoutOverlap();
    void insertGreaterThanRootWithOverlap();
    void checkIfRangeCanBeInsertedBeforeRoot();
    void checkIfRangeCanBeInsertedAfterRoot();
    void checkIfRangeCannotBeInsertedBeforeRoot();
    void checkIfRangeCannotBeInsertedAfterRoot();
    void rootChangeWithLeftRotation();
    void rootChangeWithRightRotation();
    void rootChangeWithDoubleLeftRotation();
    void rootChangeWithDoubleRightRotation();
    void insertZeroToSix();
    void findingAValue();
    void checkRootOfAnEmptyTree();
    void findExistentElement();
    void findInexistentElement();
    void insert1000SortedElementsAndFindOne();
    void insert1000NonSortedElementsAndFindOne();
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



void RtreeTest::checkNumberOfNodes()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.empty());
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval root(100, 300);
    rtree.insert(root);
    QVERIFY(rtree.root() == root);
}

void RtreeTest::insertLessThanRootWithoutOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(rtree.insert(NonOverlappingInterval(50, 10)));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertLessThanRootWithOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(!rtree.insert(NonOverlappingInterval(80, 30)));
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::insertGreatherThanRootWithoutOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(rtree.insert(NonOverlappingInterval(401, 30)));
    QVERIFY(rtree.size() == 2);
}

void RtreeTest::insertGreaterThanRootWithOverlap()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(!rtree.insert(NonOverlappingInterval(390, 30)));
    QVERIFY(rtree.size() == 1);
}

void RtreeTest::checkIfRangeCanBeInsertedBeforeRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree ;
    QVERIFY(rtree.insert(NonOverlappingInterval(100, 300)));
    QVERIFY(rtree.find(NonOverlappingInterval(50, 49)).sameAs(NonOverlappingInterval::invalid()));
}

void RtreeTest::checkIfRangeCanBeInsertedAfterRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    rtree.insert(NonOverlappingInterval(100, 300));
}

void RtreeTest::checkIfRangeCannotBeInsertedBeforeRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    rtree.insert(NonOverlappingInterval(100, 300));
    QVERIFY(rtree.find(NonOverlappingInterval(50, 100)).sameAs(NonOverlappingInterval(100, 300)));
}

void RtreeTest::checkIfRangeCannotBeInsertedAfterRoot()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    rtree.insert(NonOverlappingInterval(100, 300));
    QVERIFY(rtree.find(NonOverlappingInterval(390, 50)).sameAs(NonOverlappingInterval(100, 300)));
}


void RtreeTest::rootChangeWithLeftRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    NonOverlappingInterval d(30, 9);
    rtree.insert(a);
    QVERIFY(rtree.root().sameAs(a));
    rtree.insert(b);
    QVERIFY(rtree.root().sameAs(a));
    rtree.insert(c);
    QVERIFY(rtree.root().sameAs(b));
    rtree.insert(d);
    QVERIFY(rtree.root().sameAs(b));
}

void RtreeTest::rootChangeWithRightRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    NonOverlappingInterval d(30, 9);
    rtree.insert(d);
    QVERIFY(rtree.root().sameAs(d));
    rtree.insert(c);
    QVERIFY(rtree.root().sameAs(d));
    rtree.insert(b);
    QVERIFY(rtree.root().sameAs(c));
    rtree.insert(a);
    QVERIFY(rtree.root().sameAs(c));
}

void RtreeTest::rootChangeWithDoubleLeftRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);

    rtree.insert(a);
    QVERIFY(rtree.root().sameAs(a));
    rtree.insert(c);
    QVERIFY(rtree.root().sameAs(a));
    rtree.insert(b);
    QVERIFY(rtree.root().sameAs(b));
}

void RtreeTest::rootChangeWithDoubleRightRotation()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    rtree.insert(c);
    QVERIFY(rtree.root().sameAs(c));
    rtree.insert(a);
    QVERIFY(rtree.root().sameAs(c));
    rtree.insert(b);
    QVERIFY(rtree.root().sameAs(b));
}

void RtreeTest::insertZeroToSix()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    NonOverlappingInterval d(30, 9);
    NonOverlappingInterval e(40, 9);
    NonOverlappingInterval f(50, 9);
    NonOverlappingInterval g(60, 9);
    QVERIFY(rtree.insert(a));
    QVERIFY(rtree.root().sameAs(a));
    QVERIFY(rtree.insert(b));
    QVERIFY(rtree.root().sameAs(a));
    QVERIFY(rtree.insert(c));
    QVERIFY(rtree.root().sameAs(b));
    QVERIFY(rtree.insert(d));
    QVERIFY(rtree.root().sameAs(b));
    QVERIFY(rtree.insert(e));
    QVERIFY(rtree.root().sameAs(b));
    QVERIFY(rtree.insert(f));
    QVERIFY(rtree.root().sameAs(d));
    QVERIFY(rtree.insert(g));
    QVERIFY(rtree.root().sameAs(d));
}



void RtreeTest::CreateAValidInterval()
{
    const NonOverlappingInterval interval(120, 10);
    QVERIFY(interval.begin() == 120);
    QVERIFY(interval.end() == 129);
    QVERIFY(interval.size() == 10);
    QVERIFY(interval.valid());
}

void RtreeTest::CompareTwoIntervals()
{
    const NonOverlappingInterval a(120, 10);
    const NonOverlappingInterval b(140, 10);
    QVERIFY(a < b);
    QVERIFY(b > a);
    QVERIFY(!(a == b));
}


void RtreeTest::findingAValue()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    NonOverlappingInterval d(30, 9);
    NonOverlappingInterval e(40, 9);
    NonOverlappingInterval f(50, 9);
    NonOverlappingInterval g(60, 9);
    QVERIFY(rtree.insert(g));
    QVERIFY(rtree.insert(f));
    QVERIFY(rtree.insert(e));
    QVERIFY(rtree.insert(d));
    QVERIFY(rtree.insert(c));
    QVERIFY(rtree.insert(b));
    QVERIFY(rtree.insert(a));
    QVERIFY(rtree.find(NonOverlappingInterval(32, 5)).sameAs(NonOverlappingInterval(30, 9)));
}


void RtreeTest::checkRootOfAnEmptyTree()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.root().sameAs(NonOverlappingInterval::invalid()));
}


void RtreeTest::findExistentElement()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    NonOverlappingInterval d(30, 9);
    QVERIFY(rtree.insert(a));
    QVERIFY(rtree.insert(b));
    QVERIFY(rtree.insert(c));
    QVERIFY(rtree.insert(d));
    const NonOverlappingInterval result = rtree.find(NonOverlappingInterval(33, 5));
    QVERIFY(result.sameAs(d));
}

void RtreeTest::findInexistentElement()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    rtree.insert(a);
    rtree.insert(b);
    rtree.insert(c);
    const NonOverlappingInterval result = rtree.find(NonOverlappingInterval(30, 5));
    QVERIFY(result.sameAs(NonOverlappingInterval::invalid()));
}
int myrandom (int i) { return std::rand()%i;}
void RtreeTest::insert1000NonSortedElementsAndFindOne()
{
    std::srand (0);
    std::vector<std::pair<int, unsigned> > mySet;
    AVL_Tree<NonOverlappingInterval> row;
    for(unsigned i = 0; i < 1000; i++)
        mySet.push_back(make_pair(i*10, 5));
    random_shuffle(mySet.begin(), mySet.end(), myrandom);
    for(unsigned i = 0; i < mySet.size(); i++)
        QVERIFY(row.insert(NonOverlappingInterval(mySet[i].first, mySet[i].second)));
    QVERIFY(row.size() == mySet.size());
    const NonOverlappingInterval result = row.find(NonOverlappingInterval(51, 2));
    QVERIFY(result.sameAs(NonOverlappingInterval(50, 5)));
}

void RtreeTest::insert1000SortedElementsAndFindOne()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    for(unsigned i = 0; i < 1000; i++)
        QVERIFY(rtree.insert(NonOverlappingInterval(i*10, 5)));
    QVERIFY(rtree.size() == 1000);
    NonOverlappingInterval result = rtree.find(NonOverlappingInterval(51, 2));
    QVERIFY(result.sameAs(NonOverlappingInterval(50, 5)));
}

void RtreeTest::removeFromAEmptyTree()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(10, 1));
    QVERIFY(rtree.size() == 0);
    QVERIFY(value_removed.sameAs(NonOverlappingInterval::invalid()));
}

void RtreeTest::removeRootFromATreeWithASingleElement()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    QVERIFY(rtree.insert(NonOverlappingInterval(10, 300)));
    NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(13, 1));
    QVERIFY(rtree.empty());
    QVERIFY(value_removed.sameAs(NonOverlappingInterval(10, 300)));
}

void RtreeTest::removeTheBiggestFromATreeWithTwoElements()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    rtree.insert(a);
    rtree.insert(b);
    QVERIFY(rtree.size() == 2);
    const NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(10, 1));
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed.sameAs(b));
    QVERIFY(rtree.root().sameAs(a));
}

void RtreeTest::removeTheSmallestFromATreeWithTwoElements()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    rtree.insert(a);
    rtree.insert(b);
    QVERIFY(rtree.size() == 2);
    const NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(2, 1));
    QVERIFY(rtree.size() == 1);
    QVERIFY(value_removed.sameAs(a));
    QVERIFY(rtree.root().sameAs(b));
}

void RtreeTest::removeTheRootFromATreeWithThreeElements()
{
    AVL_Tree<NonOverlappingInterval> rtree ;
    NonOverlappingInterval a(0, 9);
    NonOverlappingInterval b(10, 9);
    NonOverlappingInterval c(20, 9);
    rtree.insert(a);
    rtree.insert(b);
    rtree.insert(c);
    QVERIFY(rtree.size() == 3);
    const NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(13, 1));
    QVERIFY(rtree.size() == 2);
    QVERIFY(value_removed.sameAs(b));
    QVERIFY(rtree.root().sameAs(c));
    QVERIFY(rtree.find(NonOverlappingInterval(5, 2)).sameAs(a));
}

void RtreeTest::removeTheRootFromATreeWithTwoSubtreesWithThreeElementsEach()
{
    AVL_Tree<NonOverlappingInterval> rtree;
    NonOverlappingInterval a(4000, 50);
    NonOverlappingInterval b(2000, 25);
    NonOverlappingInterval c(6000, 25);
    NonOverlappingInterval d(1000, 25);
    NonOverlappingInterval e(3000, 25);
    NonOverlappingInterval f(5000, 25);
    NonOverlappingInterval g(7000, 25);

    QVERIFY(rtree.insert(a));
    QVERIFY(rtree.insert(b));
    QVERIFY(rtree.insert(c));
    QVERIFY(rtree.insert(d));
    QVERIFY(rtree.insert(e));
    QVERIFY(rtree.insert(f));
    QVERIFY(rtree.insert(g));


    QVERIFY(rtree.size() == 7);
    QVERIFY(rtree.root().sameAs(a));
    NonOverlappingInterval value_removed = rtree.remove(NonOverlappingInterval(4005, 1));
    QVERIFY(rtree.size() == 6);
    QVERIFY(value_removed.sameAs(a));
    QVERIFY(rtree.root().sameAs(f));
    QVERIFY(rtree.find(NonOverlappingInterval(6005, 3)).sameAs(c));
}



QTEST_APPLESS_MAIN(RtreeTest)

#include "tst_rtreetest.moc"

