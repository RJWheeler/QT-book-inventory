#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QList>
#include <QSysInfo>
#include <iostream>
#include <QRect>
#include <QScreen>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qsizetype screenNumber;
    if (QGuiApplication::screens().size() > 1){
       screenNumber = 1;
    }
    else{
       screenNumber = 0;
    }

    // Sets the display to primay and secondary screens
    QScreen *screens = QGuiApplication::primaryScreen();
    QScreen *screen = QGuiApplication::screens().at(screenNumber);
    QSize screenGeometry = screen->size();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    w.setScreen(screens);


    height = height*.15;
    width = width*.15;
    QPixmap pixmap("splash.png");
    QSplashScreen splash(screen, pixmap, Qt::WindowStaysOnTopHint);
    splash.setFixedHeight(height);
    splash.setFixedWidth(width);
    splash.show();
    splash.showMessage("Now Loading Nevermore");
    a.processEvents();
    QTimer::singleShot(5000, &splash, SLOT(close()));
    QTimer::singleShot(5000, &w, SLOT(show()));
    return a.exec();
}
