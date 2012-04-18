#ifndef CASHCONTROL_H
#define CASHCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>
#include <QMessageBox>
#include <QDateEdit>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPrinter>

class CashControl : public QWidget
{
    Q_OBJECT
public:
    explicit CashControl(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    // bool save(void);
    void clear(void);

protected:
    QDateEdit *dataInicial;
    QDateEdit *dataFinal;

    QTableView *tableView;

    QPushButton *printButton;

signals:
    
public slots:
    void onHelp();
    void onShow();
    void onPrint();

};

#endif // CASHCONTROL_H
