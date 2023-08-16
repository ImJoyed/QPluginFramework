#ifndef SUBWINDOWLIST_H
#define SUBWINDOWLIST_H

#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QCloseEvent>
#include <QMdiArea>
#include <QMdiSubWindow>

class SubWindowList : public QDockWidget
{
    Q_OBJECT
public:
    explicit SubWindowList(QWidget *parent = nullptr);

protected:
    // ingore close event
    virtual void closeEvent(QCloseEvent *event) override;

public:
    void AddSubWindow(QWidget *window);
    QMdiArea *GetSubWindowArea();

private slots:
    void onWindowChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void onWindowChanged(QMdiSubWindow *subWindow);

private:
    QLabel *m_title = nullptr;
    QMdiArea *m_subWindowArea = nullptr;
    QListWidget *m_subWindowList = nullptr;
};

#endif // SUBWINDOWLIST_H
