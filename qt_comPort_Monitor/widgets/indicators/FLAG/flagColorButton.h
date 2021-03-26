#ifndef FLAGCOLORBUTTON_H
#define FLAGCOLORBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QColor>
#include "flagElement.h"

#define BKGDCOLOR_PUSHBUTTON_DEFAULT   QString("#e1e1e1")
#define BKGDCOLOR_PUSHBUTTON_ACTIVE    Qt::red
#define BKGDCOLOR_PUSHBUTTON_DISABLE   QString("#f0f0f0")

class FlagColorButton : public QPushButton
{
    Q_OBJECT

    FlagElement *m_flag;
    QColor background{BKGDCOLOR_PUSHBUTTON_DEFAULT};      //дефолтный цвет фона кнопки
    QColor currentground{BKGDCOLOR_PUSHBUTTON_ACTIVE};    //текущий цвет фона кнопки

public:
    FlagColorButton(FlagElement *flag, QWidget *parent = nullptr);

    QColor getBackground() const;
    FlagElement *getFlag() const;
    bool contains(QString const&);

public slots:
    void changeBackground(int);
    void setBackground(const QColor &back);
    void restoreBackground();
};

#endif // FLAGCOLORBUTTON_H

/*
    https://ru.stackoverflow.com/questions/1005062/Перелив-из-одного-цвета-в-другой-qpushbutton
    https://www.w3.org/TR/SVG11/types.html#ColorKeywords
    https://doc.qt.io/qt-5/qcolor.html#setNamedColor
    http://doc.crossplatform.ru/qt/4.5.0/stylesheet-examples.html#customizing-qpushbutton
*/
