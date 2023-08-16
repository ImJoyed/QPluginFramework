#ifndef PLUGINDEMO_H
#define PLUGINDEMO_H

#include "IPluginDemo.h"

class PluginDemo : public IPluginDemo
{
    Q_OBJECT

public:
    explicit PluginDemo(QObject *parent = nullptr);
    ~PluginDemo();

    // IPlugin interface
public:
    virtual bool InitPlugin() override;
    virtual PLUGIN_TYPE GetPluginType() override;

public slots:
    virtual void MessageSlot(const QString& key, const QObject* msgObj) override;

    // IPluginDemo interface
public:
    virtual void Echo(const QString &msg) override;
};

#endif // PLUGINDEMO_H
