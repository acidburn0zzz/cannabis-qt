#ifndef MEMBERS_H
#define MEMBERS_H

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
#include <QInputDialog>

class Members : public QWidget
{
    Q_OBJECT
public:
    explicit Members(QWidget *parent = 0);

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
    void addNewMember();
    void deleteMember();
    void onFilter();
    void onClearFilter();

    void onApply();
    void onCancel();
    void onHelp();

    void onDataChanged(QModelIndex , QModelIndex );
};

#endif // MEMBERS_H
