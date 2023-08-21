#include "WindowPlugin.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QApplication>

WindowPlugin::WindowPlugin(QObject *parent)
    : IWindowPlugin{parent}
{
    m_widget = new QWidget();
    m_widget->setWindowTitle(tr("Style Sheet Editor"));
    QVBoxLayout *layout = new QVBoxLayout(m_widget);
    m_widget->setLayout(layout);

    // editor
    QPlainTextEdit *styleSheetEditor = new QPlainTextEdit(m_widget);
    layout->addWidget(styleSheetEditor);

    // ctrl
    QHBoxLayout *ctrlLayout = new QHBoxLayout(m_widget);
    layout->addLayout(ctrlLayout);
    ctrlLayout->setAlignment(Qt::AlignRight);
    QPushButton *button = new QPushButton(tr("Apply"), m_widget);
    ctrlLayout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [=](){
        QString styleSheet = styleSheetEditor->toPlainText();
        qDebug() << "QSS:--------------------------------------";
        qDebug() << styleSheet;
        qApp->setStyleSheet(styleSheet);
    });
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
    return m_widget;
}
