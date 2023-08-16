#ifndef RIBBONBAR_H
#define RIBBONBAR_H

#include <QWidget>
#include <QTabWidget>
#include <QList>
#include "Ui/RibbonCategory.h"

class RibbonBar : public QWidget
{
    Q_OBJECT
public:
    explicit RibbonBar(QWidget *parent = nullptr);

public:
    RibbonCategory* AddCategory(const QString &name, const int &index = -1);
    bool RemoveCategory(const int &index);

    qsizetype GetCategoryCount() const;
    RibbonCategory* GetCategory(const int &index) const;


protected:
    QTabWidget *m_tabWidget;
    QList<RibbonCategory*> m_categories;
};

#endif // RIBBONBAR_H
