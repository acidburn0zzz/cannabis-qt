#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);
    
signals:
    
public slots:

    void showLicense();

};

#endif // ABOUT_H
