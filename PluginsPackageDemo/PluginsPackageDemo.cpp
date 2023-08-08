#include "PluginsPackageDemo.h"
#include "PluginsCore/IPlugin.h"
#include <QDebug>
#include <QMap>
#include <QList>

#include "PluginDemo.h"

#define LOG() qDebug() << "[PluginsPackageDemo]: "

PluginsPackageDemo::PluginsPackageDemo(QObject *parent)
    : IPluginsPackage(parent)
{
}

QList<QString> PluginsPackageDemo::GetIds()
{
    return {PLUGINDEMO_ID};
}

IPlugin *PluginsPackageDemo::CreatePlugin(const QString &id)
{
    IPlugin *plugin = nullptr;
    if(id == PLUGINDEMO_ID)
    {
        plugin = new PluginDemo();
        emit Register(plugin);
    }
    return plugin;
}
