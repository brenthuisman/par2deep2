#include "constants.h"
#include "par2deep2.h"
#include "gui.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(APPNAME);
    QApplication::setApplicationVersion(APPVER);

    auto opts = configargparse(QCoreApplication::arguments());

    par2deep2 p2d(opts);
    pgui w;
	w.p2d = &p2d;
    w.show();

    return app.exec();
}
