#ifndef RIBBONPANEL_H
#define RIBBONPANEL_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>

class RibbonPanel : public QGroupBox
{
    Q_OBJECT
public:
    explicit RibbonPanel(const QString &name, QWidget *parent = nullptr);

public:
    void AddButton(QWidget* button);
    void AddSeparator();
    bool InsertButton(QWidget* &button, const int &index = -1);
    void InsertSeparator(const int &index = -1);

    qsizetype GetCount() const;
    bool RemoveAt(const int &index);
    void RemoveAll();

private:
    QFrame* createVLine();

protected:
    QHBoxLayout* m_layout;
    QLabel *m_name;
    QList<QWidget*> m_buttons;
};

#endif // RIBBONPANEL_H
