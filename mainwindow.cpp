#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
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

      for (int i = 0; i < 5 ; ++i) {
          for (int j = 0; j < 5 ; ++j) {
              QPushButton* button = new QPushButton(this);
              button->setGeometry(3+i*95,j*95,91,81);
              connect(button,SIGNAL(clicked()),this,SLOT(btnPressed()));
              btnList.push_back(button);
          }
      }

     qDebug()<<btnList;

  }




  void MainWindow::btnPressed()
  {

    QPushButton* sender = static_cast<QPushButton*>(QObject::sender());

    QString program = "C:\\Users";
    QStringList arguments;
    arguments << "-style" << "fusion";
    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);
    QProcess::startDetached("explorer",  arguments);



    QPixmap pixmap("C:\\Users\\Rich\\Desktop\\fold\\1st.jfif");
    QIcon ButtonIcon(pixmap);

    sender->setIcon(ButtonIcon);
    sender->setStyleSheet("C:\\Users\\Rich\\Desktop\\fold\\1st.jfif");
    sender->setIconSize(QSize(200,200));


  }

  int MainWindow::jsonParse()
  {

    QFile file("C:\\Users\\Rich\\Desktop\\fold\\test.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open the file" << file.fileName() << "for reading:" << file.errorString();
        return 1;
    }else
    {
        qDebug()<<"File's been open sucsessfuly";
    }

    QByteArray jsonData = file.readAll();
    if (file.error() != QFile::NoError)
    {
        qDebug() << QString("Failed to read from file %1, error: %2").arg(file.fileName()).arg(file.errorString());
        return 2;
    }

    if (jsonData.isEmpty())
    {
        qDebug() << "No data was currently available for reading from file" << file.fileName();
        return 3;
    } else
    {
       qDebug()<<jsonData;
    }


    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject())
    {
        qDebug() << "Document is not an object";
        return 4;
    }

    QJsonObject object = document.object();
    QJsonValue jsonValue = object.value("id");

    if (jsonValue.isUndefined())
    {
        qDebug() << "Key id does not exist";
        return 5;
    }

    if (!jsonValue.isString())
    {
        qDebug() << "Value not string";
        return 6;
    }

        qDebug() << jsonValue.toString()<< "+";


  }






  MainWindow::~MainWindow()
  {
      delete ui;
  }

