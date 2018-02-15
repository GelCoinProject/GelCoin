<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "trafficgraphwidget.h"
#include "clientmodel.h"

<<<<<<< HEAD
#include <boost/bind.hpp>

#include <QPainter>
#include <QColor>
=======
#include <QColor>
#include <QPainter>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QTimer>

#include <cmath>

<<<<<<< HEAD
#define XMARGIN                 10
#define YMARGIN                 10

#define DEFAULT_SAMPLE_HEIGHT    1.1f

TrafficGraphWidget::TrafficGraphWidget(QWidget *parent) :
    QWidget(parent),
    timer(0),
    fMax(DEFAULT_SAMPLE_HEIGHT),
    nMins(0),
    clientModel(0),
    trafficGraphData(TrafficGraphData::Range_30m)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updateRates()));
    timer->setInterval(TrafficGraphData::SMALLEST_SAMPLE_PERIOD);
    timer->start();
}

void TrafficGraphWidget::setClientModel(ClientModel *model)
{
    clientModel = model;
    if(model) {
        trafficGraphData.setLastBytes(model->getTotalBytesRecv(), model->getTotalBytesSent());
=======
#define DESIRED_SAMPLES 800

#define XMARGIN 10
#define YMARGIN 10

TrafficGraphWidget::TrafficGraphWidget(QWidget* parent) : QWidget(parent),
                                                          timer(0),
                                                          fMax(0.0f),
                                                          nMins(0),
                                                          vSamplesIn(),
                                                          vSamplesOut(),
                                                          nLastBytesIn(0),
                                                          nLastBytesOut(0),
                                                          clientModel(0)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updateRates()));
}

