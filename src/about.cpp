#include "about.h"
#include "constants.h"

About::About(QWidget *parent) :
    QDialog(parent)
{
    QLabel *label = new QLabel(
     tr("Sobre Cannabis-qt"
        "<b>Cannabis-qt</b> és un senzill programa de gestió d'un local social "
           "on es pugui dispensar cànnabis mitjançant un control estricte.<br/><br/>"
           "El programa està fet amb les llibreríes QT : <a href='http://qt.nokia.com'>qt.nokia.com</a><br/><br/>"
           "La web del programa : <a href='http://karasu.github.com/cannabis-qt'>karasu.github.com/cannabis-qt</a><br/><br/>"
           "El programa permet:<br/><br/>"
           "\t- Gestionar els socis<br/>"
           "\t- Gestionar els pots de cànnabis<br/>"
           "\t- Gestionar el consum dels socis (ja sigui del consum propi de cànnabis o d'altres col·laboracions amb l'associació<br/>"
           "\t- Controlar els ingressos de l'associació i imprimir informes per portar al gestor<br/>"
           "\t- Importació i exportació de les dades (SQLITE)<br/><br/>"
           "Versió %1<br/>"
           "Fet per Karasu.<br/>").arg(PROGRAM_VERSION));

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(pressed()), this, SLOT(onClose()));
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *licenseButton = new QPushButton(tr("License"));
    connect(licenseButton, SIGNAL(pressed()), this, SLOT(showLicense()));
    licenseButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(licenseButton);
    hbox->addWidget(closeButton);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);

    vbox->addLayout(hbox);

    setLayout(vbox);
}

void About::showLicense()
{
    QMessageBox::about(this, tr("About cannabis-qt"),

                tr("Licència:<br />"
                "Cannabis-qt<br />"
                "Copyright (C) 2012 Karasu<br /><br />"
                "This program is free software: you can redistribute it and/or modify "
                "it under the terms of the GNU General Public License as published by "
                "the Free Software Foundation, either version 3 of the License, or "
                "any later version.<br /><br />"
                "This program is distributed in the hope that it will be useful, "
                "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                "GNU General Public License for more details.<br /><br />"
                "You should have received a copy of the GNU General Public License "
                "along with this program.  If not, see <a href='http://www.gnu.org/licenses/'>www.gnu.org</a>."));
}

void About::onClose()
{
    this->close();
}
