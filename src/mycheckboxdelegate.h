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
