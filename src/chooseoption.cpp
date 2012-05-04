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

    QLabel *questionLabel = new QLabel(tr(""));

    membersButton = new QPushButton;
    membersButton->setIcon(QIcon::fromTheme("help-about", QIcon(":/icons/64x64/help-about")));
    membersButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QLabel *membersLabel = new QLabel(tr("Modifica la informació dels &socis o afegeix-ne de nous"));

    cannabisButton = new QPushButton(tr("Consum de &cànnabis"), this);
    cannabisButton->setIcon(QIcon::fromTheme("help-about", QIcon(":/icons/64x64/help-about")));

    cansButton = new QPushButton(tr("Pots de &cànnabis"), this);
    cansButton->setIcon(QIcon::fromTheme("edit-clear-symbolic", QIcon(":/icons/16x16/edit-clear-symbolic")));

    othersButton = new QPushButton(tr("&Altres consums"), this);
    othersButton->setIcon(QIcon::fromTheme("edit-clear-symbolic", QIcon(":/icons/16x16/edit-clear-symbolic")));

    cashButton = new QPushButton(tr("Control de cai&xa"), this);
    cashButton->setIcon(QIcon::fromTheme("edit-clear-symbolic", QIcon(":/icons/16x16/edit-clear-symbolic")));

    quitButton = new QPushButton(tr("&Sortir"), this);
    quitButton->setIcon(QIcon::fromTheme("application-exit", QIcon(":/icons/48x48/application-exit")));

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(questionLabel, 0, 0, 0, 1);
    gridLayout->addWidget(membersButton, 1, 0);
    gridLayout->addWidget(membersLabel, 1, 1);

    setLayout(gridLayout);
}

void ChooseOption::setMyStyleSheet()
{
    setStyleSheet(
        "QPushButton { font-size: 18px; min-width: 50px; min-height: 30px; max-height: 60px; }"
        "QLabel { font-size: 18px; }"
        "QGroupBox { border: 2px solid gray; border-radius: 6px; }");
}
