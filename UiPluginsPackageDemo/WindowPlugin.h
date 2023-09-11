#ifndef WINDOWPLUGIN_H
#define WINDOWPLUGIN_H

#include "IPlugin.h"
#include "UiPluginDemoIds.h"

class WindowPlugin : public IWindowPlugin
{
    Q_OBJECT
public:
    explicit WindowPlugin(QObject *parent = nullptr);

    // IPlugin interface
public:
    virtual bool InitPlugin() override;
    virtual PLUGIN_TYPE GetPluginType() override;

public slots:
    virtual void MessageSlot(const QString &key, const QObject *msgObj) override;

    // IWindowPlugin interface
public:
    virtual QWidget *GetWindowWidget() override;

private:
    QWidget *m_widget;
};

#endif // WINDOWPLUGIN_H
