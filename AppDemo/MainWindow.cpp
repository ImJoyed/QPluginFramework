#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QPluginLoader>
#include <QDebug>
#include "PluginsManager/IPluginsManager.h"
#include "PluginsDemo/IPluginDemo.h"
#include "PluginsCore/IPlugin.h"

#include "Ui/RibbonBar.h"
#include <QDateTime>
#include <QDockWidget>
#include <QListView>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ribbon bar
    RibbonBar *ribbonBar = new RibbonBar(this);
    this->setMenuWidget(ribbonBar);
    RibbonCategory *category;
    // tab 1
    category = ribbonBar->AddCategory("cate_1");
    RibbonPanel *panel;
    // tab1 group 1
    panel = category->AddPanel("panel_1_1");
    QPushButton *btn;
    btn = new QPushButton("btn_1_1_1");
    panel->AddButton(btn);
    btn = new QPushButton("btn_1_1_2");
    panel->AddButton(btn);
    panel->AddSeparator();
    btn = new QPushButton("btn_1_1_3");
    panel->AddButton(btn);
    // tab1 group 2
    panel = category->AddPanel("panel_1_2");
    btn = new QPushButton("btn_1_2_1");
    panel->AddButton(btn);
    btn = new QPushButton("btn_1_2_2");
    panel->AddButton(btn);
    // tab2
    category = ribbonBar->AddCategory("cate_2");
    // tab2 group 1
    panel = category->AddPanel("panel_2_1");
    btn = new QPushButton("btn_2_1_1");
    panel->AddButton(btn);

    // mdi area
    QMdiArea *mdiArea = new QMdiArea(this->centralWidget());
    this->setCentralWidget(mdiArea);
    QMdiSubWindow *subWindow;
    QWidget *viewWidget;
    // sub window 1
    viewWidget = new QWidget(this);
    new QLabel("sub window 1", viewWidget);
    subWindow = mdiArea->addSubWindow(viewWidget);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
    subWindow->showMaximized();
    subWindow->setWindowTitle("sub window 1");
    viewWidget->showMaximized();
    // sub window 2
    viewWidget = new QWidget(this);
    new QLabel("sub window 2", viewWidget);
    subWindow = mdiArea->addSubWindow(viewWidget);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
    subWindow->showMaximized();
    subWindow->setWindowTitle("sub window 2");
    viewWidget->showMaximized();
    // active sub window 1
    if(mdiArea->subWindowList().count() > 0)
        mdiArea->setActiveSubWindow(mdiArea->subWindowList().at(0));

    // dock widget
    QDockWidget *subWindowsTree = new QDockWidget();
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, subWindowsTree);
    QWidget *subWindowsTreeWidget = new QWidget(subWindowsTree);
    subWindowsTree->setWidget(subWindowsTreeWidget);
    // layout
    QVBoxLayout *subWindowsTreeLayout = new QVBoxLayout(subWindowsTree);
    subWindowsTreeWidget->setLayout(subWindowsTreeLayout);
    subWindowsTreeLayout->setAlignment(Qt::AlignTop);
    // title bar
    delete subWindowsTree->titleBarWidget();
    QWidget *subWindowsTreeTitleBar = new QWidget(subWindowsTree);
    subWindowsTree->setTitleBarWidget(subWindowsTreeTitleBar);
    QLabel *subWindowsTitleLabel = new QLabel("sub windows tree", subWindowsTreeWidget);
    subWindowsTreeLayout->addWidget(subWindowsTitleLabel);
    QListView *subWindowsList = new QListView(subWindowsTreeWidget);
    subWindowsTreeLayout->addWidget(subWindowsList);

    // status bar
    QWidget *statusBar = new QWidget(this);
    this->statusBar()->addPermanentWidget(statusBar);
    QHBoxLayout *statusBarLayout = new QHBoxLayout(this->statusBar());
    statusBar->setLayout(statusBarLayout);
    statusBarLayout->setAlignment(Qt::AlignRight);
    QLabel *dateTime = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"), this->statusBar());
    statusBarLayout->addWidget(dateTime);

#define LOAD_PLUGINS_MANAGER 0
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
#endif
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

