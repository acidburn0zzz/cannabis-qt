#ifndef CANNABIS_H
#define CANNABIS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>
#include <QMessageBox>

class Cannabis : public QWidget
{
    Q_OBJECT
public:
    explicit Cannabis(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    bool save(void);

protected:
    QLineEdit *filterLineEdit;

    QTableView *tableView;

signals:
    
public slots:

    void addNewOrder();
    void deleteOrder();
    void onFilter();

    void onCancel();
    void onHelp();

};

#endif // MEMBERS_H
