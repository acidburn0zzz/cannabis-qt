#ifndef CANNABIS_H
#define CANNABIS_H

#include <QWidget>
#include <QPushButton>
#include <QList>
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

class Cannabis : public QWidget
{
    Q_OBJECT
public:
    explicit Cannabis(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    bool save(bool showMessage=true);

protected:
    QLineEdit *filterLineEdit;

    QTableView *tableView;

    bool isDirty;

    void setDirtyFlag(bool status);

signals:
    
public slots:

    void addNewOrder();
    void deleteOrder();
    void onFilter();
    void onClearFilter();

    void onApply();
    void onCancel();
    void onHelp();

    void onDataChanged(QModelIndex , QModelIndex );
};

#endif // CANNABIS_H
