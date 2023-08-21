#include "DockPlugin.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDockWidget>
#include <QMessageBox>

DockPlugin::DockPlugin(QObject *parent)
    : IDockPlugin{parent}
{

}

bool DockPlugin::InitPlugin()
{
    m_button = new QToolButton();
    m_button->setIcon(QIcon("://Button.png"));
    m_button->setIconSize(QSize(32, 32));
    m_button->setText(tr("Tool Button"));
    m_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_button->setAutoRaise(true);
    m_button->setMouseTracking(true);
    m_button->setCheckable(true);
    m_button->setChecked(true);
    connect(m_button, &QToolButton::clicked, this, &DockPlugin::onButtonClicked);

    m_widget = new QWidget();
    m_widget->setWindowTitle(tr("Dock View"));
    QHBoxLayout *layout = new QHBoxLayout(m_widget);
    m_widget->setLayout(layout);
    layout->addWidget(new QLabel(tr("Label in Dock View"), m_widget));
    return true;
}

PLUGIN_TYPE DockPlugin::GetPluginType()
{
    return PLUGIN_TYPE::SINGLE;
}

void DockPlugin::MessageSlot(const QString &key, const QObject *msgObj)
{

}

QWidget *DockPlugin::GetButtonWidget()
{
    return m_button;
}

const QString DockPlugin::GetCategory()
{
    return tr("Plugins");
}

const QString DockPlugin::GetPanel()
{
    return tr("Dock Views");
}

QWidget *DockPlugin::GetDockWidget()
{
    return m_widget;
}

Qt::DockWidgetArea DockPlugin::GetDockPosition()
{
    return Qt::LeftDockWidgetArea;
}

void DockPlugin::onButtonClicked(bool checked)
{
    // m_widget's parent is not a QDockWidget！
    // m_widget's parent is the widget, which set by QDockWidget::setWidget(QWidget*) in PluginsManager.
    QObject *parent = m_widget->parent();
    QDockWidget *dockWidget = dynamic_cast<QDockWidget*>(parent);
    if(!dockWidget)
    {
        parent = parent->parent();
        dockWidget = dynamic_cast<QDockWidget*>(parent);
    }
    if(!dockWidget)
        return;

    QString msg = tr("Dock Button is %1.").arg(checked ? "checked" : "unchecked");
    this->setProperty("echo", msg);
    emit MessageSignal("echo.demoplugin.pluginspackage.joyed.cn", this);

    QMessageBox::information(nullptr, tr("Tips"), tr("You clicked Dock Button, now dock is %1.").arg(checked ? "show" : "hide"), QMessageBox::Ok);

    checked ? dockWidget->show() : dockWidget->hide();
}
