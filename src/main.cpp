#include "constants.h"
#include "par2deep2.h"
#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(APPNAME);
    QApplication::setApplicationVersion(APPVER);

    pgui w(argc,argv);
    w.show();

    return app.exec();
}

