#ifndef DECRYPTWINDOW_H
#define DECRYPTWINDOW_H

#include <QDialog>

namespace Ui {
class DecryptWindow;
}

class DecryptWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DecryptWindow(QWidget *parent = nullptr);
    ~DecryptWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DecryptWindow *ui;
};

#endif // DECRYPTWINDOW_H
