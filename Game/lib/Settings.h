#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "PropertiesEditor.h"

extern QDialog *settingsDialog;

template <class T> void edit(T &object)
{
    auto form = object.getPropertiesEditor().getForm();
    if(settingsDialog == nullptr)
        settingsDialog = new QDialog();
    settingsDialog->setWindowTitle("Settings");
    settingsDialog->setWindowFlags(Qt::WindowCloseButtonHint);
    settingsDialog->setLayout(form);
    settingsDialog->adjustSize();
    settingsDialog->show();
    settingsDialog->raise();
    settingsDialog->activateWindow();
}

#endif // SETTINGS_H
