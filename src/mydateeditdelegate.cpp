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
