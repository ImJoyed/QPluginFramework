#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QPluginLoader>
#include <QDebug>
#include "IPluginsManager.h"
#include "IPluginDemo.h"
#include "UiPluginDemoIds.h"
#include "IPlugin.h"

#include <QDateTime>
#include <QPushButton>
#include <QTimer>

#include "SubWindowList.h"
#include "RibbonBar.h"
#include "RibbonCategory.h"
#include "RibbonPanel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ribbon bar
    RibbonBar *ribbonBar = new RibbonBar(this);
    this->setMenuWidget(ribbonBar);

    // dock widget
    SubWindowList *subWindowsList = new SubWindowList(this);
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, subWindowsList);

    // mdi area
    this->setCentralWidget(subWindowsList->GetSubWindowArea());

    // status bar
    QWidget *statusBar = new QWidget(this);
    this->statusBar()->addPermanentWidget(statusBar);
    QHBoxLayout *statusBarLayout = new QHBoxLayout(this->statusBar());
    statusBar->setLayout(statusBarLayout);
    statusBarLayout->setAlignment(Qt::AlignRight);
    QLabel *dateTime = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"), this->statusBar());
    statusBarLayout->addWidget(dateTime);
    // timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        dateTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    });
    timer->setInterval(1000);
    timer->start();

#define LOAD_PLUGINS_MANAGER 1
#if LOAD_PLUGINS_MANAGER
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
                qDebug() << "Set ribbonbar, mainwindow, subwindowlist to plugin manager.";
                manager->SetRibbonBar(ribbonBar);
                manager->SetMainWindow(this);
                manager->SetSubWindowList(subWindowsList);
                qDebug() << "Create plugins...";
                manager->CreatePlugin(PLUGINDEMO_ID);
                manager->CreatePlugin(COMMANDPLUGIN_ID);
                manager->CreatePlugin(DOCKPLUGIN_ID);
                manager->CreatePlugin(TOOLPLUGIN_ID);
                manager->CreatePlugin(WINDOWPLUGIN_ID);
                qDebug() << "Create plugins done.";

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
//                qDebug() << "Destroy IPluginDemo...";
//                if(!manager->DestroyPlugin(pluginDemo))
//                {
//                    qDebug() << "Destroyed IPluginDemo failed!!!";
//                }
//                else
//                {
//                    qDebug() << "Destroyed IPluginDemo.";
//                }
            }
        }
    }
#endif
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMenu* MainWindow::createPopupMenu()
{
    return nullptr;
}

