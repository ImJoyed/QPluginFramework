﻿#include "PluginsManager.h"
#include "IPluginsPackage.h"
#include "IPlugin.h"
#include <QDebug>
#include <QMap>
#include <QList>
#include <QVBoxLayout>
#include "RibbonBar.h"
#include <QMainWindow>
#include "SubWindowList.h"

#define LOG() qDebug() << "[PluginsManager]: "

PluginsManager::PluginsManager(QObject *parent)
    : IPluginsManager(parent)
{
}

bool PluginsManager::InitPluginManager(QString plguinsDir)
{
    LOG() << "Scan PluginsPackage in " << plguinsDir << "...";

    QString appName = QCoreApplication::applicationName();
    QString pluginsManagerName;
    if(appName.endsWith("_d"))
    {
        pluginsManagerName = "libPluginsManager_d.plugin";
    }
    else
    {
        pluginsManagerName = "libPluginsManager.plugin";
    }

    QString pluginsPackageDirPath = QCoreApplication::applicationDirPath() + "/" + plguinsDir;
    QStringList pluginsPackagePathList;

    QFileInfoList fileInfoList = QDir(pluginsPackageDirPath).entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if (!fileInfo.isFile() || (0 != fileInfo.suffix().compare("plugin")) || fileInfo.fileName() == pluginsManagerName)
        {
            continue;
        }
        LOG() << "Find PluginsPackage: " << fileInfo.filePath();
        pluginsPackagePathList.append(fileInfo.filePath());
    }

    foreach(QString pluginsPackagePath, pluginsPackagePathList)
    {
        LOG() << "Load PluginsPackage: " << pluginsPackagePath << "...";
        QPluginLoader pluginloader(pluginsPackagePath);
        QObject *plugin = pluginloader.instance();
        if(!plugin)
        {
            LOG() << "Load PluginsPackage failed!!!";
        }
        else
        {
            LOG() << "Convert interface.";
            IPluginsPackage *pluginsPackage = qobject_cast<IPluginsPackage *>(plugin);
            if(!pluginsPackage)
            {
                LOG() << "Convert interface failed!!!";
            }
            else
            {
                LOG() << "Get ids in this PluginsPackage.";
                QList<QString> ids = pluginsPackage->GetIds();
                foreach(QString id, ids)
                {
                    m_pluginsPkg.insert(id, pluginsPackage);
                }
                LOG() << "Connect register signal.";
                connect(pluginsPackage, &IPluginsPackage::RegisterSignal, this, &PluginsManager::RegisterSlot);
                LOG() << "Load PluginsPackage: " << pluginsPackagePath << " done.";
            }
        }
    }
    LOG() << "Load PluginsPackage in " << plguinsDir << " done.";
    return m_pluginsPkg.count() > 0;
}

IPlugin *PluginsManager::CreatePlugin(const QString &id, bool translateUi)
{
    if(m_plugins.contains(id)
        && m_plugins.value(id).count() >= 1)
    {
        IPlugin* plugin = m_plugins.value(id).at(0);
        if(plugin->GetPluginType() == PLUGIN_TYPE::SINGLE)
        {
            LOG() << "Plugin " << id << " is SINGLETON, and have been created, return it.";
            return m_plugins.value(id).at(0);
        }
    }

    LOG() << "Find " << id << "in plugins package...";
    IPluginsPackage *pluginsPkg = m_pluginsPkg.find(id).value();
    if(pluginsPkg)
    {
        LOG() << "Found, now create plugin...";
        IPlugin *plugin = pluginsPkg->CreatePlugin(id);
        if(plugin)
        {
            LOG() << "Created, now init plugin...";
            if(!plugin->InitPlugin())
            {
                LOG() << "Init plugin failed!!!";
                delete plugin;
                return nullptr;
            }
            LOG() << "Init complete, now insert into m_plugins.";
            QMap<QString, QList<IPlugin*>>::iterator it = m_plugins.find(id);
            if(it != m_plugins.end())
            {
                it->append(plugin);
            }
            else
            {
                QList<IPlugin*> plugins {plugin};
                m_plugins.insert(id, plugins);
            }
            // Set manager pointer
            plugin->SetManager(this);

            if(!translateUi)
            {
                LOG() << "Needn't translate ui, return.";
                return plugin;
            }
            LOG() << "Translate ui...";
            if(m_ribbonBar)
            {
                IButtonPlugin *buttonPlugin = dynamic_cast<IButtonPlugin*>(plugin);
                if(buttonPlugin)
                {
                    QWidget *widget = buttonPlugin->GetButtonWidget();
                    if(widget)
                    {
                        LOG() << "Translate to IButtonPlugin successful, add to ribbon bar.";
                        m_ribbonBar->AddButton(buttonPlugin->GetCategory()
                                               , buttonPlugin->GetPanel()
                                               , widget);
                    }
                }
            }
            if(m_mainWindow)
            {
                IDockPlugin *dockPlugin = dynamic_cast<IDockPlugin*>(plugin);
                if(dockPlugin)
                {
                    QWidget *widget = dockPlugin->GetDockWidget();
                    if(widget)
                    {
                        LOG() << "Translate to IDockPlugin successful, add to dock area.";
                        QDockWidget *dockWidget = new QDockWidget();
                        // delete title bar
                        delete dockWidget->titleBarWidget();
                        dockWidget->setTitleBarWidget(new QWidget(dockWidget));
                        // dock real widget
                        QWidget *dockRealWidget = new QWidget(dockWidget);
                        dockWidget->setWidget(dockRealWidget);
                        QVBoxLayout *layout = new QVBoxLayout(dockRealWidget);
                        dockRealWidget->setLayout(layout);
                        layout->setAlignment(Qt::AlignTop);
                        // dock main widget
                        widget->setParent(dockWidget);
                        // title
                        QLabel *title = new QLabel(widget->windowTitle(), widget);
                        layout->addWidget(title);
                        // widget in plugin
                        layout->addWidget(widget);
                        static QDockWidget* s_leftDockWidget = m_subWindowList;
                        static QDockWidget* s_rightDockWidget = nullptr;
                        static QDockWidget* s_topDockWidget = nullptr;
                        static QDockWidget* s_bottomDockWidget = nullptr;
                        switch(dockPlugin->GetDockPosition())
                        {
                            case Qt::LeftDockWidgetArea:
                            {
                                if(s_leftDockWidget)
                                {
                                    m_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
                                }
                                else
                                {
                                    m_mainWindow->tabifyDockWidget(s_leftDockWidget, dockWidget);
                                }
                                s_leftDockWidget = dockWidget;
                                break;
                            }
                            case Qt::RightDockWidgetArea:
                            {
                                if(s_rightDockWidget)
                                {
                                    m_mainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
                                }
                                else
                                {
                                    m_mainWindow->tabifyDockWidget(s_rightDockWidget, dockWidget);
                                }
                                s_rightDockWidget = dockWidget;
                                break;
                            }
                            case Qt::TopDockWidgetArea:
                            {
                                if(s_topDockWidget)
                                {
                                    m_mainWindow->addDockWidget(Qt::TopDockWidgetArea, dockWidget);
                                }
                                else
                                {
                                    m_mainWindow->tabifyDockWidget(s_topDockWidget, dockWidget);
                                }
                                s_topDockWidget = dockWidget;
                                break;
                            }
                            case Qt::BottomDockWidgetArea:
                            {
                                if(s_bottomDockWidget)
                                {
                                    m_mainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
                                }
                                else
                                {
                                    m_mainWindow->tabifyDockWidget(s_bottomDockWidget, dockWidget);
                                }
                                s_bottomDockWidget = dockWidget;
                                break;
                            }
                        }
                    }
                }
            }
            if(m_subWindowList)
            {
                IWindowPlugin *windowPlugin = dynamic_cast<IWindowPlugin*>(plugin);
                if(windowPlugin)
                {
                    QWidget *widget = windowPlugin->GetWindowWidget();
                    if(widget)
                    {
                        LOG() << "Translate to IWindowPlugin successful, add to dock area.";
                        m_subWindowList->AddSubWindow(widget);
                    }
                }
            }
            LOG() << "Translate ui done.";
            return plugin;
        }
        LOG() << "Create failed!!!";
    }
    LOG() << "Not fount!!!";
    return nullptr;
}

