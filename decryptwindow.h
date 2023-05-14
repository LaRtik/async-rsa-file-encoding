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

private:
    Ui::DecryptWindow *ui;
};

#endif // DECRYPTWINDOW_H
