#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<QPushButton*> btnList;
    QJsonArray jarray;
    QStringList pathmass;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
public slots:
    void btnPressed();
    int jsonParse();
    void btnsInsertStart();
    void startApp();
};
#endif // MAINWINDOW_H
