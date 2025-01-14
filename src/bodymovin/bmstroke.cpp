// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "bmstroke_p.h"

#include <QLoggingCategory>

#include "bmconstants_p.h"

QT_BEGIN_NAMESPACE

BMStroke::BMStroke(const BMStroke &other)
    : BMShape(other)
{
    m_opacity = other.m_opacity;
    m_width = other.m_width;
    m_color = other.m_color;
    m_capStyle = other.m_capStyle;
    m_joinStyle = other.m_joinStyle;
    m_miterLimit = other.m_miterLimit;
    m_dashOffset = other.m_dashOffset;
    m_dashLength = other.m_dashLength;
    m_dashGap = other.m_dashGap;
    m_isDashed = other.m_isDashed;
}

BMStroke::BMStroke(const QJsonObject &definition, const QVersionNumber &version, BMBase *parent)
{
    setParent(parent);

    BMBase::parse(definition);
    if (m_hidden)
        return;

    qCDebug(lcLottieQtBodymovinParser) << "BMStroke::BMStroke()" << m_name;

    int lineCap = definition.value(QLatin1String("lc")).toVariant().toInt();
    switch (lineCap) {
    case 1:
        m_capStyle = Qt::FlatCap;
        break;
    case 2:
        m_capStyle = Qt::RoundCap;
        break;
    case 3:
        m_capStyle = Qt::SquareCap;
        break;
    default:
        qCDebug(lcLottieQtBodymovinParser) << "Unknown line cap style in BMStroke";
    }

    int lineJoin = definition.value(QLatin1String("lj")).toVariant().toInt();
    switch (lineJoin) {
    case 1:
        m_joinStyle = Qt::MiterJoin;
        m_miterLimit = definition.value(QLatin1String("ml")).toVariant().toReal();
        break;
    case 2:
        m_joinStyle = Qt::RoundJoin;
        break;
    case 3:
        m_joinStyle = Qt::BevelJoin;
        break;
    default:
        qCDebug(lcLottieQtBodymovinParser) << "Unknown line join style in BMStroke";
    }

    QJsonObject opacity = definition.value(QLatin1String("o")).toObject();
    opacity = resolveExpression(opacity);
    m_opacity.construct(opacity, version);

    QJsonObject width = definition.value(QLatin1String("w")).toObject();
    width = resolveExpression(width);
    m_width.construct(width, version);

    QJsonObject color = definition.value(QLatin1String("c")).toObject();
    color = resolveExpression(color);
    m_color.construct(color, version);

    QJsonArray dashes = definition.value(QLatin1String("d")).toArray();
    if (dashes.size()) {
        auto it = dashes.cend();
        while (it != dashes.cbegin()) {
            --it;
            QJsonObject dashSpec = it->toObject();
            QJsonObject val = resolveExpression(dashSpec.value(QLatin1String("v")).toObject());
            QString n = dashSpec.value(QLatin1String("n")).toString();
            if (n == QLatin1String("o"))
                m_dashOffset.construct(val, version);
            else if (n == QLatin1String("g"))
                m_dashGap.construct(val, version);
            else if (n == QLatin1String("d"))
                m_dashLength.construct(val, version);
        }
        m_isDashed = true;
    }
}

BMBase *BMStroke::clone() const
{
    return new BMStroke(*this);
}

void BMStroke::updateProperties(int frame)
{
    m_opacity.update(frame);
    m_width.update(frame);
    m_color.update(frame);
    if (m_isDashed) {
        m_dashOffset.update(frame);
        m_dashLength.update(frame);
        m_dashGap.update(frame);
    }
}

void BMStroke::render(LottieRenderer &renderer) const
{
    renderer.render(*this);
}

QPen BMStroke::pen() const
{
    qreal width = m_width.value();
    if (qFuzzyIsNull(width))
        return QPen(Qt::NoPen);
    QPen pen;
    pen.setColor(getColor());
    pen.setWidthF(width);
    pen.setCapStyle(m_capStyle);
    pen.setJoinStyle(m_joinStyle);
    pen.setMiterLimit(m_miterLimit);
    if (m_isDashed) {
        pen.setDashOffset(m_dashOffset.value() / width);
        pen.setDashPattern({m_dashLength.value() / width, m_dashGap.value() / width});
    }
    return pen;
}

QColor BMStroke::getColor() const
{
    QVector4D cVec = m_color.value();
    QColor color;
    qreal r = static_cast<qreal>(cVec.x());
    qreal g = static_cast<qreal>(cVec.y());
    qreal b = static_cast<qreal>(cVec.z());
    qreal a = static_cast<qreal>(cVec.w());
    color.setRgbF(r, g, b, a);
    return color;
}

qreal BMStroke::opacity() const
{
    return m_opacity.value();
}

QT_END_NAMESPACE
