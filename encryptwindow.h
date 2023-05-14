#ifndef ENCRYPTWINDOW_H
#define ENCRYPTWINDOW_H

#include <QDialog>

namespace Ui {
class EncryptWindow;
}

class EncryptWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EncryptWindow(QWidget *parent = nullptr);
    ~EncryptWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EncryptWindow *ui;
};

#endif // ENCRYPTWINDOW_H
