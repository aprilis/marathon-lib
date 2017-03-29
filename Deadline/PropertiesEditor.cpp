#include "PropertiesEditor.h"
#include <QHeaderView>

QDialog *settingsDialog = nullptr;

EventHandler::EventHandler(Property *property) : prop(property)
{

}

void EventHandler::valueChanged()
{
     prop->valueChanged();
}

template<> string convertString<string>(const string &str)
{
    return str;
}

PropertiesEditor::PropertiesEditor()
{
    form = new QFormLayout;
}

PropertiesEditor::~PropertiesEditor()
{
    for(auto *x : properties)
        delete x;
}

void PropertiesEditor::add(Property *property)
{
    properties.push_back(property);
    form->addRow(property->getLabel(), property->getWidget());
}

void PropertiesEditor::setObject(void *object)
{
    for(auto x : properties)
        x->setObject(object);
}

QFormLayout* PropertiesEditor::getForm()
{
    return form;
}
