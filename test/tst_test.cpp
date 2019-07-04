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
    void createList();
};

TestList::TestList()
{
}

void TestList::createList()
{
    using namespace pa;
    List l;
    QVERIFY(l.size() == 0);
    auto backValue = l.pop_back();
    QVERIFY(backValue == int());
    QVERIFY(l.size() == 0);
    auto frontValue = l.pop_front();
    QVERIFY(frontValue == int());
    QVERIFY(l.size() == 0);
}

QTEST_MAIN(TestList)

#include "tst_test.moc"
