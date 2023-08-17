#ifndef RIBBONCATEGORY_H
#define RIBBONCATEGORY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QList>

class RibbonPanel;

class RibbonCategory : public QWidget
{
    Q_OBJECT
public:
    explicit RibbonCategory(const QString &name, QWidget *parent = nullptr);

public:
    RibbonPanel* AddPanel(const QString &name, const int &index = -1);
    bool RemovePanel(const int &index);

    qsizetype GetPanelCount() const;
    RibbonPanel* GetPanel(const int &index) const;
    QList<RibbonPanel*> GetAllPanels() const;

    const QString &GetName();

protected:
    QHBoxLayout *m_layout;
    QList<RibbonPanel*> m_panels;
    QString m_name;
};

#endif // RIBBONCATEGORY_H
