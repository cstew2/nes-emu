#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QScrollArea>
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
	QWidget window;
	window.setWindowTitle(QString::fromUtf8("cnes"));
	window.setFixedSize(256,240);

	//Menu setup
	QMenuBar *menu_bar = new QMenuBar(&window);
	
	QMenu *file = new QMenu(QString::fromUtf8("File"));
	file->addAction(QString::fromUtf8("Open"));
	file->addAction(QString::fromUtf8("File Info"));
	file->addAction(QString::fromUtf8("Quit"));
	menu_bar->addMenu(file);

	QMenu *prog = new QMenu(QString::fromUtf8("Prog"));

	QAction *gui_open_file;
	QAction *gui_file_info;
	QAction *gui_quit;
	

	//Hex Window
	QWidget hex_window;
	hex_window.resize(256,240);
	prog->addAction(QString("Hex"), &hex_window, SLOT(show()));

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
	window.show();
	app.exec();
	return 0;
}
