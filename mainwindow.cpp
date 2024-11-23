#include "mainwindow.h"
#include <QDebug>
#include "RtMidi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    try {
        midiout = new RtMidiOut();

        // 列出可用的MIDI端口
        unsigned int nPorts = midiout->getPortCount();
        qDebug() << "Found" << nPorts << "MIDI output ports.";

        for (unsigned int i = 0; i < nPorts; i++) {
            QString portName = QString::fromStdString(midiout->getPortName(i));
            qDebug() << "Port" << i << ":" << portName;
        }

        if (nPorts > 0) {
            // 打开第一个可用的MIDI端口
            midiout->openPort(0);
            qDebug() << "Successfully opened MIDI port:" << QString::fromStdString(midiout->getPortName(0));

            // 发送一个测试音符
            std::vector<unsigned char> message;
            message.push_back(0x90);
            message.push_back(60);
            message.push_back(100);
            midiout->sendMessage(&message);

            qDebug() << "Sent test note";

            // 关闭测试音符
            message[0] = 0x80;
            message[2] = 0;
            midiout->sendMessage(&message);
        } else {
            qDebug() << "No MIDI ports available. Creating virtual port...";
            midiout->openVirtualPort("My Virtual Port");
            qDebug() << "Created virtual MIDI port";
        }
    } catch (RtMidiError &error) {
        qDebug() << "RtMidi error:" << QString::fromStdString(error.getMessage());
    }

    // 设置窗口标题和大小
    setWindowTitle("MIDI Keyboard");
    setMinimumSize(1920, 1200);
    resize(1920, 1200);

}

MainWindow::~MainWindow()
{
    if (midiout) {
        midiout->closePort();
        delete midiout;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        // 将键盘按键映射到MIDI音符
        int note = -1; // 初始化为无效值
        switch (event->key()) {
        case Qt::Key_A: note = 60; break;
        case Qt::Key_W: note = 61; break;
        case Qt::Key_S: note = 62; break;
        case Qt::Key_E: note = 63; break;
        case Qt::Key_D: note = 64; break;
        case Qt::Key_F: note = 65; break;
        case Qt::Key_T: note = 66; break;
        case Qt::Key_G: note = 67; break;
        case Qt::Key_Y: note = 68; break;
        case Qt::Key_H: note = 69; break;
        case Qt::Key_U: note = 70; break;
        case Qt::Key_J: note = 71; break;
        case Qt::Key_K: note = 72; break;
        }

        if (note != -1) {
            playNote(note, 100);
        }
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        int note = -1;
        switch (event->key()) {
        case Qt::Key_A: note = 60; break;
        case Qt::Key_W: note = 61; break;
        case Qt::Key_S: note = 62; break;
        case Qt::Key_E: note = 63; break;
        case Qt::Key_D: note = 64; break;
        case Qt::Key_F: note = 65; break;
        case Qt::Key_T: note = 66; break;
        case Qt::Key_G: note = 67; break;
        case Qt::Key_Y: note = 68; break;
        case Qt::Key_H: note = 69; break;
        case Qt::Key_U: note = 70; break;
        case Qt::Key_J: note = 71; break;
        case Qt::Key_K: note = 72; break;
        }

        if (note != -1) {
            playNote(note, 0);
        }
    }
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::playNote(int note, int velocity)
{
    if (!midiout || !midiout->isPortOpen()) {
        return;
    }

    static std::vector<unsigned char> message(3);  // 静态分配消息缓冲区
    message[0] = velocity > 0 ? 0x90 : 0x80;  // Note On/Off channel 1
    message[1] = note;
    message[2] = velocity;

    midiout->sendMessage(&message);
}

