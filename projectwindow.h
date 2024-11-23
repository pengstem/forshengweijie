#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

class projectwindowData;

class projectwindow
{

public:
    projectwindow();
    projectwindow(const projectwindow &);
    projectwindow &operator=(const projectwindow &);
    ~projectwindow();

private:
    QSharedDataPointer<projectwindowData> data;
};

#endif // PROJECTWINDOW_H
