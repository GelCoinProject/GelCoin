<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "csvmodelwriter.h"

#include <QAbstractItemModel>
#include <QFile>
#include <QTextStream>

<<<<<<< HEAD
CSVModelWriter::CSVModelWriter(const QString &filename, QObject *parent) :
    QObject(parent),
    filename(filename), model(0)
{
}

void CSVModelWriter::setModel(const QAbstractItemModel *model)
=======
CSVModelWriter::CSVModelWriter(const QString& filename, QObject* parent) : QObject(parent),
                                                                           filename(filename), model(0)
{
}

void CSVModelWriter::setModel(const QAbstractItemModel* model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->model = model;
}

<<<<<<< HEAD
void CSVModelWriter::addColumn(const QString &title, int column, int role)
=======
void CSVModelWriter::addColumn(const QString& title, int column, int role)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Column col;
    col.title = title;
    col.column = column;
    col.role = role;

    columns.append(col);
}

<<<<<<< HEAD
static void writeValue(QTextStream &f, const QString &value)
=======
static void writeValue(QTextStream& f, const QString& value)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QString escaped = value;
    escaped.replace('"', "\"\"");
    f << "\"" << escaped << "\"";
}

<<<<<<< HEAD
static void writeSep(QTextStream &f)
=======
static void writeSep(QTextStream& f)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    f << ",";
}

<<<<<<< HEAD
static void writeNewline(QTextStream &f)
=======
static void writeNewline(QTextStream& f)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    f << "\n";
}

bool CSVModelWriter::write()
{
    QFile file(filename);
<<<<<<< HEAD
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
=======
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    QTextStream out(&file);

    int numRows = 0;
<<<<<<< HEAD
    if(model)
    {
=======
    if (model) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        numRows = model->rowCount();
    }

    // Header row
<<<<<<< HEAD
    for(int i=0; i<columns.size(); ++i)
    {
        if(i!=0)
        {
=======
    for (int i = 0; i < columns.size(); ++i) {
        if (i != 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            writeSep(out);
        }
        writeValue(out, columns[i].title);
    }
    writeNewline(out);

    // Data rows
<<<<<<< HEAD
    for(int j=0; j<numRows; ++j)
    {
        for(int i=0; i<columns.size(); ++i)
        {
            if(i!=0)
            {
=======
    for (int j = 0; j < numRows; ++j) {
        for (int i = 0; i < columns.size(); ++i) {
            if (i != 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                writeSep(out);
            }
            QVariant data = model->index(j, columns[i].column).data(columns[i].role);
            writeValue(out, data.toString());
        }
        writeNewline(out);
    }

    file.close();

    return file.error() == QFile::NoError;
}
