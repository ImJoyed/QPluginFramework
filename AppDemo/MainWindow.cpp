#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QPluginLoader>
#include <QDebug>
#include "PluginsManager/IPluginsManager.h"
#include "PluginsDemo/IPluginDemo.h"
#include "PluginsCore/IPlugin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Load plugin.";

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
    QPluginLoader pluginloader(QApplication::applicationDirPath() + "/../pluginspackage/" + pluginsManagerName);
    QObject *qPlugin = pluginloader.instance();
    if(!qPlugin)
    {
        qDebug() << "Load plugin failed!!!";
    }
    else
    {
        qDebug() << "Convert interface.";
        IPluginsManager *manager = dynamic_cast<IPluginsManager *>(qPlugin);
        if(!manager)
        {
            qDebug() << "Convert interface failed!!!";
        }
        else
        {
            qDebug() << "Init plugin manager.";
            if(!manager->InitPluginManager("../pluginspackage"))
            {
                qDebug() << "Init plugin manager failed!!!";
            }
            else
            {
                qDebug() << "Test IPluginDemo...";
                IPlugin *plugin = manager->CreatePlugin(PLUGINDEMO_ID);
                if(!plugin)
                {
                    qDebug() << "Create plugin failed!!!";
                }
                IPluginDemo *pluginDemo = dynamic_cast<IPluginDemo *>(plugin);
                if(!pluginDemo)
                {
                    qDebug() << "Convert IPluginDemo failed!!!";
                }
                else
                {
                    pluginDemo->Echo("Hello.");
                }
                qDebug() << "Destroy IPluginDemo...";
                if(!manager->DestroyPlugin(pluginDemo))
                {
                    qDebug() << "Destroyed IPluginDemo failed!!!";
                }
                else
                {
                    qDebug() << "Destroyed IPluginDemo.";
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

