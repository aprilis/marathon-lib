#ifndef PROPERTIESEDITOR_H
#define PROPERTIESEDITOR_H

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QObject>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

template<class T> T convertString(const string &str)
{
    istringstream stream(str);
    T t;
    stream >> t;
    if(stream.fail()) throw 0;
    return t;
}

template<> string convertString<string>(const string &str);

template<class T> QString toQString(const T &t)
{
    ostringstream stream;
    stream << t;
    return QString(stream.str().c_str());
}

class Property;

class EventHandler : public QObject
{
    Q_OBJECT

private:
    Property *prop;

public:
    EventHandler(Property *property);

public slots:
    void valueChanged();
};

class Property
{
protected:
    QString label;

    QWidget *widget;

    char *object = nullptr;

    int offset;

    EventHandler handler;

    char *getObject() { return object + offset; }

public:
    Property(string text, int diff = 0)
        : label(text.c_str()), offset(diff), handler(this) { }

    QString getLabel() { return label; }

    QWidget *getWidget() { return widget; }

    EventHandler *getHandler() { return &handler; }

    virtual ~Property() { }

    virtual void setObject(void *obj) { object = (char*)obj; }

    virtual void valueChanged() = 0;
};

template<class T> class DefaultProperty : public Property
{
    QLineEdit *edit;

    T& getTObject()
    {
        return *reinterpret_cast<T*>(getObject());
    }

public:
    DefaultProperty(string text, int diff = 0)
        : Property(text, diff)
    {
        edit = new QLineEdit();
        edit->setMaximumWidth(50);
        widget = edit;
        QObject::connect(edit, SIGNAL(editingFinished()), &handler, SLOT(valueChanged()));
    }

    void setObject(void *obj)
    {
        Property::setObject(obj);
        edit->setText(toQString(getTObject()));
    }

    void valueChanged()
    {
        try
        {
            getTObject() = convertString<T>(edit->text().toStdString());
        }
        catch(...)
        {
            getTObject() = T();
        }
        edit->setText(toQString(getTObject()));
    }
};

template<> class DefaultProperty<bool> : public Property
{
    QCheckBox *check;

    bool& getTObject()
    {
        return *reinterpret_cast<bool*>(getObject());
    }

public:
    DefaultProperty(string text, int diff = 0)
        : Property(text, diff)
    {
        check = new QCheckBox();
        widget = check;
        QObject::connect(check, SIGNAL(stateChanged(int)), &handler, SLOT(valueChanged()));
    }

    void setObject(void *obj)
    {
        Property::setObject(obj);
        check->setChecked(getTObject());
    }

    void valueChanged()
    {
        getTObject() = check->checkState() == Qt::CheckState::Checked;
    }
};

template <class T> class ComboBoxProperty : public Property
{
    vector<T> values;

    QComboBox *combo;

    T& getTObject()
    {
        return *reinterpret_cast<T*>(getObject());
    }

public:
    ComboBoxProperty(string  text, int diff = 0)
        : Property(text, diff)
    {
        combo = new QComboBox();
        QObject::connect(combo, SIGNAL(currentIndexChanged(int)), &handler, SLOT(valueChanged()));
        widget = combo;
    }

    ComboBoxProperty *add(string key, const T &value)
    {
        combo->addItem(key.c_str());
        values.push_back(value);
        return this;
    }

    ComboBoxProperty *add(const T &value)
    {
        return add(toQString(value).toStdString(), value);
    }

    void setObject(void *obj)
    {
        Property::setObject(obj);
        const auto &value = getTObject();
        for(int i = 0; i < values.size(); i++)
            if(values[i] == value)
                combo->setCurrentIndex(i);
    }

    void valueChanged()
    {
        if(object != nullptr)
            getTObject() = values[combo->currentIndex()];
    }
};

class PropertiesEditor
{
    QFormLayout *form;

    vector<Property*> properties;

public:
    PropertiesEditor();

    ~PropertiesEditor();

    void add(Property *property);

    void setObject(void *object);

    QFormLayout* getForm();
};

template<class T> DefaultProperty<T>* makeDefaultProperty(string text, T &property, void *object)
{
    return new DefaultProperty<T>(text, (char*)&property - (char*)object);
}

template<class T> ComboBoxProperty<T>* makeComboBoxProperty(string text, T &property, void *object)
{
    return new ComboBoxProperty<T>(text, (char*)&property - (char*)object);
}

#define DEFAULT_PROPERTY(prop) makeDefaultProperty(#prop, prop, this)
#define COMBOBOX_PROPERTY(prop) makeComboBoxProperty(#prop, prop, this)

#endif // PROPERTIESEDITOR_H
