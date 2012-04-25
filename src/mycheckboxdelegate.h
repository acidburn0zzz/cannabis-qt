/*
    Cannabis-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MYCHECKBOXDELEGATE_H
#define MYCHECKBOXDELEGATE_H

#include <QApplication>
#include <QMouseEvent>
#include <QStyledItemDelegate>

class MyCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyCheckBoxDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);
signals:
    
public slots:
    
};

#endif // MYCHECKBOXDELEGATE_H
