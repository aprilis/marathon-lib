#include "StreamWindow.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

StreamWindow::StreamWindow(initializer_list<string> streams)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setWindowTitle("Output");
    resize(400, 400);
    auto widget = new QWidget();
    auto hbox = new QHBoxLayout();
    hbox->setSpacing(10);
    widget->setLayout(hbox);
    setCentralWidget(widget);
    for(auto s: streams)
    {
        auto vbox = new QVBoxLayout();
        auto scroll = new QScrollArea();
        scroll->setStyleSheet("background-color: white");
        auto label = new QLabel();
        label->setTextInteractionFlags(Qt::TextSelectableByMouse);
        labels.push_back(label);
        scroll->setWidget(label);
        vbox->addWidget(new QLabel(QString::fromStdString(s)));
        vbox->addWidget(scroll, 1);
        hbox->addLayout(vbox, 1);
    }
    show();
}

void StreamWindow::setText(initializer_list<string> streams)
{
    vector<string> vec(streams);
    vec.resize(labels.size());
    for(int i = 0; i < labels.size(); i++)
    {
        labels[i]->setText(QString::fromStdString(vec[i]));
        labels[i]->adjustSize();
    }
}
