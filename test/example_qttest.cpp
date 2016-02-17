#include <QTest>

class Example : public QObject {
  Q_OBJECT
    private slots:
    void t1() { QVERIFY(true); }
};

QTEST_MAIN(Example)
#include "example_qttest.moc"
