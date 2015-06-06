#ifndef YJLVRSOUNDWIDGET_H
#define YJLVRSOUNDWIDGET_H

#include <QWidget>

namespace Ui {
class yJLVRSoundWidget;
}

class yJLVRSoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit yJLVRSoundWidget(QWidget *parent = 0);
    ~yJLVRSoundWidget();

private:
    Ui::yJLVRSoundWidget *ui;
};

#endif // YJLVRSOUNDWIDGET_H
