#include "chooseoption.h"

ChooseOption::ChooseOption(QWidget *parent) :
    QWidget(parent)
{
    membersButton = new QPushButton(tr("Modifica la informació dels &socis o afegeix-ne de nous"), this);
    cannabisButton = new QPushButton(tr("Consum de &cannabis"), this);
    othersButton = new QPushButton(tr("&Altres consums"), this);
    cashButton = new QPushButton(tr("Control de cai&xa"), this);
    quitButton = new QPushButton(tr("&Sortir"), this);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(membersButton);
    vbox->addWidget(cannabisButton);
    vbox->addWidget(othersButton);
    vbox->addWidget(cashButton);
    vbox->addWidget(quitButton);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(vbox);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(groupBox);

    setLayout(vbox2);
}
