/********************************************************************************
** Form generated from reading UI file 'tesseractwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESSERACTWIDGET_H
#define UI_TESSERACTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TesseractWidget
{
public:

    void setupUi(QWidget *TesseractWidget)
    {
        if (TesseractWidget->objectName().isEmpty())
            TesseractWidget->setObjectName(QStringLiteral("TesseractWidget"));
        TesseractWidget->resize(400, 300);

        retranslateUi(TesseractWidget);

        QMetaObject::connectSlotsByName(TesseractWidget);
    } // setupUi

    void retranslateUi(QWidget *TesseractWidget)
    {
        TesseractWidget->setWindowTitle(QApplication::translate("TesseractWidget", "Tesseract Inspired By Minecraft", 0));
    } // retranslateUi

};

namespace Ui {
    class TesseractWidget: public Ui_TesseractWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESSERACTWIDGET_H
