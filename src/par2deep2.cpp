#include "par2deep2.h"

#include <popl.hpp>

#include <QCommandLineParser>
#include <QSettings>

// https://en.cppreference.com/w/cpp/filesystem/status

Opts configargparse(const QStringList &arguments)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to copy."));
    parser.addOptions({
        // A boolean option with a single name (-p)
        {"p",
            QCoreApplication::translate("main", "Show progress during copy")},
        // A boolean option with multiple names (-f, --force)
        {{"f", "force"},
            QCoreApplication::translate("main", "Overwrite existing files.")},
        // An option with a value
        {{"t", "target-directory"},
            QCoreApplication::translate("main", "Copy all source files into <directory>."),
            QCoreApplication::translate("main", "directory")},
    });

    // Process the actual command line arguments given by the user
    parser.process(arguments);

    const QStringList args = parser.positionalArguments();
    // source is args.at(0), destination is args.at(1)

//     bool showProgress = parser.isSet(showProgressOption);
//     bool force = parser.isSet(forceOption);
//     QString targetDir = parser.value(targetDirectoryOption);


    QSettings settings("/home/petra/misc/myapp.ini", QSettings::IniFormat);

    //unify ini and args
    Opts opts;
    return opts;
};

par2deep2::par2deep2(Opts opts)
{
	test = "brent";
};
