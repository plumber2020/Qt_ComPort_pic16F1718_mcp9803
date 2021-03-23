#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QStringList m_values READ values WRITE setValues NOTIFY valuesChanged)
//    Q_PROPERTY(QStringList m_flags READ flags WRITE setFlags NOTIFY flagsChanged)


    QString m_name{};
    QStringList m_values{};
    QStringList m_flags{};
public:
    explicit Device(QString name, QObject *parent = nullptr);

    QString name() const;

    void setValues(const QStringList &);
    void setFlags(const QStringList &);

    QStringList values();
    QStringList flags();

signals:
    void valuesChanged(const QStringList &);
    void flagsChanged(const QStringList&);
};

#endif // DEVICE_H
