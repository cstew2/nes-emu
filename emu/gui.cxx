#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QScrollArea>
#include <QFileDialog> 
#include <QString>

#include "emu/gui.hxx"
#include "sim/asm.h"
#include "sim/code.h"
#include "sim/hex.h"


int main_gui(void)
{
	int argc = 1;
	char prog_name[] = "cnes";
	char *argv[] = {prog_name};
	QApplication app(argc, argv);

	//main Window
	QWidget *window = new QWidget();
	window->setWindowTitle(QString::fromUtf8("cnes"));
	window->setFixedSize(256,240);

	//Menu setup
	QMenuBar *menu_bar = new QMenuBar(window);
	
	QMenu *file = new QMenu(QString::fromUtf8("File"), window);
	QFileDialog *file_picker = new QFileDialog(window,
						   QString::fromUtf8("Choose a file "),
						   QString::fromUtf8("~/"),
						   QString::fromUtf8("nes rom files (*.nes)"));
	file->addAction(QString::fromUtf8("Open"), file_picker, SLOT(show()));
	
	
	QWidget *file_info_window = new QWidget();
	file_info_window->setWindowTitle(QString::fromUtf8("File Info"));
	file->addAction(QString::fromUtf8("File Info"), file_info_window, SLOT(show()));
	
	file->addAction(QString::fromUtf8("Quit"), window, SLOT(close()));
	menu_bar->addMenu(file);

	
	QMenu *prog = new QMenu(QString::fromUtf8("Prog"));
	//Hex Window
	QWidget *hex_window =  new QWidget();
	hex_window->resize(256,240);
	prog->addAction(QString("Hex"), hex_window, SLOT(show()));

	//Code Window
	QWidget code_window;
	code_window.resize(256,240);
	prog->addAction(QString("Code"), &code_window, SLOT(show()));

	//Register Window
	QWidget registers_window;
	registers_window.resize(256,240);
	prog->addAction(QString("Registers"), &registers_window, SLOT(show()));
	
	//Ram Window
	QWidget ram_window;
	ram_window.resize(256,240);
	prog->addAction(QString("RAM"), &ram_window, SLOT(show()));
	
	menu_bar->addMenu(prog);
	
	//start GUI
	window->show();
	app.exec();
	return 0;
}
