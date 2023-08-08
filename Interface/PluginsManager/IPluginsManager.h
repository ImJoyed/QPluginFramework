#ifndef IPLUGINSMANAGER_H
#define IPLUGINSMANAGER_H

#include <QtCore>

class IPluginsPackage;
class IPlugin;

#define IPluginsManagerIID "iplugsmanager.joyed.cn"

class IPluginsManager : public QObject
{
    Q_OBJECT

public:
    explicit IPluginsManager(QObject* parent = nullptr) : QObject(parent)
    {

    }
    // 访问IPluginsPackage::GetIds，填充m_pluginsPkg，关联IPluginsPackage::Register和IPluginsManager::onRegister
    virtual bool InitPluginManager(QString plguinsDir = "../pluginspackage") = 0;
    // 访问IPluginsPackage::CreatePlugin，插入m_plugins
    virtual IPlugin* CreatePlugin(const QString& id) = 0;
    // 访问m_plugins
    virtual IPlugin* GetPlugin(const QString& id, const qsizetype& index = 0) = 0;
    // 从m_plugins中删除
    virtual bool DestroyPlugin(const QString& id, const qsizetype& index = 0) = 0;
    virtual bool DestroyPlugin(const IPlugin* plugin) = 0;
    // 返回m_plugins中的数量
    virtual qsizetype GetPluginsCount(const QString& id) = 0;

public slots:
    // 收到注册消息
    // connect(this, Message, plugin, onMessage)
    // connect(plugin, Message, this, onMessage)
    virtual void onRegister(const IPlugin* plugin) = 0;
    virtual void onMessage(const QString& key, const QVariant& msg) = 0;

signals:
    void Message(const QString& key, const QVariant& msg);
};

Q_DECLARE_INTERFACE(IPluginsManager, IPluginsManagerIID)

#endif // IPLUGINSMANAGER_H
