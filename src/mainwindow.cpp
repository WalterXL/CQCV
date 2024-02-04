#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mFps = 24.0;
    mIsWrite = false;
    this->setFixedSize(639, 594);
    this->move(382, 134);

    std::thread capRun = std::thread(std::bind(&MainWindow::captureRun,this));
    capRun.detach();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::captureRun() {

    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    int flag = 0;

    mCap.open(deviceID, apiID);
    if (mCap.get(CAP_PROP_FPS) > 0) {
        mFps = mCap.get(CAP_PROP_FPS);
    }

    while (true) {
        mCap.read(mFrame);
        cv::resize(mFrame, mFrame, Size(640, 480));

        cv::flip(mFrame, mFrame, +1);
        cv::cvtColor(mFrame, mFrame, cv::COLOR_BGR2RGB);
        QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) mFrame.data, mFrame.cols, mFrame.rows, QImage::Format_RGB888));
        ui->label->setPixmap(pix);
        if(mIsWrite) {
            mWriter.write(mFrame);
        }
    }
}

void MainWindow::on_start_video_clicked(){
    int codec = VideoWriter::fourcc('X', 'V', 'I', 'D');
    string filename = "./live_xvid.mp4";
    bool isColor = (mFrame.type() == CV_8UC3);
    mWriter.open(filename, codec, mFps, mFrame.size(), isColor);

    if (!mWriter.isOpened()) {
        cerr << "Could not open the output video file for write\n";
    }
    mIsWrite = true;
}

void MainWindow::on_end_video_clicked(){
    mIsWrite = false;
    sleepms(1000);
    mWriter.release();
}

