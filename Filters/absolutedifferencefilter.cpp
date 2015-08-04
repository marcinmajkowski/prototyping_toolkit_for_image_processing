#include <QtWidgets>

#include <opencv2/highgui/highgui.hpp>

#include "absolutedifferencefilter.h"

AbsoluteDifferenceFilter::AbsoluteDifferenceFilter(FilterObserver *observer, QObject *parent) :
    Filter("Absolute difference", observer, parent),
    m_adjustSecondInput(NONE)
{
}

QStringList AbsoluteDifferenceFilter::codeSnippet() const
{
    //TODO
    return Filter::codeSnippet();
}

cv::Mat &AbsoluteDifferenceFilter::process(cv::Mat &input)
{
    //TODO
    return Filter::process(input);
}

void AbsoluteDifferenceFilter::read(QDataStream &data)
{
    //TODO
}

void AbsoluteDifferenceFilter::write(QDataStream &data) const
{
    //TODO
}

void AbsoluteDifferenceFilter::setSecondInput(const QString &adaptiveMethod)
{
    //TODO
}

void AbsoluteDifferenceFilter::setAdjustSecondInput(int adjustSecondInput)
{
    //TODO
}

void AbsoluteDifferenceFilter::browse()
{
    //TODO change with cv::imread supported types
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName,
             QImageReader::supportedMimeTypes()) {
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();
    const QStringList picturesLocations =
            QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(m_pathLineEdit, tr("Open File"), picturesLocations.isEmpty() ?
                           QDir::currentPath() : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted &&
           !loadSecondInput(dialog.selectedFiles().first())) {
    }
}

QLayout *AbsoluteDifferenceFilter::dialogParametersGroupLayout()
{
    m_pathLineEdit = new QLineEdit;
    QPushButton *button = new QPushButton("Browse");
    connect(button, SIGNAL(clicked()), this, SLOT(browse()));

    QHBoxLayout *browseLayout = new QHBoxLayout;
    browseLayout->addWidget(m_pathLineEdit);
    browseLayout->addWidget(button);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("second input path:"), browseLayout);

    return formLayout;
}

QLabel *AbsoluteDifferenceFilter::dialogDescriptionLabel()
{
    return Filter::dialogDescriptionLabel();
}

bool AbsoluteDifferenceFilter::loadSecondInput(QString fileName)
{
    m_secondInputImage = cv::imread(fileName.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);
    if (m_secondInputImage.empty()) {
        QMessageBox::information(m_pathLineEdit, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return false;
    }

    m_pathLineEdit->setText(fileName);

    return true;
}
