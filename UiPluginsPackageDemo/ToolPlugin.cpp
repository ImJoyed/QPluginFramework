#include "ToolPlugin.h"

#include <QMessageBox>

ToolPlugin::ToolPlugin(QObject *parent)
    : IButtonPlugin{parent}
{
}

bool ToolPlugin::InitPlugin()
{
    m_button = new QToolButton();
    m_button->setIcon(QIcon("://Button.png"));
    m_button->setIconSize(QSize(32, 32));
    m_button->setText(tr("Tool Button"));
    m_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_button->setAutoRaise(true);
    m_button->setMouseTracking(true);
    m_button->setCheckable(true);
    connect(m_button, &QToolButton::clicked, this, &ToolPlugin::onButtonClicked);
    return true;
}

PLUGIN_TYPE ToolPlugin::GetPluginType()
{
    return PLUGIN_TYPE::SINGLE;
}

void ToolPlugin::MessageSlot(const QString &key, const QObject *msgObj)
{

}

QWidget *ToolPlugin::GetButtonWidget()
{
    return m_button;
}

const QString ToolPlugin::GetCategory()
{
    return tr("Plugins");
}

const QString ToolPlugin::GetPanel()
{
    return tr("Buttons");
}

void ToolPlugin::onButtonClicked(bool checked)
{
    QString msg = tr("Tool Button is %1.").arg(checked ? "checked" : "unchecked");
    this->setProperty("echo", msg);
    emit MessageSignal("echo.demoplugin.pluginspackage.joyed.cn", this);

    QMessageBox::information(nullptr, tr("Tips"), tr("You clicked Command Button, now is %1.").arg(checked ? "checked" : "unchecked"), QMessageBox::Ok);
}