void TrafficGraphWidget::setClientModel(ClientModel* model)
{
    clientModel = model;
    if (model) {
        nLastBytesIn = model->getTotalBytesRecv();
        nLastBytesOut = model->getTotalBytesSent();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

int TrafficGraphWidget::getGraphRangeMins() const
{
    return nMins;
}

<<<<<<< HEAD

void TrafficGraphWidget::paintPath(QPainterPath &path, const TrafficGraphData::SampleQueue &queue, SampleChooser chooser)
{
    int h = height() - YMARGIN * 2, w = width() - XMARGIN * 2;
    int sampleCount = queue.size(), x = XMARGIN + w, y;
    if(sampleCount > 0) {
        path.moveTo(x, YMARGIN + h);
        for(int i = 0; i < sampleCount; ++i) {
            x = XMARGIN + w - w * i / TrafficGraphData::DESIRED_DATA_SAMPLES;
            y = YMARGIN + h - (int)(h * chooser(queue.at(i)) / fMax);
=======
void TrafficGraphWidget::paintPath(QPainterPath& path, QQueue<float>& samples)
{
    int h = height() - YMARGIN * 2, w = width() - XMARGIN * 2;
    int sampleCount = samples.size(), x = XMARGIN + w, y;
    if (sampleCount > 0) {
        path.moveTo(x, YMARGIN + h);
        for (int i = 0; i < sampleCount; ++i) {
            x = XMARGIN + w - w * i / DESIRED_SAMPLES;
            y = YMARGIN + h - (int)(h * samples.at(i) / fMax);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            path.lineTo(x, y);
        }
        path.lineTo(x, YMARGIN + h);
    }
}

<<<<<<< HEAD
namespace
{
    float chooseIn(const TrafficSample& sample)
    {
        return sample.in;
    }
    float chooseOut(const TrafficSample& sample)
    {
        return sample.out;
    }
}

void TrafficGraphWidget::paintEvent(QPaintEvent *)
=======
void TrafficGraphWidget::paintEvent(QPaintEvent*)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

<<<<<<< HEAD
    if(fMax <= 0.0f) return;
=======
    if (fMax <= 0.0f) return;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QColor axisCol(Qt::gray);
    int h = height() - YMARGIN * 2;
    painter.setPen(axisCol);
    painter.drawLine(XMARGIN, YMARGIN + h, width() - XMARGIN, YMARGIN + h);

    // decide what order of magnitude we are
    int base = floor(log10(fMax));
    float val = pow(10.0f, base);

<<<<<<< HEAD
    const QString units     = tr("KB/s");
    const float yMarginText = 2.0;
    
    // draw lines
    painter.setPen(axisCol);
    painter.drawText(XMARGIN, YMARGIN + h - h * val / fMax-yMarginText, QString("%1 %2").arg(val).arg(units));
    for(float y = val; y < fMax; y += val) {
=======
    const QString units = tr("KB/s");
    const float yMarginText = 2.0;

    // draw lines
    painter.setPen(axisCol);
    painter.drawText(XMARGIN, YMARGIN + h - h * val / fMax - yMarginText, QString("%1 %2").arg(val).arg(units));
    for (float y = val; y < fMax; y += val) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        int yy = YMARGIN + h - h * y / fMax;
        painter.drawLine(XMARGIN, yy, width() - XMARGIN, yy);
    }
    // if we drew 3 or fewer lines, break them up at the next lower order of magnitude
<<<<<<< HEAD
    if(fMax / val <= 3.0f) {
        axisCol = axisCol.darker();
        val = pow(10.0f, base - 1);
        painter.setPen(axisCol);
        painter.drawText(XMARGIN, YMARGIN + h - h * val / fMax-yMarginText, QString("%1 %2").arg(val).arg(units));
        int count = 1;
        for(float y = val; y < fMax; y += val, count++) {
            // don't overwrite lines drawn above
            if(count % 10 == 0)
=======
    if (fMax / val <= 3.0f) {
        axisCol = axisCol.darker();
        val = pow(10.0f, base - 1);
        painter.setPen(axisCol);
        painter.drawText(XMARGIN, YMARGIN + h - h * val / fMax - yMarginText, QString("%1 %2").arg(val).arg(units));
        int count = 1;
        for (float y = val; y < fMax; y += val, count++) {
            // don't overwrite lines drawn above
            if (count % 10 == 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                continue;
            int yy = YMARGIN + h - h * y / fMax;
            painter.drawLine(XMARGIN, yy, width() - XMARGIN, yy);
        }
    }

<<<<<<< HEAD
    const TrafficGraphData::SampleQueue& queue = trafficGraphData.getCurrentRangeQueueWithAverageBandwidth();

    if(!queue.empty()) {
        QPainterPath pIn;
        paintPath(pIn, queue, boost::bind(chooseIn,_1));
        painter.fillPath(pIn, QColor(0, 255, 0, 128));
        painter.setPen(Qt::green);
        painter.drawPath(pIn);

        QPainterPath pOut;
        paintPath(pOut, queue, boost::bind(chooseOut,_1));
        painter.fillPath(pOut, QColor(255, 0, 0, 128));
        painter.setPen(Qt::red);
        painter.drawPath(pOut);
=======
    if (!vSamplesIn.empty()) {
        QPainterPath p;
        paintPath(p, vSamplesIn);
        painter.fillPath(p, QColor(0, 255, 0, 128));
        painter.setPen(Qt::green);
        painter.drawPath(p);
    }
    if (!vSamplesOut.empty()) {
        QPainterPath p;
        paintPath(p, vSamplesOut);
        painter.fillPath(p, QColor(255, 0, 0, 128));
        painter.setPen(Qt::red);
        painter.drawPath(p);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void TrafficGraphWidget::updateRates()
{
<<<<<<< HEAD
    if(!clientModel) return;

    bool updated = trafficGraphData.update(clientModel->getTotalBytesRecv(),clientModel->getTotalBytesSent());

    if (updated){
        float tmax = DEFAULT_SAMPLE_HEIGHT;
        Q_FOREACH(const TrafficSample& sample, trafficGraphData.getCurrentRangeQueueWithAverageBandwidth()) {
            if(sample.in > tmax) tmax = sample.in;
            if(sample.out > tmax) tmax = sample.out;
        }
        fMax = tmax;
        update();
    }
}

void TrafficGraphWidget::setGraphRangeMins(int value)
{
    trafficGraphData.switchRange(static_cast<TrafficGraphData::GraphRange>(value));
    update();
=======
    if (!clientModel) return;

    quint64 bytesIn = clientModel->getTotalBytesRecv(),
            bytesOut = clientModel->getTotalBytesSent();
    float inRate = (bytesIn - nLastBytesIn) / 1024.0f * 1000 / timer->interval();
    float outRate = (bytesOut - nLastBytesOut) / 1024.0f * 1000 / timer->interval();
    vSamplesIn.push_front(inRate);
    vSamplesOut.push_front(outRate);
    nLastBytesIn = bytesIn;
    nLastBytesOut = bytesOut;

    while (vSamplesIn.size() > DESIRED_SAMPLES) {
        vSamplesIn.pop_back();
    }
    while (vSamplesOut.size() > DESIRED_SAMPLES) {
        vSamplesOut.pop_back();
    }

    float tmax = 0.0f;
    foreach (float f, vSamplesIn) {
        if (f > tmax) tmax = f;
    }
    foreach (float f, vSamplesOut) {
        if (f > tmax) tmax = f;
    }
    fMax = tmax;
    update();
}

void TrafficGraphWidget::setGraphRangeMins(int mins)
{
    nMins = mins;
    int msecsPerSample = nMins * 60 * 1000 / DESIRED_SAMPLES;
    timer->stop();
    timer->setInterval(msecsPerSample);

    clear();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void TrafficGraphWidget::clear()
{
<<<<<<< HEAD
    trafficGraphData.clear();
    fMax = DEFAULT_SAMPLE_HEIGHT;
    if(clientModel) {
        trafficGraphData.setLastBytes(clientModel->getTotalBytesRecv(), clientModel->getTotalBytesSent());
    }
    update();
=======
    timer->stop();

    vSamplesOut.clear();
    vSamplesIn.clear();
    fMax = 0.0f;

    if (clientModel) {
        nLastBytesIn = clientModel->getTotalBytesRecv();
        nLastBytesOut = clientModel->getTotalBytesSent();
    }
    timer->start();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
