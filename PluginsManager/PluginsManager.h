#ifndef PLUGINSMANAGER_H
#define PLUGINSMANAGER_H

#include "IPluginsManager.h"

#define PluginsManagerIID "pluginsmanager.joyed.cn"
#define PluginsManagerFILE "PluginsManager.json"

class PluginsManager : public IPluginsManager
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID PluginsManagerIID FILE PluginsManagerFILE)
#endif

    Q_INTERFACES(IPluginsManager)

public:
    explicit PluginsManager(QObject *parent = nullptr);

private:
    QMap<QString, IPluginsPackage*> m_pluginsPkg;
    QMap<QString, QList<IPlugin*>> m_plugins;

    // IPluginsManager interface
public:
    virtual bool InitPluginManager(QString plguinsDir = "../pluginspackage") override;
    virtual IPlugin *CreatePlugin(const QString &id, bool translateUi = true) override;
    virtual IPlugin *GetPlugin(const QString &id, const qsizetype &index = 0) override;
    virtual bool DestroyPlugin(const QString &id, const qsizetype &index = 0) override;
    virtual bool DestroyPlugin(const IPlugin* plugin) override;
    virtual qsizetype GetPluginsCount(const QString& id) override;
    virtual void SetRibbonBar(RibbonBar *ribbonBar) override;
    virtual void SetMainWindow(QMainWindow *mainWindow) override;
    virtual void SetSubWindowList(SubWindowList *subWindowList) override;

public slots:
    virtual void RegisterSlot(const IPlugin *plugin) override;
    virtual void MessageSlot(const QString& key, const QObject *msgObj) override;

private:
    RibbonBar *m_ribbonBar = nullptr;
    QMainWindow *m_mainWindow = nullptr;
    SubWindowList *m_subWindowList = nullptr;
};

#endif // PLUGINSMANAGER_H
