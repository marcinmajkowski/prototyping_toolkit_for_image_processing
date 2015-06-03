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
    createCentralWidget();
    createDockWindows();

    setWindowTitle("Prototyping Toolkit for Image Processing");

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openProject()
{

}

void MainWindow::openImage()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName,
             QImageReader::supportedMimeTypes()) {
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();
    const QStringList picturesLocations =
            QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"), picturesLocations.isEmpty() ?
                           QDir::currentPath() : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted &&
           !loadImageFile(dialog.selectedFiles().first())) {
    }

    //TODO update actions? rather in loadImageFile
}

void MainWindow::undo()
{

}

void MainWindow::zoomIn()
{

}

void MainWindow::zoomOut()
{

}

void MainWindow::normalSize()
{

}

void MainWindow::fitToWindow()
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
    openProjectAct = new QAction(tr("&Open Project..."), this);
    openProjectAct->setShortcuts(QKeySequence::Open);
    //TODO setStatusTip
    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(openProject()));

    openImageAct = new QAction(tr("&Open Image..."), this);
    //TODO setShortcut
    //TODO setStatusTip
    connect(openImageAct, SIGNAL(triggered()), this, SLOT(openImage()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    //TODO setShortcut
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F")); //TODO setShortcut
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openProjectAct);
    fileMenu->addAction(openImageAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(undoAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    windowMenu = new QMenu(tr("&Window"), this);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(windowMenu);
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

void MainWindow::createCentralWidget()
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
    windowMenu->addAction(dock->toggleViewAction());

    pipelineWidget = new PipelineWidget;

    dock = new QDockWidget(tr("Pipeline"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); //TODO
    dock->setWidget(pipelineWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    windowMenu->addAction(dock->toggleViewAction());
}

void MainWindow::updateActions()
{

}

bool MainWindow::loadImageFile(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageWidget->setPixmap(QPixmap());
        return false;
    }
    imageWidget->setPixmap(QPixmap::fromImage(image));
    imageWidget->setScaleFactor(1.0);

    setWindowFilePath(fileName);
    return true;
}
