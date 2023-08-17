#ifndef IPLUGINSMANAGER_H
#define IPLUGINSMANAGER_H

#include <QtCore>

class IPluginsPackage;
class IPlugin;
class RibbonBar;
class QMainWindow;
class SubWindowList;

#define IPluginsManagerIID "iplugsmanager.joyed.cn"

class IPluginsManager : public QObject
{
    Q_OBJECT

public:
    explicit IPluginsManager(QObject* parent = nullptr) : QObject(parent)
    {

    }
    virtual bool InitPluginManager(QString plguinsDir = "../pluginspackage") = 0;
    virtual IPlugin* CreatePlugin(const QString& id, bool translateUi = true) = 0;
    virtual IPlugin* GetPlugin(const QString& id, const qsizetype& index = 0) = 0;
    virtual bool DestroyPlugin(const QString& id, const qsizetype& index = 0) = 0;
    virtual bool DestroyPlugin(const IPlugin* plugin) = 0;
    virtual qsizetype GetPluginsCount(const QString& id) = 0;
    virtual void SetRibbonBar(RibbonBar *ribbonBar) = 0;
    virtual void SetMainWindow(QMainWindow *mainWindow) = 0;
    virtual void SetSubWindowList(SubWindowList *subWindowList) = 0;

public slots:
    virtual void RegisterSlot(const IPlugin* plugin) = 0;
    virtual void MessageSlot(const QString& key, const QObject* msgObj) = 0;

signals:
    void MessageSignal(const QString& key, const QObject* msgObj);
};

Q_DECLARE_INTERFACE(IPluginsManager, IPluginsManagerIID)

#endif // IPLUGINSMANAGER_H
