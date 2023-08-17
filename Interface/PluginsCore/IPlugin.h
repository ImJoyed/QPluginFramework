#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QDockWidget>
#include <QtCore>

enum class PLUGIN_TYPE {
    NORMAL = 0,
    SINGLE,
};

class IPlugin : public QObject
{
    Q_OBJECT

public:
    explicit IPlugin(QObject *parent = nullptr) : QObject(parent)
    {

    }
    virtual ~IPlugin()
    {
    
    }
    virtual bool InitPlugin() = 0;

    virtual PLUGIN_TYPE GetPluginType() = 0;

signals:
    void MessageSignal(const QString& key, const QObject* msgObj);

public slots:
    virtual void MessageSlot(const QString& key, const QObject* msgObj) = 0;
};

class IButtonPlugin : public IPlugin
{
    Q_OBJECT

public:
    explicit IButtonPlugin(QObject *parent = nullptr) : IPlugin(parent)
    {

    }
    virtual ~IButtonPlugin()
    {

    }
    virtual QWidget *GetButtonWidget() = 0;
    virtual const QString& GetCategory() = 0;
    virtual const QString& GetPanel() = 0;
};

class IDockPlugin : public IButtonPlugin
{
    Q_OBJECT

public:
    explicit IDockPlugin(QObject *parent = nullptr) : IButtonPlugin(parent)
    {

    }
    virtual ~IDockPlugin()
    {

    }
    virtual QDockWidget *GetDockWidget() = 0;
    virtual Qt::DockWidgetArea GetDockPosition() = 0;
};

class IWindowPlugin : public IPlugin
{
    Q_OBJECT

public:
    explicit IWindowPlugin(QObject *parent = nullptr) :IPlugin(parent)
    {

    }
    virtual ~IWindowPlugin()
    {

    }
    virtual QWidget *GetWindowWidget() = 0;
};

#endif // IPLUGIN_H
