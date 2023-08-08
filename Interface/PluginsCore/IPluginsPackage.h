#ifndef IPLUGINSPACKAGE_H
#define IPLUGINSPACKAGE_H

#include <QtCore>

class IPlugin;

#define IPluginsPackageIID "iplugspackage.joyed.cn"

class IPluginsPackage : public QObject
{
    Q_OBJECT

public:
    explicit IPluginsPackage(QObject* parent = nullptr) : QObject(parent)
    {

    }
    virtual QList<QString> GetIds() = 0;
    virtual IPlugin* CreatePlugin(const QString& id) = 0;

signals:
    void RegisterSignal(const IPlugin* obj);
};

Q_DECLARE_INTERFACE(IPluginsPackage, IPluginsPackageIID)

#endif // IPLUGINSPACKAGE_H
