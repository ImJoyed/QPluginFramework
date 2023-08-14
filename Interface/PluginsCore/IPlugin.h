#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtCore>

class IPlugin : public QObject
{
    Q_OBJECT

public:
    explicit IPlugin(QObject *parent = nullptr) : QObject(parent)
    {

    }
    virtual ~IPlugin()
    {
    
    };
    virtual bool InitPlugin() = 0;

    enum PLUGIN_TYPE{
        NORMAL = 0,
        SINGLE,
    };
    virtual PLUGIN_TYPE GetPluginType() = 0;

signals:
    void MessageSignal(const QString& key, const QObject* msgObj);

public slots:
    virtual void MessageSlot(const QString& key, const QObject* msgObj) = 0;
};

#endif // IPLUGIN_H
