#ifndef COMMANDPLUGIN_H
#define COMMANDPLUGIN_H

#include "IPlugin.h"
#include "UiPluginDemoIds.h"

#include <QToolButton>

class CommandPlugin : public IButtonPlugin
{
    Q_OBJECT
public:
    explicit CommandPlugin(QObject *parent = nullptr);

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
    void onButtonClicked();

private:
    QToolButton *m_button;
};

#endif // COMMANDPLUGIN_H
