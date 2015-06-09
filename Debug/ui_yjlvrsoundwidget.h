/********************************************************************************
** Form generated from reading UI file 'yjlvrsoundwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YJLVRSOUNDWIDGET_H
#define UI_YJLVRSOUNDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_yJLVRSoundWidget
{
public:

    void setupUi(QWidget *yJLVRSoundWidget)
    {
        if (yJLVRSoundWidget->objectName().isEmpty())
            yJLVRSoundWidget->setObjectName(QStringLiteral("yJLVRSoundWidget"));
        yJLVRSoundWidget->resize(800, 600);

        retranslateUi(yJLVRSoundWidget);

        QMetaObject::connectSlotsByName(yJLVRSoundWidget);
    } // setupUi

    void retranslateUi(QWidget *yJLVRSoundWidget)
    {
        yJLVRSoundWidget->setWindowTitle(QApplication::translate("yJLVRSoundWidget", "yJLVRSound Inspired By Minecraft", 0));
    } // retranslateUi

};

namespace Ui {
    class yJLVRSoundWidget: public Ui_yJLVRSoundWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YJLVRSOUNDWIDGET_H
