// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtTest/QtTest>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "private/bmlayer_p.h"
#include "private/bmstroke_p.h"

using namespace Qt::StringLiterals;

class tst_BMStroke: public QObject
{
    Q_OBJECT

public:
    tst_BMStroke();
    ~tst_BMStroke();

private:

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testStaticInitialColor();
    void testStaticInitialOpacity();
    void testStaticInitialWidth();
    void testStaticInitialCapStyle();
    void testStaticInitialJoinStyle();
    void testStaticInitialMiterLimit();
    void testStaticUpdatedColor();
    void testStaticUpdatedOpacity();
    void testStaticUpdatedWidth();
    void testStaticUpdatedCapStyle();
    void testStaticUpdatedJoinStyle();
    void testStaticUpdatedMiterLimit();

    void testAnimatedInitialColor();
    void testAnimatedInitialOpacity();
    void testAnimatedInitialWidth();
    void testAnimatedInitialCapStyle();
    void testAnimatedInitialJoinStyle();
    void testAnimatedInitialMiterLimit();
    void testAnimatedUpdatedColor();
    void testAnimatedUpdatedOpacity();
    void testAnimatedUpdatedWidth();

    void testName();
    void testType();
    void testActive();
    void testHidden();

private:
    void loadTestData(const QString &filename);
    void updateProperty(int frame);

    BMStroke *m_stroke = nullptr;
};

tst_BMStroke::tst_BMStroke()
{

}

tst_BMStroke::~tst_BMStroke()
{

}

void tst_BMStroke::initTestCase()
{
}

void tst_BMStroke::cleanupTestCase()
{
    if (m_stroke)
        delete m_stroke;
}

void tst_BMStroke::testStaticInitialColor()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(m_stroke->pen().color() == QColor(Qt::blue));
}

void tst_BMStroke::testStaticInitialOpacity()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(qFuzzyCompare(m_stroke->opacity(), 100.0));
}

void tst_BMStroke::testStaticInitialWidth()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(qFuzzyCompare(m_stroke->pen().width(), 2.0));
}

void tst_BMStroke::testStaticInitialCapStyle()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(m_stroke->pen().capStyle() == Qt::FlatCap);
}

void tst_BMStroke::testStaticInitialJoinStyle()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(m_stroke->pen().joinStyle() == Qt::MiterJoin);
}

void tst_BMStroke::testStaticInitialMiterLimit()
{
    loadTestData("stroke_static_blue_2.json");

    QVERIFY(qFuzzyCompare(m_stroke->pen().miterLimit(), 4.0));
}

void tst_BMStroke::testStaticUpdatedColor()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(m_stroke->pen().color() == QColor(Qt::blue));
}

void tst_BMStroke::testStaticUpdatedOpacity()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(qFuzzyCompare(m_stroke->opacity(), 100.0));
}

void tst_BMStroke::testStaticUpdatedWidth()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(qFuzzyCompare(m_stroke->pen().width(), 2.0));
}

void tst_BMStroke::testStaticUpdatedCapStyle()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(m_stroke->pen().capStyle() == Qt::FlatCap);
}

void tst_BMStroke::testStaticUpdatedJoinStyle()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(m_stroke->pen().joinStyle() == Qt::MiterJoin);
}

void tst_BMStroke::testStaticUpdatedMiterLimit()
{
    loadTestData("stroke_static_blue_2.json");
    updateProperty(179);

    QVERIFY(qFuzzyCompare(m_stroke->pen().miterLimit(), 4.0));
}

void tst_BMStroke::testAnimatedInitialColor()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(m_stroke->pen().color() == QColor(Qt::blue));
}

void tst_BMStroke::testAnimatedInitialOpacity()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(qFuzzyCompare(m_stroke->opacity(), 100.0));
}

void tst_BMStroke::testAnimatedInitialWidth()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(qFuzzyCompare(m_stroke->pen().width(), 5.0));
}

void tst_BMStroke::testAnimatedInitialCapStyle()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(m_stroke->pen().capStyle() == Qt::FlatCap);
}

void tst_BMStroke::testAnimatedInitialJoinStyle()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(m_stroke->pen().joinStyle() == Qt::MiterJoin);
}

void tst_BMStroke::testAnimatedInitialMiterLimit()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(0);

    QVERIFY(qFuzzyCompare(m_stroke->pen().miterLimit(), 4.0));
}

void tst_BMStroke::testAnimatedUpdatedColor()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(179);

    QVERIFY(m_stroke->pen().color() == QColor(Qt::white));
}

void tst_BMStroke::testAnimatedUpdatedOpacity()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(179);

    QVERIFY(qFuzzyCompare(m_stroke->opacity(), 10.0));
}

void tst_BMStroke::testAnimatedUpdatedWidth()
{
    loadTestData("stroke_animated_blue5_white1.json");
    updateProperty(179);

    QVERIFY(qFuzzyCompare(m_stroke->pen().width(), 1.0));
}

void tst_BMStroke::testName()
{
    loadTestData("stroke_static_blue_2.json");
    QVERIFY(m_stroke->name() == QString("Stroke 1"));
}

void tst_BMStroke::testType()
{
    loadTestData("stroke_static_blue_2.json");
    QVERIFY(m_stroke->type() == BM_SHAPE_STROKE_IX);
}

void tst_BMStroke::testActive()
{
    loadTestData("stroke_static_blue_2.json");
    QVERIFY(m_stroke->active(100) == true);

    loadTestData("stroke_hidden.json");
    QVERIFY(m_stroke->active(100) == false);
}

void tst_BMStroke::testHidden()
{
    loadTestData("stroke_hidden.json");
    QVERIFY(m_stroke->hidden() == true);
}

void tst_BMStroke::loadTestData(const QString &filename)
{
    if (m_stroke) {
        delete m_stroke;
        m_stroke = nullptr;
    }

    QFile sourceFile(QFINDTESTDATA(QLatin1String("data/") + filename));
    if (!sourceFile.exists())
        QFAIL("File does not exist");
    if (!sourceFile.open(QIODevice::ReadOnly))
        QFAIL("Cannot read test file");

    QByteArray json = sourceFile.readAll();

    sourceFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject rootObj = doc.object();
    if (rootObj.empty())
        QFAIL("Cannot parse test file");

    const auto version = QVersionNumber::fromString(rootObj.value("v"_L1).toString());

    QJsonArray layers = rootObj.value(QLatin1String("layers")).toArray();
    QJsonObject layerObj = layers[0].toObject();
    int type = layerObj.value(QLatin1String("ty")).toInt();
    if (type != 4)
        QFAIL("It's not shape layer");

    QJsonArray shapes = layerObj.value(QLatin1String("shapes")).toArray();
    QJsonArray::const_iterator shapesIt = shapes.constBegin();
    BMShape* shape = nullptr;
    while (shapesIt != shapes.end()) {
        QJsonObject childObj = (*shapesIt).toObject();
        shape = BMShape::construct(childObj, version);
        QVERIFY(shape != nullptr);
        if (shape->type() == BM_SHAPE_STROKE_IX)
            break;
        shapesIt++;
    }

    m_stroke = static_cast<BMStroke*>(shape);

    QVERIFY(m_stroke != nullptr);
}

void tst_BMStroke::updateProperty(int frame)
{
    m_stroke->updateProperties(frame);
}

QTEST_MAIN(tst_BMStroke)
#include "tst_bmstroke.moc"
