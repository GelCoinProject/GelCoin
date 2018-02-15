<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TRAFFICGRAPHWIDGET_H
#define BITCOIN_QT_TRAFFICGRAPHWIDGET_H

<<<<<<< HEAD
#include "trafficgraphdata.h"

#include <boost/function.hpp>

#include <QWidget>
#include <QQueue>
=======
#include <QQueue>
#include <QWidget>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class ClientModel;

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QTimer;
QT_END_NAMESPACE

class TrafficGraphWidget : public QWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit TrafficGraphWidget(QWidget *parent = 0);
    void setClientModel(ClientModel *model);
    int getGraphRangeMins() const;

protected:
    void paintEvent(QPaintEvent *);

public Q_SLOTS:
    void updateRates();
    void setGraphRangeMins(int value);
    void clear();

private:
    typedef boost::function<float(const TrafficSample&)> SampleChooser;
    void paintPath(QPainterPath &path, const TrafficGraphData::SampleQueue &queue, SampleChooser chooser);

    QTimer *timer;
    float fMax;
    int nMins;
    ClientModel *clientModel;
    TrafficGraphData trafficGraphData;
=======
    explicit TrafficGraphWidget(QWidget* parent = 0);
    void setClientModel(ClientModel* model);
    int getGraphRangeMins() const;

protected:
    void paintEvent(QPaintEvent*);

public slots:
    void updateRates();
    void setGraphRangeMins(int mins);
    void clear();

private:
    void paintPath(QPainterPath& path, QQueue<float>& samples);

    QTimer* timer;
    float fMax;
    int nMins;
    QQueue<float> vSamplesIn;
    QQueue<float> vSamplesOut;
    quint64 nLastBytesIn;
    quint64 nLastBytesOut;
    ClientModel* clientModel;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_TRAFFICGRAPHWIDGET_H
