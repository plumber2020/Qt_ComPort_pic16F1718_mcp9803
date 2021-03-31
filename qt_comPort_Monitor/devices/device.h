#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT

    QString m_name{};               //deviceName [sensorName:address]
    QStringList m_values{};         //current variable's values
    QStringList m_flags{};          //current flags's values
public:
    explicit Device(QString name, QObject *parent = nullptr);

    QString name() const;
    QString sensorName() const;

    QStringList values() const;
    QStringList flags() const;

    void setValues(const QStringList &);
    void setFlags(const QStringList &);

signals:
    void valuesChanged(const QStringList&);
    void flagsChanged(const QStringList&);
};

#endif // DEVICE_H
