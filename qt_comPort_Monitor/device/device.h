#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT

    QString m_name{};               //deviceName [sensorName:address]
    QStringList m_values{};         //current variable's values
public:
    explicit Device(QObject *parent = nullptr);
    ~Device();

    QString name() const;
    void setName(const QString &name);

    QString sensorName() const;
    QStringList values() const;


signals:
    void valuesChanged(QStringList);

public slots:
    void setValues(const QStringList &);
};

#endif // DEVICE_H
