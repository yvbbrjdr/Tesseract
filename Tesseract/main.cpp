#include "loginwidget.h"
#include <bass.h>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BASS_Init(-1,44100,BASS_DEVICE_3D,0,0);
    BASS_Set3DFactors(1,1,0);
    BASS_SetConfig(BASS_CONFIG_3DALGORITHM,BASS_3DALG_FULL);
    LoginWidget w;
    w.show();
    return a.exec();
}
