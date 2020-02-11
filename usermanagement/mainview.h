#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
};

#endif // MAINVIEW_H
