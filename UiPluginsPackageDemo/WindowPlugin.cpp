#include "WindowPlugin.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QApplication>
#include <QFile>

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
    QFile file(QApplication::applicationDirPath() + "/../etc/style.qss");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "QSS: open qss file failed!";
    }
    QString styleSheet = file.readAll();
    file.close();
    styleSheetEditor->appendPlainText(styleSheet);
    qApp->setStyleSheet(styleSheet);

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
    button = new QPushButton(tr("Save"), m_widget);
    ctrlLayout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [=](){
        QString styleSheet = styleSheetEditor->toPlainText();
        QFile file(QApplication::applicationDirPath() + "/../etc/style.qss");
        if(!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
        {
            qDebug() << "QSS: open qss file failed!";
        }
        file.write(styleSheet.toUtf8());
        file.close();
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
