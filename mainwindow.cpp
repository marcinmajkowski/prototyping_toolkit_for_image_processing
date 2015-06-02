#include <QtWidgets>

#include "mainwindow.h"
#include "codewidget.h"
#include "pipelinewidget.h"
#include "filterswidget.h"
#include "imagewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createTabs();
    createDockWindows();

    setWindowTitle("Prototyping Toolkit for Image Processing");

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{

}

void MainWindow::undo()
{

}

void MainWindow::about() //TODO
{
    QMessageBox::about(this,
                       tr("About Prototyping Toolkit for Image Processing"),
                       tr("<p>The <b>Prototyping Toolkit for Image Processing"
                          "</b> is built with OpenCV and Qt libraries.</p>"
                          "<p>It's not finished yet...</p>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(undoAct);

    viewMenu = new QMenu(tr("&View"), this);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createTabs()
{
    imageWidget = new ImageWidget;
    codeWidget = new CodeWidget;

    tabWidget = new QTabWidget;
    tabWidget->addTab(imageWidget, "Image"); //TODO
    tabWidget->addTab(codeWidget, "Code"); //TODO

    setCentralWidget(tabWidget);
}

void MainWindow::createDockWindows()
{
    filtersWidget = new FiltersWidget;

    QDockWidget *dock = new QDockWidget(tr("Filters"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); //TODO
    dock->setWidget(filtersWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    pipelineWidget = new PipelineWidget;

    dock = new QDockWidget(tr("Pipeline"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); //TODO
    dock->setWidget(pipelineWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::updateActions()
{

}
