#include "CommandPlugin.h"
#include <QMessageBox>

CommandPlugin::CommandPlugin(QObject *parent)
    : IButtonPlugin{parent}
{
}

bool CommandPlugin::InitPlugin()
{
    m_button = new QToolButton();
    m_button->setIcon(QIcon("://Button.png"));
    m_button->setIconSize(QSize(32, 32));
    m_button->setText(tr("Command Button"));
    m_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_button->setAutoRaise(true);
    m_button->setMouseTracking(true);
    connect(m_button, &QToolButton::clicked, this, &CommandPlugin::onButtonClicked);
    return true;
}

PLUGIN_TYPE CommandPlugin::GetPluginType()
{
    return PLUGIN_TYPE::SINGLE;
}

void CommandPlugin::MessageSlot(const QString &key, const QObject *msgObj)
{

}

QWidget *CommandPlugin::GetButtonWidget()
{
    return m_button;
}

const QString CommandPlugin::GetCategory()
{
    return tr("Plugins");
}

const QString CommandPlugin::GetPanel()
{
    return tr("Buttons");
}

void CommandPlugin::onButtonClicked()
{
    QString msg = tr("Command Button");
    this->setProperty("echo", msg);
    emit MessageSignal("echo.demoplugin.pluginspackage.joyed.cn", this);

    QMessageBox::information(nullptr, tr("Tips"), tr("You clicked Command Button."), QMessageBox::Ok);
}
