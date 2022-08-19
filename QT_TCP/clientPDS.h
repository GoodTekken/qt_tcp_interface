#ifndef CLIENTPDS_H
#define CLIENTPDS_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

#include "AGVMessage/AgvExternalPara.h"
#include "PDS_protocol/PalletRequestClass.h"
#include "Spline/ExternalPathCoordinateSet.h"
#include "Math/UserMatrix.h"
#include "main.h"

//#define qtcout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]";

namespace Ui {
class ClientPDS;
}

class ClientPDS : public QWidget
{
    Q_OBJECT

public:
    explicit ClientPDS(QWidget *parent = nullptr);
    ~ClientPDS();


private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonEnter_clicked();

    void on_pushButtonLeave_clicked();

private:
    Ui::ClientPDS *ui;

    QTcpSocket *tcpSocket;
};

#endif // CLIENTPDS_H
