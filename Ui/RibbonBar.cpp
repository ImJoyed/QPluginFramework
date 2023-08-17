#include "RibbonBar.h"
#include <QHBoxLayout>
#include "RibbonCategory.h"
#include "RibbonPanel.h"

RibbonBar::RibbonBar(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    this->setLayout(layout);

    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);
    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->setMovable(false);
}

RibbonCategory *RibbonBar::AddCategory(const QString &name, const int &index)
{
    RibbonCategory *category = new RibbonCategory(name ,m_tabWidget);
    if(index < 0 || index >= m_categories.count())
    {
        m_categories.append(category);
        m_tabWidget->addTab(category, name);
    }
    else
    {
        m_categories.insert(index, category);
        m_tabWidget->insertTab(index, category, name);
    }
    return category;
}

bool RibbonBar::RemoveCategory(const int &index)
{
    if(index < 0 || index >= m_categories.count())
        return false;
    m_tabWidget->removeTab(index);
    delete m_categories[index];
    m_categories.removeAt(index);
    return true;
}

qsizetype RibbonBar::GetCategoryCount() const
{
    return m_categories.count();
}

RibbonCategory *RibbonBar::GetCategory(const int &index) const
{
    if(index < 0 || index >= m_categories.count())
        return nullptr;
    return m_categories.at(index);
}

void RibbonBar::AddButton(const QString &categoryName, const QString &panelName, QWidget *button)
{
    int i , j;
    for(i = 0 ; i < m_categories.count() ; ++i)
    {
        RibbonCategory *category = m_categories.at(i);
        if(category->GetName() == categoryName)
        {
            for(j = 0 ; j < category->GetAllPanels().count() ; ++j)
            {
                RibbonPanel *panel = category->GetAllPanels().at(j);
                if(panel->GetName() == panelName)
                {
                    panel->AddButton(button);
                    break;
                }
            }
            break;
        }
    }
    // has category
    if(i != m_categories.count())
    {
        RibbonCategory *category = m_categories.at(i);
        // no panel
        if(j == category->GetPanelCount())
        {
            RibbonPanel *panel = category->AddPanel(panelName);
            panel->AddButton(button);
        }
    }
    // no category
    else
    {
        RibbonCategory *category = this->AddCategory(categoryName);
        RibbonPanel *panel = category->AddPanel(panelName);
        panel->AddButton(button);
    }
}
