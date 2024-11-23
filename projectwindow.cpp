#include "projectwindow.h"

class projectwindowData : public QSharedData
{
public:
};

projectwindow::projectwindow()
    : data(new projectwindowData)
{}

projectwindow::projectwindow(const projectwindow &rhs)
    : data{rhs.data}
{}

projectwindow &projectwindow::operator=(const projectwindow &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

projectwindow::~projectwindow() {}
