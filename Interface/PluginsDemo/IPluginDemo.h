#ifndef IPLUGINDEMO_H
#define IPLUGINDEMO_H

#include <QtCore>
#include "../PluginsCore/IPlugin.h"

#define PLUGINDEMO_ID "plugindemo.pluginspackagedemo.joyed.cn"

class IPluginDemo : public IPlugin
{
    Q_OBJECT

public:
    explicit IPluginDemo(QObject *parent = nullptr) : IPlugin(parent)
    {

    }
    virtual ~IPluginDemo()
    {
    
    };
    virtual void Echo(const QString& msg) = 0;
};

#endif // IPLUGINDEMO_H
