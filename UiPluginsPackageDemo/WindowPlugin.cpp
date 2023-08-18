#include "WindowPlugin.h"
#include <QLabel>

WindowPlugin::WindowPlugin(QObject *parent)
    : IWindowPlugin{parent}
{

}

bool WindowPlugin::InitPlugin()
{
    return true;
}

PLUGIN_TYPE WindowPlugin::GetPluginType()
{
    return PLUGIN_TYPE::SINGLE;
}

void WindowPlugin::MessageSlot(const QString &key, const QObject *msgObj)
{

}

QWidget *WindowPlugin::GetWindowWidget()
{
    QWidget *window = new QWidget();
    window->setWindowTitle(tr("Sub Window"));
    new QLabel(tr("Label in Sub Window"), window);
    return window;
}
