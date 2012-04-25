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

#include "mydateeditdelegate.h"

MyDateEditDelegate::MyDateEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
     this->setParent(parent);
}

QWidget * MyDateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *dateEdit = new QDateEdit(parent);

    QString dateStr = index.model()->data(index, Qt::EditRole).toString();

    // QDate date(QDate::fromString(dateStr, "dd/MM/yyyy"));
    QDate date(QDate::fromString(dateStr, "yyyyMMdd"));

    if (date.isNull())
    {
        date = date.currentDate();
    }

    dateEdit->setDate(date);
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    dateEdit->setCalendarPopup(true);

    return dateEdit;
}

void MyDateEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString dateStr = index.model()->data(index, Qt::EditRole).toString();

    // QDate date(QDate::fromString(dateStr,"dd/MM/yyyy"));
    QDate date(QDate::fromString(dateStr, "yyyyMMdd"));

    QDateEdit * dateEdit = static_cast<QDateEdit *>(editor);

    dateEdit->setDate(date);
    dateEdit->setDisplayFormat("dd/MM/yyyy");
}

void MyDateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);

    dateEdit->interpretText();

    QString dateStr = dateEdit->date().toString("yyyyMMdd");

    model->setData(index, dateStr, Qt::EditRole);

}

void MyDateEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void MyDateEditDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.isValid())
    {
        QString dateStr = index.data().toString();

        QDate date(QDate::fromString(dateStr, "yyyyMMdd"));

        dateStr = date.toString("dd/MM/yyyy");

        QFontMetrics fm(painter->fontMetrics());

        QRect r(option.rect);

        r.adjust(2, (option.rect.height() - fm.height()) / 2, 0, 0);

        painter->drawText(r, dateStr);
    }
}
