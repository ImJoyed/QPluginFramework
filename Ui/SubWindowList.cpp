#include "Ui/SubWindowList.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

SubWindowList::SubWindowList(QWidget *parent)
    : QDockWidget(parent)
{
    m_subWindowArea = new QMdiArea(parent);

    // delete title bar
    delete this->titleBarWidget();
    this->setTitleBarWidget(new QWidget(this));

    // widget
    QWidget *dockWdiget = new QWidget(this);
    this->setWidget(dockWdiget);
    // layout
    QVBoxLayout *layout = new QVBoxLayout(dockWdiget);
    dockWdiget->setLayout(layout);

    // title
    m_title = new QLabel(tr("Sub Windows List"), dockWdiget);
    layout->addWidget(m_title);
    // list
    m_subWindowList = new QListWidget(dockWdiget);
    layout->addWidget(m_subWindowList);


    connect(m_subWindowList, &QListWidget::currentItemChanged,
            this, QOverload<QListWidgetItem*, QListWidgetItem*>::of(&SubWindowList::onWindowChanged));
    connect(m_subWindowArea, &QMdiArea::subWindowActivated,
            this, QOverload<QMdiSubWindow*>::of(&SubWindowList::onWindowChanged));
}

void SubWindowList::closeEvent(QCloseEvent *event)
{
    return event->ignore();
}

void SubWindowList::AddSubWindow(QWidget *window)
{
    if(!m_subWindowArea || !window)
        return;
    // add to sub window area
    QMdiSubWindow *subWindow = m_subWindowArea->addSubWindow(window);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
    subWindow->showMaximized();
    subWindow->setWindowTitle(window->windowTitle());
    window->showMaximized();
    // add to sub window list
    QListWidgetItem *item = new QListWidgetItem(window->windowTitle());
    m_subWindowList->addItem(item);
    item->setData(Qt::UserRole, QVariant::fromValue((void*)subWindow));
}

QMdiArea *SubWindowList::GetSubWindowArea()
{
    return m_subWindowArea;
}

void SubWindowList::onWindowChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);

    QMdiSubWindow *subWindow = (QMdiSubWindow*)current->data(Qt::UserRole).value<void*>();
    if(!subWindow)
        return;
    m_subWindowArea->setActiveSubWindow(subWindow);
}

void SubWindowList::onWindowChanged(QMdiSubWindow *subWindow)
{
    for(int i = 0 ; i < m_subWindowList->count() ; ++i)
    {
        QListWidgetItem *item = m_subWindowList->item(i);
        if(!item)
            continue;
        QMdiSubWindow *itemSubWindow = (QMdiSubWindow*)item->data(Qt::UserRole).value<void*>();
        if(subWindow == itemSubWindow)
        {
            m_subWindowList->setCurrentItem(item);
            break;
        }
    }
}
