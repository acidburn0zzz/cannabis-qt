#ifndef CANS_H
#define CANS_H

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

class Cans : public QWidget
{
    Q_OBJECT
public:
    explicit Cans(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    bool save(void);

protected:
    QLineEdit *filterLineEdit;

    QTableView *tableView;

    bool isDirty;

    void setDirtyFlag(bool status);

signals:

public slots:

    void addNewCan();
    void deleteCan();
    void onFilter();

    void onApply();
    void onCancel();
    void onHelp();

    void onDataChanged(QModelIndex , QModelIndex );

};

#endif // CANS_H
