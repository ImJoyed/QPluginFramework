#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // The createPopupMenu() function creates popup menus when the main window receives context menu events.
    // The default implementation generates a menu with the checkable actions from the dock widgets and toolbars.
    // Override createPopupMenu, return nullptr.
    virtual QMenu* createPopupMenu() override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
