#ifndef GUI_H
#define GUI_H

#include "constants.h"
#include "par2deep2.h"

#include <QMainWindow>
#include <QSettings>

class pgui : public QMainWindow
{
    Q_OBJECT

public:
	explicit pgui(QWidget *parent = nullptr);
	~pgui() = default;
	par2deep2 *p2d;

private:
	QSettings guisettings {ORGNAME, APPNAME};
// 	QWidget *t;
// 	QWidget *m;
// 	QWidget *b
	void closeEvent(QCloseEvent*);
	void new_window(QWidget*,QWidget*,QWidget*);
	QWidget* topbar_frame(int);
	QWidget* start_options_frame(QString="");
	QWidget* start_actions_frame();
};

#endif // GUI_H
