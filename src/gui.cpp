#include "gui.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDir>

#include <iostream>

pgui::pgui(QWidget *parent) :
    QMainWindow(parent)
{
	setWindowTitle(APPNAME);
	resize(800, 800);
	setWindowIcon(QIcon("../par2deep.ico"));

	auto geometry = guisettings.value("geometry", saveGeometry());
	auto lastdir = guisettings.value("lastdir", QDir::homePath()).toString();

	restoreGeometry(geometry.toByteArray());

	new_window(topbar_frame(0), start_options_frame(lastdir), start_actions_frame());
}

void pgui::closeEvent(QCloseEvent *event)
{
	guisettings.setValue("geometry", saveGeometry());
// 	std::cout<<p2d->test;
}

void pgui::new_window(QWidget *t,QWidget *m,QWidget *b)
{
	auto subframe = new QWidget();
	auto mainLayout = new QVBoxLayout();
	mainLayout->addWidget(t,0);
	t->setFixedHeight(100);
	mainLayout->addWidget(m,1);
	mainLayout->addWidget(b,0);
	b->setFixedHeight(100);
	subframe->setLayout(mainLayout);
	setCentralWidget(subframe);
}

QWidget* pgui::topbar_frame(int stage){
	auto subframe = new QWidget();
	auto l = new QHBoxLayout();
	l->addStretch(1);
	QStringList labels = {"Start","Proposed actions","Executing actions","Report","Further actions","Final report"};
	labels.replace(stage,"<u>"+labels.at(stage)+"</u>");
	for (auto label : labels){
		l->addWidget(new QLabel(label));
		l->insertSpacing(-1,10);
	}
	l->addStretch(1);
	subframe->setLayout(l);
	return subframe;
}


QWidget* pgui::start_options_frame(QString chosen_dir){
	auto subframe = new QWidget();
	return subframe;
}


QWidget* pgui::start_actions_frame(){
	auto ssa_btn = new QPushButton("Check directory contents");
	//ssa_btn->clicked.connect(set_start_actions)
	
	auto subframe = new QWidget();
	auto l = new QHBoxLayout();
	l->addStretch(1);
	l->addWidget(ssa_btn);
	l->addStretch(1);
	subframe->setLayout(l);
	return subframe;
}
