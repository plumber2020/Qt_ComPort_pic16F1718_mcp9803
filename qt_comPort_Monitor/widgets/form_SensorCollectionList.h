#ifndef FORM_SENSORCOLLECTIONLIST_H
#define FORM_SENSORCOLLECTIONLIST_H

#include <QWidget>
#include <QHash>
#include "sensor.h"

namespace Ui {
class Form_SensorCollectionList;
}

class Form_SensorCollectionList : public QWidget
{
    Q_OBJECT
    QHash<QString, QStringList> m_sensorCollectionStrings{};
    QHash<QString, Sensor> m_sensors{};
public:
    explicit Form_SensorCollectionList(QWidget *parent = nullptr);
    ~Form_SensorCollectionList();

    void uploadCollection();

private:
    Ui::Form_SensorCollectionList *ui;
};

#endif // FORM_SENSORCOLLECTIONLIST_H
