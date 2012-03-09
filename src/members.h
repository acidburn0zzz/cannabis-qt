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

class Members : public QWidget
{
    Q_OBJECT
public:
    explicit Members(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    bool save(void);

protected:
    QLineEdit *filterLineEdit;

    QTableView *tableView;

    bool isDirty;

signals:
    
public slots:
    void addNewMember();
    void deleteMember();
    void onFilter();

    void onCancel();
    void onHelp();

    void onDataChanged(QModelIndex , QModelIndex );
};

#endif // MEMBERS_H
