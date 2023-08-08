#ifndef PLUGINDEMO_H
#define PLUGINDEMO_H

#include "PluginsDemo/IPluginDemo.h"

class PluginDemo : public IPluginDemo
{
    Q_OBJECT

public:
    explicit PluginDemo(QObject *parent = nullptr);

    // IPlugin interface
public:
    virtual bool InitPlugin() override;
    virtual PLUGIN_TYPE GetPluginType() override;

public slots:
    virtual void onMessage(const QString& key, const QVariant &msg) override;

    // IPluginDemo interface
public:
    virtual void Echo(const QString &msg) override;
};

#endif // PLUGINDEMO_H
