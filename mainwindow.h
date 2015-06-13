#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QTabWidget;
class QToolBar;
class QUndoStack;
class QUndoView;
class ImageWidget;
class CodeWidget;
class PipelineWidget;
class FiltersWidget;
class Filter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openProject();
    void openImage();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();
    void createDockWindows();
    void createUndoView();
    void updateActions();
    bool loadImageFile(const QString &fileName);
    QSharedPointer<Filter> createFilter(const QString &filterName);

    QTabWidget *tabWidget;

    ImageWidget *imageWidget;
    CodeWidget *codeWidget;
    PipelineWidget *pipelineWidget;
    FiltersWidget *filtersWidget;

    QUndoStack *undoStack;
    QUndoView *undoView;

    QAction *openProjectAct;
    QAction *openImageAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif // MAINWINDOW_H
