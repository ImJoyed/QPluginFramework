#include "RibbonPanel.h"
#include <QLine>

RibbonPanel::RibbonPanel(const QString &name, QWidget *parent)
    : m_name(name), QGroupBox(parent)
{
    // panel's layout
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(vLayout);
    // btn's layout
    QWidget *buttonsWidget = new QWidget(this);
    vLayout->addWidget(buttonsWidget);
    m_layout = new QHBoxLayout(buttonsWidget);
    m_layout->setAlignment(Qt::AlignCenter);
    buttonsWidget->setLayout(m_layout);
    // title
    m_nameLabel = new QLabel(name, this);
    m_nameLabel->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(m_nameLabel);
}

void RibbonPanel::AddButton(QWidget *button)
{
    if(!button)
        return;
    m_buttons.append(button);
    m_layout->addWidget(button);
}

void RibbonPanel::AddSeparator()
{
    QFrame* separator = createVLine();
    m_layout->addWidget(separator);
}

bool RibbonPanel::InsertButton(QWidget *&button, const int &index)
{
    if(!button)
        return false;
    if(index < 0 || index >= m_buttons.size())
    {
        m_buttons.append(button);
        m_layout->addWidget(button);
    }
    else
    {
        m_buttons.insert(index, button);
        m_layout->insertWidget(index, button);
    }
    return true;
}

void RibbonPanel::InsertSeparator(const int &index)
{
    QFrame* separator = createVLine();
    if(index < 0 || index >= m_buttons.count())
    {
        m_layout->addWidget(separator);
    }
    else
    {
        m_layout->insertWidget(index, separator);
    }
}

qsizetype RibbonPanel::GetCount() const
{
    return m_buttons.count();
}

bool RibbonPanel::RemoveAt(const int &index)
{
    if(index < 0 || index >= m_buttons.count())
        return false;
    delete m_buttons[index];
    m_buttons.removeAt(index);
    return true;
}

void RibbonPanel::RemoveAll()
{
    while (QLayoutItem* item = m_layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->deleteLater();

        delete item;
    }
    m_buttons.clear();
}

const QString &RibbonPanel::GetName()
{
    return m_name;
}

QFrame *RibbonPanel::createVLine()
{
    QFrame* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    return separator;
}
