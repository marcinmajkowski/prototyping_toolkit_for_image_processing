#ifndef STRUCTURINGELEMENTARGUMENT_H
#define STRUCTURINGELEMENTARGUMENT_H

#include <QObject>
#include <QLayout>
#include <QString>
#include <QDataStream>
#include <QMap>
#include <opencv2/core/core.hpp>

class StructuringElementArgument : public QObject
{
    Q_OBJECT
public:
    explicit StructuringElementArgument(int shape, int sizeWidth,
                                        int sizeHeight, QObject *parent = 0);
    QLayout *layout();
    QString text() const;
    cv::Mat value();

    //TODO replace with << and >> operators
    void read(QDataStream &data);
    void write(QDataStream &data) const;

signals:
    void updated();

public slots:
    void setShape(const QString &shape);
    void setSizeWidth(int sizeWidth);
    void setSizeHeight(int sizeHeight);

private:
    int m_shape;
    QMap<int, QString> m_shapeMap;
    int m_sizeWidth;
    int m_sizeHeight;
    cv::Point m_anchor;
};

#endif // STRUCTURINGELEMENTARGUMENT_H
