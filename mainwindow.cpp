#include <QtWidgets>
#include <QDebug>

#include "mainwindow.h"
#include "codewidget.h"
#include "filterswidget.h"
#include "imagewidget.h"
#include "pipelinewidget.h"
#include "pipelinewidgetitem.h"
#include "Filters/filter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    undoStack = new QUndoStack(this);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createCentralWidget();
    createDockWindows();
#ifndef QT_NO_DEBUG
    createUndoView();
#endif

    // every loaded image goes from loadImageFile() through the pipeline
    // to the imageWidget
    //TODO
//    connect(pipelineModel, SIGNAL(resultChanged(QPixmap)),
//            imageWidget, SLOT(setPixmap(QPixmap)));


    setWindowTitle("Prototyping Toolkit for Image Processing");

    loadImageFile(":/Images/lena.jpg");

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
}

void MainWindow::zoomIn()
{
    double newScaleFactor = imageWidget->scaleFactor() * 1.25;
    imageWidget->setScaleFactor(newScaleFactor);

    updateActions();
}

void MainWindow::zoomOut()
{
    double newScaleFactor = imageWidget->scaleFactor() * 0.8;
    imageWidget->setScaleFactor(newScaleFactor);

    updateActions();
}

void MainWindow::normalSize()
{
    imageWidget->setScaleFactor(1.0);

    updateActions();
}

void MainWindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    imageWidget->setFitToWindow(fitToWindow);
    updateActions();
}


void MainWindow::about() //TODO
{
    QMessageBox::about(this,
                       tr("About Prototyping Toolkit for Image Processing"),
                       tr("<p>The <b>Prototyping Toolkit for Image Processing"
                          "</b> is built with OpenCV and Qt libraries.</p>"
                          "<p>It's not finished yet...</p>"));
}

void MainWindow::showFilterWidget(QListWidgetItem *item)
{
    PipelineWidgetItem *pipelineItem = dynamic_cast<PipelineWidgetItem*>(item);
    if (!pipelineItem) {
        return;
    }

    QDialog *dialog = pipelineItem->filter()->dialog();
    if (dialog) {
        dialog->setParent(this, Qt::Dialog);
        int result = dialog->exec();
    }
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

    undoAct = undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));

    redoAct = undoStack->createRedoAction(this, tr("&Redo"));
    redoAct->setShortcuts(QKeySequence::Redo);
    //TODO setStatusTip
//    redoAct->setStatusTip(tr("Undo the last editing action"));

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
    editMenu->addAction(redoAct);

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
    statusBar()->setSizeGripEnabled(false); //TODO just try to fix Ubuntu bug
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

    connect(pipelineWidget, SIGNAL(itemActivated(QListWidgetItem*)),
            this, SLOT(showFilterWidget(QListWidgetItem*)));

    dock = new QDockWidget(tr("Pipeline"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); //TODO
    dock->setWidget(pipelineWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    windowMenu->addAction(dock->toggleViewAction());

    connect(filtersWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            pipelineWidget, SLOT(appendItem(QTreeWidgetItem*,int)));
}

void MainWindow::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void MainWindow::updateActions()
{
    double scaleFactor = imageWidget->scaleFactor();
    zoomInAct->setEnabled(!fitToWindowAct->isChecked() && scaleFactor < 3.0);
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked() && scaleFactor > 0.333);
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
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

    //TODO
    imageWidget->setPixmap(QPixmap::fromImage(image));
//    pipelineModel->setInitialPixmap(QPixmap::fromImage(image));

    setWindowFilePath(fileName);

    fitToWindowAct->setEnabled(true);
    updateActions();

    return true;
}
