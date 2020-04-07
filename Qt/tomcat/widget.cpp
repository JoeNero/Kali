#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
//    QProcess::execute("pwd"); // 阻塞方式
//    system("ls");
    QProcess *proc = new QProcess;
    proc->start("sudo sh open.sh");
    proc->start("pwd");
//    proc->start("pwd");
    if(!proc->waitForFinished()){
        proc->close();
        ui->textEdit->setText("open创建进程失败");
    }
    QString strResult = proc->readAllStandardOutput();
    proc->terminate();
    proc->close();
    ui->textEdit->setText(strResult);
    delete proc;
}

void Widget::on_pushButton_2_clicked()
{
    //    QProcess::execute("pwd"); // 阻塞方式
    //    system("ls");
        QProcess *proc = new QProcess;
        proc->start("sudo sh close.sh");
        proc->start("pwd");
    //    proc->start("pwd");
        if(!proc->waitForFinished()){
            proc->close();
            ui->textEdit->setText("close创建进程失败");
        }
        QString strResult = proc->readAllStandardOutput();
        proc->terminate();
        proc->close();
        ui->textEdit->setText(strResult);
        delete proc;
}
