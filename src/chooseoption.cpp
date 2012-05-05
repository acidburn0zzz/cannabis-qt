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

#include "chooseoption.h"

ChooseOption::ChooseOption(QWidget *parent) :
    QWidget(parent)
{
    setMyStyleSheet();

    this->setPalette(QPalette(Qt::white));
    this->setAutoFillBackground(true);

    QString htmlTitle("<h1>%1</h1>\n<h3><font color='grey'>%2</font></h3>");

    QLabel *questionLabel = new QLabel(htmlTitle.arg(tr("Benvingut a Cannabis-qt!"), tr("Què vols fer?")), this);
    questionLabel->setAlignment(Qt::AlignCenter);
    //questionLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString html("<h2>%1</h2>\n<h4><font color='grey'>%2</font></h4>");

    buttons["members"] = new QPushButton(this);
    buttons["members"]->setIcon(QIcon::fromTheme("notification-message-im", QIcon(":/icons/48x48/notification-message-im")));
    buttons["members"]->setIconSize(QSize(48,48));
    buttons["members"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["members"] = new QLabel(html.arg(tr("Socis"), tr("Modifica la informació dels socis")), this);

    buttons["cannabis"] = new QPushButton(this);
    buttons["cannabis"]->setIcon(QIcon(":/icons/leaf-icon"));
    buttons["cannabis"]->setIconSize(QSize(48,48));
    buttons["cannabis"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["cannabis"] = new QLabel(html.arg(tr("Cànnabis"), tr("Controla el consum de cànnabis")), this);

    buttons["cans"] = new QPushButton(this);
    buttons["cans"]->setIcon(QIcon(":/icons/container"));
    buttons["cans"]->setIconSize(QSize(48,48));
    buttons["cans"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["cans"] = new QLabel(html.arg(tr("Pots"), tr("Controla els pots de cànnabis")), this);

    buttons["others"] = new QPushButton(this);
    buttons["others"]->setIcon(QIcon(":/icons/others"));
    buttons["others"]->setIconSize(QSize(48,48));
    buttons["others"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["others"] = new QLabel(html.arg(tr("Altres"), tr("Registra altres consums")), this);

    buttons["cash"] = new QPushButton(this);
    buttons["cash"]->setIcon(QIcon(":/icons/cashbox"));
    buttons["cash"]->setIconSize(QSize(48,48));
    buttons["cash"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["cash"] = new QLabel(html.arg(tr("Caixa"), tr("Extreu un resum de l'estat de la caixa")), this);

    buttons["quit"] = new QPushButton(this);
    buttons["quit"]->setIcon(QIcon::fromTheme("application-exit", QIcon(":/icons/48x48/application-exit")));
    buttons["quit"]->setIconSize(QSize(48,48));
    buttons["quit"]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labels["quit"] = new QLabel(html.arg(tr("Sortir"), tr("Tanca l'aplicació")), this);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(questionLabel, 0, Qt::AlignCenter);

    QHBoxLayout *hbox;

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["members"]);
    hbox->addWidget( labels["members"]);
    layout->addLayout(hbox);

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["cannabis"]);
    hbox->addWidget( labels["cannabis"]);
    layout->addLayout(hbox);

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["cans"]);
    hbox->addWidget( labels["cans"]);
    layout->addLayout(hbox);

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["others"]);
    hbox->addWidget( labels["others"]);
    layout->addLayout(hbox);

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["cash"]);
    hbox->addWidget( labels["cash"]);
    layout->addLayout(hbox);

    hbox = new QHBoxLayout;
    hbox->addWidget(buttons["quit"]);
    hbox->addWidget( labels["quit"]);
    layout->addLayout(hbox);

    /*
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(questionLabel, 0, 0, 1, -1, Qt::AlignCenter);

    layout->addWidget(buttons["members"], 1, 0, Qt::AlignRight);
    layout->addWidget( labels["members"], 1, 1);

    layout->addWidget(buttons["cannabis"], 2, 0, Qt::AlignRight);
    layout->addWidget( labels["cannabis"], 2, 1);
    layout->addWidget(buttons["cans"], 3, 0, Qt::AlignRight);
    layout->addWidget( labels["cans"], 3, 1);
    layout->addWidget(buttons["others"], 4, 0, Qt::AlignRight);
    layout->addWidget( labels["others"], 4, 1);
    layout->addWidget(buttons["cash"], 5, 0, Qt::AlignRight);
    layout->addWidget( labels["cash"], 5, 1);
    layout->addWidget(buttons["quit"], 6, 0, Qt::AlignRight);
    layout->addWidget( labels["quit"], 6, 1);

    // layout->setColumnStretch(1, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setRowStretch(4, 1);
    layout->setRowStretch(5, 1);
    layout->setRowStretch(6, 1);
    */

    /*
    QMap <QString, QPushButton *>::const_iterator button = buttons.constBegin();
    QMap <QString, QLabel *>::const_iterator label = labels.constBegin();

    for (int row=0; row < buttons.size(); row++)
    {
        gridLayout->addWidget(button.value(), row+1, 0);
        gridLayout->addWidget(label.value(), row+1, 1);
    }
    */

    // center our layout
    QHBoxLayout *hbox0 = new QHBoxLayout;

    hbox0->addStretch(1);
    hbox0->addLayout(layout);
    hbox0->addStretch(1);
    setLayout(hbox0);

    // setLayout(layout);
}

void ChooseOption::setMyStyleSheet()
{
    setStyleSheet(
        "QPushButton { font-size: 18px; min-width: 50px; min-height: 50px; }" // max-height: 60px; }"
        "QLabel { font-size: 12px; }"
        "QGroupBox { border: 2px solid gray; border-radius: 6px; }");
}
