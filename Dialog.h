#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QProcess>
#include <QUdpSocket>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btn_start_clicked();

    void on_btn_shutdown_clicked();

private:
    Ui::Dialog *ui;

    QUdpSocket m_sendMagicPacket;
    QProcess m_net;
    QProcess m_shutdown;
};

#endif // DIALOG_H
