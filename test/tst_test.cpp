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
    void insertToList();
};

TestList::TestList()
{
}

void TestList::createEmptyList()
{
    using namespace pa;
    List l;
    QVERIFY(l.size() == 0);
    auto backValue = l.popBack();
    QVERIFY(backValue == int());
    QVERIFY(l.size() == 0);
    auto frontValue = l.popFront();
    QVERIFY(frontValue == int());
    QVERIFY(l.size() == 0);
}

void TestList::insertToList()
{
    using namespace pa;
    List l;
    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);
    QVERIFY(l.size() == 3);
}

QTEST_MAIN(TestList)

#include "tst_test.moc"
