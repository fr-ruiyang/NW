#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#define M 3
#define D -1
#define DI -2

using namespace std;

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

QString s1,s2;
//struct point
//{
//    //分数
//    int score;
//    //指向的坐标
//    int i;
//    int j;
//};

/*打分规则
 *  匹配=3
 *  错配=-1
 *  空位=-2
*/

int max_flag(int a,int b,int c)
{
    if (c>=a&&c>=b)
        return 3;
    else if (a>=b&&a>=c)
        return 1;
    else
        return 2;
}

void Widget::on_pushButton_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择文件"),
                                          "",
                                          tr("所有文件(*.*)"));

    if(filename.isEmpty())
    {
         return;
    }
    else
    {
        ui->lineEdit->setText(filename);
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) //加载文件
        {
            QMessageBox::warning(this,
                                     tr("警告"),
                                     tr("打开文件失败!"));
            return;
        }
//        file.readLine();
        s1=QString(file.readAll());
        s1.remove(QChar('\n'));
        ui->textBrowser->append(tr("S1串为："));
        ui->textBrowser->append(s1);
    }
}

void Widget::on_pushButton_2_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择文件"),
                                          "",
                                          tr("所有文件(*.*)"));

    if(filename.isEmpty())
    {
         return;
    }
    else
    {
        ui->lineEdit_2->setText(filename);
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) //加载文件
        {
            QMessageBox::warning(this,
                                     tr("警告"),
                                     tr("打开文件失败!"));
            return;
        }
//        file.readLine();
        s2=QString(file.readAll());
        s2.remove(QChar('\n'));
        ui->textBrowser->append(tr("S2串为："));
        ui->textBrowser->append(s2);
    }
}

void Widget::on_pushButton_3_clicked()
{
    string s=s1.toStdString(),t=s2.toStdString();
    int m=s.length(),n=t.length();
    int matrix[m+1][n+1],flag[m+1][n+1];
    int i,j;
    for (i=0;i<=m;i++)
    {
        matrix[i][0]=DI*i;
        flag[i][0]=2;
    }
    for (j=0;j<=n;j++)
    {
        matrix[0][j]=DI*j;
        flag[0][j]=1;
    }
    flag[0][0]=0;
    for (i=1;i<=m;i++)
        for (j=1;j<=n;j++)
        {
            int r1=matrix[i][j-1]+DI;
            int r2=matrix[i-1][j]+DI;
            int r3=matrix[i-1][j-1];
            if (s.at(i-1)!=t.at(j-1)) r3=r3+D;
            else r3=r3+M;
            flag[i][j]=max_flag(r1,r2,r3);
            switch (flag[i][j]) {
            case 1:
                matrix[i][j]=r1;
                break;
            case 2:
                matrix[i][j]=r2;
                break;
            case 3:
                matrix[i][j]=r3;
                break;
            default:
                break;
            }
        }
    ui->lineEdit_3->setText(QString::number(matrix[m][n]));

    for (i=0;i<=m;i++)
    {
        for (j=0;j<=n;j++)
            cout<<matrix[i][j]<<"\t";
        cout<<endl;
    }

    i--;j--;
    vector <int> op;
    while (flag[i][j]!=0)
    {
        op.push_back(flag[i][j]);
        switch (op.back()) {
        case 1:
            j--;
            break;
        case 2:
            i--;
            break;
        case 3:
            i--;
            j--;
            break;
        default:
            break;
        }
    }

    i=1;j=1;
    int k=0,l=0;
    string p=s,q=t;
    while (!op.empty())
    {
//        cout<<op.back()<<endl;
//        cout<<"k:"<<k<<endl;
        switch (op.back()) {
        case 1:
//            ui->textBrowser->append(QString("%1%2%3").arg("insert(").arg(t[j-1]).arg("):"));
            p.insert(k,1,'_');
//            k++;
//            ui->textBrowser->append(QString::fromStdString(p));
//            j++;
            break;
        case 2:
//            ui->textBrowser->append(QString("%1%2%3").arg("delete(").arg(s[i-1]).arg("):"));
            q.insert(l,1,'_');
//            k++;
//            l++;
//            ui->textBrowser->append(QString::fromStdString(q));
//            i++;
            break;
//        case 3:
//            if (s[i-1]!=t[j-1])
//            {
//                ui->textBrowser->append(QString("%1%2%3%4%5").arg("replace(").arg(s[i-1]).arg(",").arg(t[j-1]).arg("):"));
//                p.replace(k,1,1,t[j]);
//                ui->textBrowser->append(QString::fromStdString(p));
//            }
//            i++;
//            j++;
//            k++;
//            l++;
//            break;
        default:
            break;
        }
        k++;
        l++;
        op.pop_back();
    }
    ui->textBrowser->append(QString::fromStdString(p));
    ui->textBrowser->append(QString::fromStdString(q));
}
