#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <iostream>
#include <stdio.h>
#include <ctime>

#include <QMainWindow>
#include <QStyleFactory>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define sleepms(val) std::this_thread::sleep_for(val##ms)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void captureRun();

private slots:
    void on_start_video_clicked();
    void on_end_video_clicked();

private:
    Ui::MainWindow *    ui;
    Mat                 mFrame;
    VideoCapture        mCap;
    VideoWriter         mWriter;
    double              mFps;
    bool                mIsWrite;
};

#endif
