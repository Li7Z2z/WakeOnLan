#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btn_start_clicked()
{
    QString strMac = ui->le_mac->text();
    QByteArray baMac = strMac.toLatin1();
    int size = 6;
    char chMac[9];
    char chMagicPacket[102];
    char *pMac = baMac.data();

    // 把Mac地址按照十六进制保存到数组中
    sscanf_s(pMac, "%2X-%2X-%2X-%2X-%2X-%2X", &chMac[0], &chMac[1], &chMac[2], &chMac[3], &chMac[4], &chMac[5]);

    // 制作封包
    memset(chMagicPacket, 0xFF, 6);
    for (int i = 0; i < 16; i++)
    {
        memcpy(chMagicPacket + size, chMac, 6);
        size += 6;
    }

    // 发送魔术封包
    m_sendMagicPacket.writeDatagram(chMagicPacket, 102, QHostAddress("192.168.0.255"), 50209);
}

void Dialog::on_btn_shutdown_clicked()
{
    QString ip          = ui->le_ip->text();
    QString user        = ui->le_user->text();
    QString password    = ui->le_password->text();
    QString cmd1        = QString("net use \\\\%1 %2 /user:%3").arg(ip, password, user);
    QString cmd2        = QString("shutdown -s -t 100 -m \\\\%1").arg(ip);
    m_net.start(cmd1);
    m_shutdown.start(cmd2);

    m_net.terminate();
    m_shutdown.terminate();

//    m_cmd.waitForStarted();
//    m_cmd.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(m_cmd.readAllStandardOutput());
}
