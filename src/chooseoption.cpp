#include "chooseoption.h"

ChooseOption::ChooseOption(QWidget *parent) :
    QWidget(parent)
{
    setMyStyleSheet();

    membersButton = new QPushButton(tr("Modifica la informació dels &socis o afegeix-ne de nous"), this);
    cannabisButton = new QPushButton(tr("Consum de &cànnabis"), this);
    cansButton = new QPushButton(tr("Pots de &cànnabis"), this);
    othersButton = new QPushButton(tr("&Altres consums"), this);
    cashButton = new QPushButton(tr("Control de cai&xa"), this);
    quitButton = new QPushButton(tr("&Sortir"), this);

    // cashButton->setHidden(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(membersButton);
    vbox->addWidget(cannabisButton);
    vbox->addWidget(cansButton);
    vbox->addWidget(othersButton);
    vbox->addWidget(cashButton);
    vbox->addWidget(quitButton);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(vbox);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(groupBox);

    setLayout(vbox2);
}

void ChooseOption::setMyStyleSheet()
{
    setStyleSheet("QPushButton {"
            "color: white;"
            "background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #44d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);"
            "border-width: 1px;"
            "border-color: #339;"
            "border-style: solid;"
            "border-radius: 7;"
            "padding: 3px;"
            "font-size: 18px;"
            "padding-left: 5px;"
            "padding-right: 5px;"
            "min-width: 50px;"
            // "max-width: 10px;"
            "min-height: 30px;"
            "max-height: 60px; }"
        "QGroupBox { border: 2px solid gray; border-radius: 6px; }");
}
