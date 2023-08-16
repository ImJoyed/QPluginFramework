#include "RibbonBar.h"
#include <QHBoxLayout>
#include "RibbonCategory.h"

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
    RibbonCategory *category = new RibbonCategory(m_tabWidget);
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
