#ifndef DOCKPLUGIN_H
#define DOCKPLUGIN_H

#include "IPlugin.h"
#include "UiPluginDemoIds.h"

#include <QToolButton>

class DockPlugin : public IDockPlugin
{
    Q_OBJECT
public:
    explicit DockPlugin(QObject *parent = nullptr);

    // IPlugin interface
public:
    virtual bool InitPlugin() override;
    virtual PLUGIN_TYPE GetPluginType() override;

public slots:
    virtual void MessageSlot(const QString &key, const QObject *msgObj) override;

    // IButtonPlugin interface
public:
    virtual QWidget *GetButtonWidget() override;
    virtual const QString GetCategory() override;
    virtual const QString GetPanel() override;

    // IDockPlugin interface
public:
    virtual QWidget *GetDockWidget() override;
    virtual Qt::DockWidgetArea GetDockPosition() override;

private:
    void onButtonClicked(bool checked);

private:
    QToolButton *m_button;
    QWidget *m_widget;
};

#endif // DOCKPLUGIN_H
