#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
      window()->setGeometry(300,300,495,500);

      for (int i = 0; i < 5 ; ++i) {
          for (int j = 0; j < 5 ; ++j) {
              QPushButton* button = new QPushButton(this);
              button->setGeometry(3+i*95,22+j*95,91,81);
              connect(button,SIGNAL(clicked()),this,SLOT(btnPressed()));
              btnList.push_back(button);
              qDebug()<<btnList[j];
          }
      }

  }




  void MainWindow::btnPressed()
  {

    QPushButton* sender = static_cast<QPushButton*>(QObject::sender());

    QString filter = "Image File (*.img) ;; JPEG File (*.jpg) ;; PNG File (*.png)";
    QString fileName = QFileDialog::getOpenFileName(this,"Open a file","C:\\",filter);
    qDebug()<<fileName;

    QPixmap pixmap(fileName);
    QIcon ButtonIcon(pixmap);

    sender->setIcon(ButtonIcon);
    sender->setIconSize(QSize(200,200));
  }

  int MainWindow::jsonParse()
  {
    QStringList roots;


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
       //qDebug()<<jsonData;
    }


    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject())
    {
        qDebug() << "Document is not an object";
        return 4;
    }

   // qDebug()<<document;

    QJsonObject root = document.object();

    roots.append(root.keys().at(0) + ": " + root.value(root.keys().at(0)).toString());

    qDebug()<<roots;

    QJsonValue jvaluemass = root.value("MASSIVE");

    if(jvaluemass.isArray()){
        jarray = jvaluemass.toArray();
              for(int i = 0; i < jarray.count(); i++){
                  QJsonObject subtree = jarray.at(i).toObject();
                  pathmass.append(subtree.value("path").toString());
                  qDebug()<<i;
              }
          }

     qDebug()<<pathmass;

  }

  void MainWindow::btnsInsertStart(){

      for (int i = 0; i < jarray.count() ;++i ) {
        QPixmap pixmap(pathmass[i]);
        QIcon ButtonIcon(pixmap);
        btnList[i]->setIcon(ButtonIcon);
        btnList[i]->setIconSize(QSize(200,200));
        qDebug()<<i;
      }
 }

  void MainWindow::startApp(){

  }



  MainWindow::~MainWindow()
  {
      delete ui;
  }

