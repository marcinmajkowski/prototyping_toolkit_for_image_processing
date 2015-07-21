#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "erodefilter.h"

ErodeFilter::ErodeFilter(FilterObserver *observer, QObject *parent) :
    Filter("Dilate", observer, parent),
    m_kernel(cv::Mat()),
    m_anchor(cv::Point(-1, - 1)),
    m_iterations(1),
    m_borderType(cv::BORDER_CONSTANT),
    m_borderValue(cv::morphologyDefaultBorderValue())
{
    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");
//    m_borderTypeMap.insert(cv::BORDER_WRAP, "cv::BORDER_WRAP"); // cv::exception
}

QStringList ErodeFilter::codeSnippet() const
{
    //TODO
    QString kernel = "cv::Mat()";
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("erode")
            .arg("img")
            .arg("img")
            .arg(kernel)
            .arg(anchor)
            .arg(m_iterations)
            .arg(m_borderTypeMap[m_borderType])
            .arg(borderValue);

    snippet << line;

    return snippet;
}

QDialog *ErodeFilter::createDialog(QWidget *parent)
{
    //TODO
    QDialog *dialog = new QDialog(parent);

    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>erode</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; Point <b>anchor</b>,<br>\
                            &nbsp; int <b>iterations</b>,<br>\
                            &nbsp; int <b>borderType</b>,<br>\
                            &nbsp; const Scalar &<b>borderValue</b>,<br>\
                            )");

    QGroupBox *parametersGroup = new QGroupBox(tr("Parameters"));

    QFormLayout *formLayout = new QFormLayout;

    QSlider *iterations = new QSlider(Qt::Horizontal);
    iterations->setRange(1, 30);
    iterations->setValue(m_iterations);
    formLayout->addRow(new QLabel("iterations:"), iterations);
    connect(iterations, SIGNAL(valueChanged(int)),
            this, SLOT(setIterations(int)));

    QComboBox *borderType = new QComboBox;
    foreach (const QString &s, m_borderTypeMap) {
        borderType->addItem(s);
    }

    borderType->setCurrentText(m_borderTypeMap[m_borderType]);
    formLayout->addRow(new QLabel("type:"), borderType);
    connect(borderType, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setBorderType(QString)));

    parametersGroup->setLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(signatureLabel);
    mainLayout->addWidget(parametersGroup);
    mainLayout->addWidget(buttonBox);

    dialog->setLayout(mainLayout);

    dialog->setWindowTitle(tr("%1 %2").arg(m_name).arg("settings"));

    return dialog;
}

cv::Mat &ErodeFilter::process(cv::Mat &input)
{
    cv::erode(input, input, m_kernel, m_anchor, m_iterations, m_borderType, m_borderValue);

    return input;
}

void ErodeFilter::setBorderType(const QString &borderType)
{
    m_borderType = m_borderTypeMap.key(borderType);

    emit updated();
}

void ErodeFilter::setIterations(int iterations)
{
    m_iterations = iterations;

    emit updated();
}
