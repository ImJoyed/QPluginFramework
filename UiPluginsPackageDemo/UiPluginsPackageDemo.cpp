#include "UiPluginsPackageDemo.h"
#include "IPlugin.h"
#include <QDebug>
#include <QList>

#include "UiPluginDemoIds.h"
#include "CommandPlugin.h"
#include "DockPlugin.h"
#include "ToolPlugin.h"
#include "WindowPlugin.h"

#define LOG() qDebug() << "[UiPluginsPackageDemo]: "

UiPluginsPackageDemo::UiPluginsPackageDemo(QObject *parent)
    : IPluginsPackage(parent)
{
}

QList<QString> UiPluginsPackageDemo::GetIds()
{
    return {
        COMMANDPLUGIN_ID
        , DOCKPLUGIN_ID
        , TOOLPLUGIN_ID
        , WINDOWPLUGIN_ID
    };
}

IPlugin *UiPluginsPackageDemo::CreatePlugin(const QString &id)
{
    IPlugin *plugin = nullptr;

    if(id == COMMANDPLUGIN_ID)
        plugin = new CommandPlugin();
    else if(id == DOCKPLUGIN_ID)
        plugin = new DockPlugin();
    else if(id == TOOLPLUGIN_ID)
        plugin = new ToolPlugin();
    else if(id == WINDOWPLUGIN_ID)
        plugin = new WindowPlugin();

    if(plugin)
        emit RegisterSignal(plugin);

    return plugin;
}
