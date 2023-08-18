#ifndef UIPLUGINSPACKAGEDEMO_H
#define UIPLUGINSPACKAGEDEMO_H

#include "IPluginsPackage.h"

#define UiPluginsPackageDemoIID "uipluginspackagedemo.joyed.cn"
#define UiPluginsPackageDemoFILE "UiPluginsPackageDemo.json"

class UiPluginsPackageDemo : public IPluginsPackage
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID UiPluginsPackageDemoIID FILE UiPluginsPackageDemoFILE)
#endif

    Q_INTERFACES(IPluginsPackage)

public:
    explicit UiPluginsPackageDemo(QObject *parent = nullptr);

    // IPluginsPackage interface
public:
    virtual QList<QString> GetIds() override;
    virtual IPlugin *CreatePlugin(const QString &id) override;
};

#endif // UIPLUGINSPACKAGEDEMO_H
