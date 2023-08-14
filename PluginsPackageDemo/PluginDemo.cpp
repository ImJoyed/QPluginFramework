#include "PluginDemo.h"
#include <QDebug>

#define LOG() qDebug() << "[plugindemo.pluginspackagedemo.joyed.cn]: "

PluginDemo::PluginDemo(QObject *parent)
    : IPluginDemo(parent)
{

}

PluginDemo::~PluginDemo()
{

}

bool PluginDemo::InitPlugin()
{
    LOG() << "Init plugin.";
    return true;
}

PLUGIN_TYPE PluginDemo::GetPluginType()
{
    return PLUGIN_TYPE::SINGLE;
}

void PluginDemo::MessageSlot(const QString& key, const QObject* msgObj)
{
    ;
    if(key == "echo.demoplugin.pluginspackage.joyed.cn")
    {
        LOG() << "recv msg: " << msgObj->property("echo").toString();
    }
}

void PluginDemo::Echo(const QString &msg)
{
    LOG() << "send msg: " << msg;
    this->setProperty("echo", msg);
    emit MessageSignal("echo.demoplugin.pluginspackage.joyed.cn", this);
}
