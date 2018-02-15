<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_CSVMODELWRITER_H
#define BITCOIN_QT_CSVMODELWRITER_H

#include <QList>
#include <QObject>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

/** Export a Qt table model to a CSV file. This is useful for analyzing or post-processing the data in
    a spreadsheet.
 */
class CSVModelWriter : public QObject
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit CSVModelWriter(const QString &filename, QObject *parent = 0);

    void setModel(const QAbstractItemModel *model);
    void addColumn(const QString &title, int column, int role=Qt::EditRole);
=======
    explicit CSVModelWriter(const QString& filename, QObject* parent = 0);

    void setModel(const QAbstractItemModel* model);
    void addColumn(const QString& title, int column, int role = Qt::EditRole);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Perform export of the model to CSV.
        @returns true on success, false otherwise
    */
    bool write();

private:
    QString filename;
<<<<<<< HEAD
    const QAbstractItemModel *model;

    struct Column
    {
=======
    const QAbstractItemModel* model;

    struct Column {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        QString title;
        int column;
        int role;
    };
    QList<Column> columns;
};

#endif // BITCOIN_QT_CSVMODELWRITER_H
