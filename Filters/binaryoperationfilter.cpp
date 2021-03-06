#include <QDebug>
#include <QtWidgets>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "binaryoperationfilter.h"

BinaryOperationFilter::BinaryOperationFilter(const QString &name,
                                             FilterObserver *observer,
                                             QObject *parent) :
    Filter(name, observer, parent),
    m_convertSecondInput(false),
    m_inputsSizesMatch(false)
{

}

BinaryOperationFilter::~BinaryOperationFilter()
{
}

QStringList BinaryOperationFilter::codeSnippet() const
{
    QString referenceImageName = "reference_image";

    QStringList snippet;

    snippet << QString("%1 = cv::imread(\"%2\", %3);")
               .arg(referenceImageName)
               .arg(m_secondInputPath)
               .arg(m_convertSecondInput
                    ? "CV_LOAD_IMAGE_GRAYSCALE"
                    : "CV_LOAD_IMAGE_COLOR");

    snippet << QString("cv::%1(%2, %3, %4);")
               .arg(binaryOperationName())
               .arg("img")
               .arg(referenceImageName)
               .arg("img");

    return snippet;
}

cv::Mat &BinaryOperationFilter::process(cv::Mat &input)
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

    binaryOperation(input, secondInput);

    m_inputsSizesMatch = true;

    return input;
}

void BinaryOperationFilter::read(QDataStream &data)
{
    data >> m_secondInputPath;
    m_secondInputImage = cv::imread(m_secondInputPath.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);
    if (m_secondInputImage.empty()) {
        qDebug() << "File" << m_secondInputPath << "does not exist.";
    }

    emit updated();
}

void BinaryOperationFilter::write(QDataStream &data) const
{
    data << m_secondInputPath;
}

void BinaryOperationFilter::browse()
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
    QFileDialog dialog(m_pathLineEdit,
                       tr("Open File"),
                       picturesLocations.isEmpty()
                       ? QDir::currentPath()
                       : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted &&
           !loadSecondInput(dialog.selectedFiles().first())) {
    }

    emit updated();
}

QLayout *BinaryOperationFilter::dialogParametersGroupLayout()
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

QLabel *BinaryOperationFilter::dialogDescriptionLabel()
{
    //TODO using binaryOperationName();
    return Filter::dialogDescriptionLabel();
}

bool BinaryOperationFilter::loadSecondInput(QString fileName)
{
    m_secondInputImage = cv::imread(fileName.toUtf8().constData(),
                                    CV_LOAD_IMAGE_COLOR);
    if (m_secondInputImage.empty()) {
        QMessageBox::information(m_pathLineEdit,
                                 QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1")
                                 .arg(QDir::toNativeSeparators(fileName)));
        return false;
    }

    m_secondInputPath = fileName;
    if (m_pathLineEdit) {
        m_pathLineEdit->setText(m_secondInputPath);
    }

    return true;
}
