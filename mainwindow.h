#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QTabWidget;
class QToolBar;
class QTreeWidgetItem;
class ImageWidget;
class CodeWidget;
class PipelineWidget;
class FiltersWidget;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void openProject();
    void openImage();
    void resetPipeline();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void showFilterWidget(QListWidgetItem *item);
    void showInputImage(bool show);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();
    void createDockWindows();
    void updateActions();
    bool loadImageFile(const QString &fileName);

    QTabWidget *tabWidget;

    ImageWidget *imageWidget;
    CodeWidget *codeWidget;
    PipelineWidget *pipelineWidget;
    FiltersWidget *filtersWidget;

    QAction *openProjectAct;
    QAction *openImageAct;
    QAction *resetPipelineAct;
    QAction *showInputImageAct;
    QAction *exitAct;
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
    QToolBar *viewToolBar;
};

#endif // MAINWINDOW_H
