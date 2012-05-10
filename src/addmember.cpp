#include "addmember.h"

AddMember::AddMember(QWidget *parent) :
    QDialog(parent)
{
    model = NULL;
/*
    QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Name:"), nameLineEdit);
        formLayout->addRow(tr("&Email:"), emailLineEdit);
        formLayout->addRow(tr("&Age:"), ageSpinBox);
        setLayout(formLayout);
*/
}

void AddMember::setModel(QSqlTableModel *model)
{
    this->model = model;
}
