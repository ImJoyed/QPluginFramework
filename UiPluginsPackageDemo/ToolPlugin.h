#ifndef TOOLPLUGIN_H
#define TOOLPLUGIN_H

#include "IPlugin.h"
#include "UiPluginDemoIds.h"

#include <QToolButton>

class ToolPlugin : public IButtonPlugin
{
    Q_OBJECT
public:
    explicit ToolPlugin(QObject *parent = nullptr);

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

private slots:
    void onButtonClicked(bool checked);

private:
    QToolButton *m_button;
};

#endif // TOOLPLUGIN_H
