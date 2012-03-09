#ifndef CHOOSEOPTION_H
#define CHOOSEOPTION_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

class ChooseOption : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseOption(QWidget *parent = 0);

    QPushButton *membersButton;
    QPushButton *quitButton;
    QPushButton *cannabisButton;
    QPushButton *othersButton;
    QPushButton *cashButton;

protected:
    void setMyStyleSheet(void);

signals:
    
public slots:
};

#endif // CHOOSEOPTION_H
