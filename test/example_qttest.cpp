#include <QTest>

// Imports for units under test are relative to src/ directory
#include "TArea.h"

class TestQString : public QObject {
    Q_OBJECT
private slots:
    void toUpper_qverify();
    void toUpper_qcompare();
    void toUpper_usingdata();
    void toUpper_usingdata_data();
};


void TestQString::toUpper_qverify()
{
  QString str = "Hello";
  QVERIFY(str.toUpper() == "HELLO");
}

void TestQString::toUpper_qcompare()
{
  QString str = "Hello";
  QCOMPARE(str.toUpper(), QString("HELLO"));
}

void TestQString::toUpper_usingdata()
{
  QFETCH(QString, string);
  QFETCH(QString, result);

  QCOMPARE(string.toUpper(), result);
}

void TestQString::toUpper_usingdata_data()
{
  QTest::addColumn<QString>("string");
  QTest::addColumn<QString>("result");

  QTest::newRow("all lower") << "hello" << "HELLO";
  QTest::newRow("mixed")     << "Hello" << "HELLO";
  QTest::newRow("all upper") << "HELLO" << "HELLO";
}

QTEST_MAIN(TestQString)
#include "example_qttest.moc"
