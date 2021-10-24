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
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<QPushButton*> btnList;
    QJsonArray jarray;
    bool opLog = false;
    int btnCount;
    QByteArray jsonData;
    QStringList pathmass;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
public slots:
    void btnPressedDefault();
    void btnPressed();
    void btnPressedSave();
    int jsonParse(QString);
    void startApp();
    void openFile();
};
#endif // MAINWINDOW_H
