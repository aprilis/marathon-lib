#ifndef STREAMWINDOW_H
#define STREAMWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <vector>
using namespace std;

class StreamWindow : public QMainWindow
{
    Q_OBJECT

    vector<QLabel*> labels;

public:
    StreamWindow(initializer_list<string> streams);

    void setText(initializer_list<string> texts);
};

#endif // STREAMWINDOW_H

