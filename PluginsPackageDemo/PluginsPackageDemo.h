#ifndef PLUGINSPACKAGEDEMO_H
#define PLUGINSPACKAGEDEMO_H

#include "PluginsCore/IPluginsPackage.h"

#define PluginsPackageDemoIID "pluginspackagedemo.joyed.cn"
#define PluginsPackageDemoFILE "PluginsPackageDemo.json"

class PluginsPackageDemo : public IPluginsPackage
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID PluginsPackageDemoIID FILE PluginsPackageDemoFILE)
#endif

    Q_INTERFACES(IPluginsPackage)

public:
    explicit PluginsPackageDemo(QObject *parent = nullptr);

    // IPluginsPackage interface
public:
    virtual QList<QString> GetIds() override;
    virtual IPlugin *CreatePlugin(const QString &id) override;
};

#endif // PLUGINSPACKAGEDEMO_H