IPlugin *PluginsManager::GetPlugin(const QString &id, const qsizetype &index)
{
    LOG() << "Find " << id << "in plugins...";
    QList<IPlugin*> plugins = m_plugins.find(id).value();
    if(plugins.size() > index)
    {
        LOG() << "Found, return.";
        return plugins.at(index);
    }
    LOG() << "Not found, return nullptr!!!";
    return nullptr;
}

bool PluginsManager::DestroyPlugin(const QString &id, const qsizetype &index)
{
    if(!m_plugins.contains(id))
    {
        LOG() << QString("Not found %1!!!").arg(id);
        return false;
    }
    QList<IPlugin*> &plugins = m_plugins[id];
    if(plugins.count() <= index)
    {
        LOG() << "Index out of range!!!";
        return false;
    }
    IPlugin* plugin = plugins.at(index);

    disconnect(plugin, &IPlugin::MessageSignal, this, &PluginsManager::MessageSlot);
    disconnect(this, &PluginsManager::MessageSignal, plugin, &IPlugin::MessageSlot);

    delete plugin;
    plugins.removeAt(index);
    LOG() << "Destroyed plugin("<< id << "[" << index << "])";
    return true;
}

bool PluginsManager::DestroyPlugin(const IPlugin *plugin)
{
    QStringList ids = m_plugins.keys();
    foreach(QString id, ids)
    {
        QList<IPlugin*> &plugins = m_plugins[id];
        for(qsizetype i = 0 ; i < plugins.count() ; ++i)
        {
            if(plugins[i] == plugin)
            {
                disconnect(plugins[i], &IPlugin::MessageSignal, this, &PluginsManager::MessageSlot);
                disconnect(this, &PluginsManager::MessageSignal, plugins[i], &IPlugin::MessageSlot);
                delete plugins[i];
                plugins.removeAt(i);
                LOG() << "Destroyed plugin("<< (void*)plugin << ")";
                return true;
            }
        }
    }
    return false;
}

qsizetype PluginsManager::GetPluginsCount(const QString &id)
{
    if(!m_plugins.contains(id))
    {
        LOG() << "Not found " << id << "!!!";
        return 0;
    }
    return m_plugins.value(id).count();
}

void PluginsManager::SetRibbonBar(RibbonBar *ribbonBar)
{
    m_ribbonBar = ribbonBar;
}

void PluginsManager::SetMainWindow(QMainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void PluginsManager::SetSubWindowList(SubWindowList *subWindowList)
{
    m_subWindowList = subWindowList;
}

void PluginsManager::RegisterSlot(const IPlugin *plugin)
{
    connect(plugin, &IPlugin::MessageSignal, this, &PluginsManager::MessageSlot);
    connect(this, &PluginsManager::MessageSignal, plugin, &IPlugin::MessageSlot);
}

void PluginsManager::MessageSlot(const QString& key, const QObject *msgObj)
{
    emit MessageSignal(key, msgObj);
}
