#include "PluginDemo.h"
#include <QDebug>

#define LOG() qDebug() << "[plugindemo.pluginspackagedemo.joyed.cn]: "

PluginDemo::PluginDemo(QObject *parent)
    : IPluginDemo(parent)
{

}

bool PluginDemo::InitPlugin()
{
    LOG() << "Init plugin.";
    return true;
}

IPlugin::PLUGIN_TYPE PluginDemo::GetPluginType()
{
    return SINGLE;
}

void PluginDemo::MessageSlot(const QString& key, const QVariant &msg)
{
    if(key == "echo.demoplugin.pluginspackage.joyed.cn")
    {
        LOG() << "recv msg: " << msg.toString();
    }
}

void PluginDemo::Echo(const QString &msg)
{
    LOG() << "send msg: " << msg;
    emit MessageSignal("echo.demoplugin.pluginspackage.joyed.cn", msg);
}
