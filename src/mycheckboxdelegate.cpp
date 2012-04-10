#include "mycheckboxdelegate.h"

MyCheckBoxDelegate::MyCheckBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

static QRect CheckBoxRect(const QStyleOptionViewItem &style)
{
  QStyleOptionButton check_box_style_option;

  QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &check_box_style_option);

  QPoint checkBoxPoint(style.rect.x() +
                         style.rect.width() / 2 -
                         checkBoxRect.width() / 2,
                         style.rect.y() +
                         style.rect.height() / 2 -
                         checkBoxRect.height() / 2);

  return QRect(checkBoxPoint, checkBoxRect.size());
}


void MyCheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton style;

    style.state |= QStyle::State_Enabled;

    if (checked)
    {
        style.state |= QStyle::State_On;
    }
    else
    {
        style.state |= QStyle::State_Off;
    }

    style.rect = CheckBoxRect(option);

    QApplication::style()->drawControl(QStyle::CE_CheckBox, &style, painter);
}


// This is essentially copied from QStyledItemEditor, except that we
// have to determine our own "hot zone" for the mouse click.
bool MyCheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
  if ((event->type() == QEvent::MouseButtonRelease) ||
      (event->type() == QEvent::MouseButtonDblClick))
  {
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

    if (mouse_event->button() != Qt::LeftButton ||
        !CheckBoxRect(option).contains(mouse_event->pos()))
    {
      return false;
    }

    if (event->type() == QEvent::MouseButtonDblClick)
    {
      return true;
    }
  }
  else if (event->type() == QEvent::KeyPress)
  {
    if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
        static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
    {
      return false;
    }
  }
  else
  {
    return false;
  }

  bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

  return model->setData(index, !checked, Qt::EditRole);
}
