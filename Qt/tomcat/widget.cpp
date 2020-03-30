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
    proc->start("ls");
    if(!proc->waitForFinished()){
        proc->close();
        ui->textEdit->setText("创建进程失败");
    }
    proc->close();
    ui->textEdit->setText("tomcat开启");
    delete proc;
}

void Widget::on_pushButton_2_clicked()
{
    //    QProcess::execute("pwd"); // 阻塞方式
    //    system("ls");
        QProcess *proc = new QProcess;
        proc->start("ls");
        if(!proc->waitForFinished()){
            proc->close();
            ui->textEdit->setText("创建进程失败");
        }
        proc->close();
        ui->textEdit->setText("tomcat关闭");
        delete proc;
}
