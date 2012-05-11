#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDialog>
#include <QFormLayout>
#include <QSqlTableModel>
#include <QLineEdit>
#include <QDate>
#include <QDateEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QDialogButtonBox>

class AddMember : public QDialog
{
    Q_OBJECT
public:
    explicit AddMember(QWidget *parent = 0);
    
    void setModel (QSqlTableModel *model);

protected:
    QSqlTableModel *model;

signals:
    
public slots:
    
};

#endif // ADDMEMBER_H
