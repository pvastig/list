#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "../list.h"

class TestList : public QObject
{
    Q_OBJECT

public:
    TestList();

private Q_SLOTS:
    void createEmptyList();
    void pushBack();
    void pushFront();
    void popFront();
    void popBack();
    void remove();
    void insert();
};

TestList::TestList()
{
}

void TestList::createEmptyList()
{
    using namespace pa;
    List<int> l;
    QVERIFY(l.size() == 0);
}

void TestList::pushBack()
{
    using namespace pa;
    List<int> l;
    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);
    QVERIFY(l.size() == 3);
}

void TestList::pushFront()
{
    using namespace pa;
    List<int> l;
    l.pushFront(3);
    l.pushFront(2);
    l.pushFront(1);
    QVERIFY(l.size() == 3);
}

void TestList::popFront()
{
    using namespace pa;
    List<int> l;
    l.pushFront(3);
    l.pushFront(2);
    l.pushFront(1);
    l.popFront();
    QVERIFY(l.size() == 2);
    l.popFront();
    QVERIFY(l.size() == 1);
    l.popFront();
    QVERIFY(l.size() == 0);
}

void TestList::popBack()
{
    using namespace pa;
    List<int> l;
    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);
    l.popFront();
    QVERIFY(l.size() == 2);
}

void TestList::remove()
{
    using namespace pa;
    {
        List<int> l;
        l.pushBack(1);
        l.pushBack(2);
        l.pushBack(3);
        l.remove(3);
        QVERIFY(l.size() == 2);
    }
    {
        List<int> l;
        l.pushBack(1);
        l.pushBack(2);
        l.pushBack(3);
        l.remove(1);
        QVERIFY(l.size() == 2);
    }
    {
        List<int> l;
        l.pushBack(1);
        l.pushBack(2);
        l.pushBack(3);
        l.remove(2);
        QVERIFY(l.size() == 2);
    }
    {
        List<int> l;
        l.pushBack(1);
        l.remove(1);
        QVERIFY(l.size() == 0);
        QVERIFY(l.empty());
    }
}

void TestList::insert()
{
    using namespace pa;
    List<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    QVERIFY(l.size() == 3);
}

QTEST_MAIN(TestList)

#include "tst_test.moc"
