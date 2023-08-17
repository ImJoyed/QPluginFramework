#include "RibbonCategory.h"
#include "RibbonPanel.h"

RibbonCategory::RibbonCategory(const QString &name, QWidget *parent)
    : m_name(name), QWidget{parent}
{
    m_layout = new QHBoxLayout(this);
    m_layout->setAlignment(Qt::AlignLeft);
    this->setLayout(m_layout);
}

RibbonPanel *RibbonCategory::AddPanel(const QString &name, const int &index)
{
    RibbonPanel *panel = new RibbonPanel(name, this);
    if(index < 0 || index >= m_panels.count())
    {
        m_panels.append(panel);
        m_layout->addWidget(panel);
    }
    else
    {
        m_panels.insert(index, panel);
        m_layout->insertWidget(index, panel);
    }
    return panel;
}

bool RibbonCategory::RemovePanel(const int &index)
{
    if(index < 0 || index >= m_panels.count())
        return false;
    delete m_panels[index];
    m_panels.removeAt(index);
    return true;
}

qsizetype RibbonCategory::GetPanelCount() const
{
    return m_panels.count();
}

RibbonPanel *RibbonCategory::GetPanel(const int &index) const
{
    if(index < 0 || index >= m_panels.count())
        return nullptr;
    return m_panels.at(index);
}

QList<RibbonPanel *> RibbonCategory::GetAllPanels() const
{
    return m_panels;
}

const QString &RibbonCategory::GetName()
{
    return m_name;
}
