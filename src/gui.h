#ifndef GUI_H
#define GUI_H

#include "constants.h"
#include "par2deep2.h"

#include <QMainWindow>
#include <QSettings>

#include <string>

class pgui : public QMainWindow
{
    Q_OBJECT

public:
	explicit pgui(int argc, char *argv[], QWidget *parent = nullptr);
	~pgui() = default;

private:
	QSettings guisettings;
	par2deep2 p2d;
// 	QWidget *t;
// 	QWidget *m;
// 	QWidget *b
	void closeEvent(QCloseEvent*);
	void new_window(QWidget*,QWidget*,QWidget*);
	QWidget* topbar_frame(int);
	QWidget* start_options_frame(std::string);
	QWidget* start_actions_frame();
};

#endif // GUI_H
