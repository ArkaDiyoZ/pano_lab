#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

/* Мозаичное панно. На форме находится квадрат 5х5 из QLabel.
 * Нажатие на каждую позволяет выбрать изображение для неё.
 * В файле хранятся изображения назначенные  каждому из QLabel.
 * Должна быть возможность сохранять и загружать файлы с полученными панно.*/


  MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent)
      , ui(new Ui::MainWindow)
  {
      ui->setupUi(this);

      connect(ui->pushButton, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_3, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_4, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_5, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_6, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_7, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_8, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_9, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_10, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_11, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_12, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_13, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_14, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_15, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_16, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_17, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_18, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_19, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_20, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_21, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_22, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_23, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_24, SIGNAL (released()),this, SLOT (btnPressed()));
      connect(ui->pushButton_25, SIGNAL (released()),this, SLOT (btnPressed()));

  }




  void MainWindow::btnPressed()
  {

    QString program = "C:\\Users";
    QStringList arguments;
    arguments << "-style" << "fusion";
    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);
    QProcess::startDetached("explorer",  arguments);


    QPixmap pixmap("C:\\Users\\Rich\\Desktop\\lab_fol\\2nd.jpg");
    QIcon ButtonIcon(pixmap);
    ui->pushButton->setIcon(ButtonIcon);
    //ui->pushButton->setStyleSheet("C:\\Users\\Rich\\Desktop\\lab_fol\\2nd.jpg");
    ui->pushButton->setIconSize(QSize(200,200));


  }






  MainWindow::~MainWindow()
  {
      delete ui;
  }

