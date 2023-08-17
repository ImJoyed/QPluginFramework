#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QPluginLoader>
#include <QDebug>
#include "IPluginsManager.h"
#include "IPluginDemo.h"
#include "IPlugin.h"

#include "RibbonBar.h"
#include <QDateTime>
#include <QPushButton>

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
//    RibbonCategory *category;
//    // tab 1
//    category = ribbonBar->AddCategory("cate_1");
//    RibbonPanel *panel;
//    // tab1 group 1
//    panel = category->AddPanel("panel_1_1");
//    QPushButton *btn;
//    btn = new QPushButton("btn_1_1_1");
//    panel->AddButton(btn);
//    btn = new QPushButton("btn_1_1_2");
//    panel->AddButton(btn);
//    panel->AddSeparator();
//    btn = new QPushButton("btn_1_1_3");
//    panel->AddButton(btn);
//    // tab1 group 2
//    panel = category->AddPanel("panel_1_2");
//    btn = new QPushButton("btn_1_2_1");
//    panel->AddButton(btn);
//    btn = new QPushButton("btn_1_2_2");
//    panel->AddButton(btn);
//    // tab2
//    category = ribbonBar->AddCategory("cate_2");
//    // tab2 group 1
//    panel = category->AddPanel("panel_2_1");
//    btn = new QPushButton("btn_2_1_1");
//    panel->AddButton(btn);

    // dock widget
    SubWindowList *subWindowsList = new SubWindowList(this);
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, subWindowsList);

    // mdi area
    this->setCentralWidget(subWindowsList->GetSubWindowArea());
//    // add sub window
//    QWidget *viewWidget;
//    // sub window 1
//    viewWidget = new QWidget(this);
//    new QLabel("sub window 1", viewWidget);
//    viewWidget->setWindowTitle("sub window 1");
//    subWindowsTree->AddSubWindow(viewWidget);
//    // sub window 2
//    viewWidget = new QWidget(this);
//    new QLabel("sub window 2", viewWidget);
//    viewWidget->setWindowTitle("sub window 2");
//    subWindowsTree->AddSubWindow(viewWidget);
//    // active sub window 1
//    if(subWindowsTree->GetSubWindowArea()->subWindowList().count() > 0)
//        subWindowsTree->GetSubWindowArea()->setActiveSubWindow(subWindowsTree->GetSubWindowArea()->subWindowList().at(0));

    // status bar
    QWidget *statusBar = new QWidget(this);
    this->statusBar()->addPermanentWidget(statusBar);
    QHBoxLayout *statusBarLayout = new QHBoxLayout(this->statusBar());
    statusBar->setLayout(statusBarLayout);
    statusBarLayout->setAlignment(Qt::AlignRight);
    QLabel *dateTime = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"), this->statusBar());
    statusBarLayout->addWidget(dateTime);

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
                qDebug() << "Create plugins done.";

//                qDebug() << "Test IPluginDemo...";
//                IPlugin *plugin = manager->CreatePlugin(PLUGINDEMO_ID);
//                if(!plugin)
//                {
//                    qDebug() << "Create plugin failed!!!";
//                }
//                IPluginDemo *pluginDemo = dynamic_cast<IPluginDemo *>(plugin);
//                if(!pluginDemo)
//                {
//                    qDebug() << "Convert IPluginDemo failed!!!";
//                }
//                else
//                {
//                    pluginDemo->Echo("Hello.");
//                }
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

