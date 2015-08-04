#include <QDebug>
#include <QtWidgets>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "bitwiseandfilter.h"

BitwiseAndFilter::BitwiseAndFilter(FilterObserver *observer, QObject *parent) :
    Filter("Bitwise and", observer, parent),
    m_convertSecondInput(false),
    m_inputsSizesMatch(false),
    m_adjustSecondInput(NONE)
{
}

QStringList BitwiseAndFilter::codeSnippet() const
{
    //TODO
    return Filter::codeSnippet();
}

cv::Mat &BitwiseAndFilter::process(cv::Mat &input)
{
    if (input.size != m_secondInputImage.size) {
        m_inputsSizesMatch = false;
        return input;
    }

    cv::Mat secondInput;

    switch(input.type()) {
    case CV_8UC1:
        cv::cvtColor(m_secondInputImage, secondInput, CV_RGB2GRAY);
        m_convertSecondInput = true;
        break;
    case CV_8UC3:
        secondInput = m_secondInputImage;
        m_convertSecondInput = false;
        break;
    case CV_8UC4:
        cv::cvtColor(m_secondInputImage, secondInput, CV_RGB2RGBA);
        m_convertSecondInput = false;
        break;
    }

    cv::bitwise_and(input, secondInput, input);

    m_inputsSizesMatch = true;

    return input;
}

void BitwiseAndFilter::read(QDataStream &data)
{
    //TODO
}

void BitwiseAndFilter::write(QDataStream &data) const
{
    //TODO
}

void BitwiseAndFilter::setAdjustSecondInput(int adjustSecondInput)
{
    //TODO
}

void BitwiseAndFilter::browse()
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

    emit updated();
}

QLayout *BitwiseAndFilter::dialogParametersGroupLayout()
{
    m_pathLineEdit = new QLineEdit(m_secondInputPath);
    QPushButton *button = new QPushButton("Browse");
    connect(button, SIGNAL(clicked()), this, SLOT(browse()));

    QHBoxLayout *browseLayout = new QHBoxLayout;
    browseLayout->addWidget(m_pathLineEdit);
    browseLayout->addWidget(button);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("second input path:"), browseLayout);

    return formLayout;
}

QLabel *BitwiseAndFilter::dialogDescriptionLabel()
{
    return Filter::dialogDescriptionLabel();
}

bool BitwiseAndFilter::loadSecondInput(QString fileName)
{
    m_secondInputImage = cv::imread(fileName.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);
    if (m_secondInputImage.empty()) {
        QMessageBox::information(m_pathLineEdit, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return false;
    }

    m_secondInputPath = fileName;
    m_pathLineEdit->setText(m_secondInputPath);

    return true;
}
