#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QTabWidget;
class QToolBar;
class ImageWidget;
class CodeWidget;
class PipelineWidget;
class FiltersWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void undo();
    void about();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();
    void createDockWindows();
    void updateActions();

    QTabWidget *tabWidget;

    ImageWidget *imageWidget;
    CodeWidget *codeWidget;
    PipelineWidget *pipelineWidget;
    FiltersWidget *filtersWidget;

    QAction *openAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif // MAINWINDOW_H
