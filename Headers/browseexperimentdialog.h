#ifndef BROWSEEXPERIMENTDIALOG_H
#define BROWSEEXPERIMENTDIALOG_H

#include <QDialog>

namespace Ui {
class BrowseExperimentDialog;
}

class BrowseExperimentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrowseExperimentDialog(QWidget *parent = nullptr);
    ~BrowseExperimentDialog();

private:
    Ui::BrowseExperimentDialog *ui;
};

#endif // BROWSEEXPERIMENTDIALOG_H
