#include "mydateedit.h"

MyDateEdit::MyDateEdit(QObject *parent) :
    QItemDelegate(parent)
{
     this->setParent(parent);
}

QWidget * MyDateEdit::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *dateEdit = new QDateEdit(parent);

    QString dateStr = index.model()->data(index, Qt::EditRole).toString();

    QDate date(QDate::fromString(dateStr, "dd/MM/yyyy"));

    if (date.isNull())
    {
        date = date.currentDate();
    }

    dateEdit->setDate(date);
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    dateEdit->setCalendarPopup(true);

    return dateEdit;
}

void MyDateEdit::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString dateStr = index.model()->data(index, Qt::EditRole).toString();

    QDate date(QDate::fromString(dateStr,"dd/MM/yyyy"));

    QDateEdit * dateEdit = static_cast<QDateEdit *>(editor);

    dateEdit->setDate(date);
}

void MyDateEdit::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);

    dateEdit->interpretText();

    QString dateStr = dateEdit->date().toString("dd/MM/yyyy");

    model->setData(index, dateStr, Qt::EditRole);
}

void MyDateEdit::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
