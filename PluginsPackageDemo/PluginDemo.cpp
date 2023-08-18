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
    if(key == "echo.demoplugin.pluginspackage.joyed.cn")
    {
        QString msg = msgObj->property("echo").toString();
        LOG() << "recv msg: " << msg;
        this->Echo(msg);
    }
}

void PluginDemo::Echo(const QString &msg)
{
    LOG() << "call Echo().";
    qDebug() << msg;
}
