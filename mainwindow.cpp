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
#include <QDataStream>


/* Мозаичное панно. На форме находится квадрат 5х5 из QPushButton.
 * Нажатие на каждую позволяет выбрать изображение для неё.
 * В файле хранятся изображения назначенные  каждому из QPushButton.
 * Должна быть возможность сохранять и загружать файлы с полученными панно.*/


  MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent)
      , ui(new Ui::MainWindow)
  {
      ui->setupUi(this);
      window()->setGeometry(300,300,495,500);

      QPushButton* btnSave = new QPushButton(this);
      btnSave->setGeometry(2,1,92,20);
      btnSave->setText("SAVE");
      connect(btnSave,SIGNAL(clicked()),this,SLOT(btnPressedSave()));
      btnCount = 0;

      QPushButton* btnOpen = new QPushButton(this);
      btnOpen->setGeometry(96,1,95,20);
      btnOpen->setText("OPEN");
      connect(btnOpen,SIGNAL(clicked()),this,SLOT(openFile()));


      for (int i = 0; i < 5 ; ++i) {
          for (int j = 0; j < 5 ; ++j) {
              QPushButton* button = new QPushButton(this);
              button->setGeometry(3+i*95,22+j*95,91,81);
              QString bname = QString::number(btnCount);
              button->setObjectName(bname);
              connect(button,SIGNAL(clicked()),this,SLOT(btnPressed()));
              btnList.push_back(button);
              btnCount++;
          }
      }
      qDebug()<<btnList;

  }

  void MainWindow::openFile()
  {

    opLog = true;

    QString filter = "JSON File (*.json) ;; TXT file (*.txt)";
    QString file = QFileDialog::getOpenFileName(this,"Open a file","C:\\",filter);

    if (file != 0)
    {
        qDebug()<<file;
        jsonParse(file);
        startApp();


    }else   {
        file = "C://Users//Rich//Documents//pano//lab_fol//file.json";
        jsonParse(file);
        startApp();
    }

  }
  void MainWindow::btnPressed()
  {

    if (opLog == true)
    {
        QPushButton* sender = static_cast<QPushButton*>(QObject::sender());

        QString filter = "JPEG File (*.jpg) ;; Image File (*.img) ;; PNG File (*.png)";
        QString fileName = QFileDialog::getOpenFileName(this,"Open a file","C:\\",filter);

        QPixmap pixmap(fileName);
        QIcon ButtonIcon(pixmap);

        sender->setIcon(ButtonIcon);
        sender->setIconSize(QSize(200,200));

        pathmass[sender->objectName().toInt()] = fileName;


        qDebug()<<sender->objectName().toInt();
        qDebug()<<pathmass<<pathmass[sender->objectName().toInt()];
        qDebug()<<fileName;
        qDebug()<<pathmass;
    }
    else if(opLog == false){

        QMessageBox::warning(this,"Button Error","Firstly choose file by using open button");

    }

  }
  int MainWindow::jsonParse(QString fName)
  {

    QFile file(fName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open the file" << file.fileName() << "for reading:" << file.errorString();
        return 1;
    }
    else    {
        qDebug()<<"File's been open sucsessfuly";
    }

    jsonData = file.readAll();
    if (file.error() != QFile::NoError)
    {
        qDebug() << QString("Failed to read from file %1, error: %2").arg(file.fileName()).arg(file.errorString());
        return 2;
    }

    if (jsonData.isEmpty())
    {
       qDebug() << "No data was currently available for reading from file" << file.fileName();
       QMessageBox::warning(this,"Data Error","File's empty !");
       return 3;
    }

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject())
    {
        qDebug() << "Document is not an object";
        return 4;
    }

    QJsonObject rootObject = document.object();
    QStringList roots;

    roots.append(rootObject.keys().at(0) + ": " + rootObject.value(rootObject.keys().at(0)).toString());
    qDebug()<<roots;

    QJsonValue jvaluemass = rootObject.value("MASSIVE");

    if(jvaluemass.isArray()){
        jarray = jvaluemass.toArray();
        qDebug()<<jarray;
              for(int i = 0; i < jarray.count(); i++){
                  QJsonObject subtree = jarray.at(i).toObject();
                  pathmass.append(subtree.value("path").toString());
                  qDebug()<<i;
              }
          }
  }
  void MainWindow::startApp(){

      for (int i = 0; i < jarray.count() ;++i ) {
        QPixmap pixmap(pathmass[i]);
        QIcon ButtonIcon(pixmap);
        btnList[i]->setIcon(ButtonIcon);
        btnList[i]->setIconSize(QSize(200,200));
      }

  }
  void MainWindow::btnPressedSave(){

      QJsonObject mainMassive = QJsonDocument::fromJson(
      "{"
        "\"MASSIVE\": ["
                     "]"
       "}").object();
      QJsonArray mainArray = mainMassive["MASSIVE"].toArray();
      for (int i = 0; i < jarray.count() ;++i) {
       QJsonObject tempObject = mainArray[i].toObject();
       tempObject.insert("path", pathmass[i]);
       mainArray.append(tempObject);
      }

      mainMassive.insert("MASSIVE", mainArray);

      QJsonDocument doc(mainMassive);
      QString jsonString = doc.toJson(QJsonDocument::Indented);

      QFile file;
      QString filter = "JSON File (*.json) ;; TXT file (*.txt)";
      QString fileSet = QFileDialog::getOpenFileName(this,"Open a file","C:\\",filter);

      file.setFileName(fileSet);
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      file.resize(0);
      QTextStream stream(&file);
      stream << jsonString;
      file.close();

  }
  MainWindow::~MainWindow()
  {
      delete ui;
  }

