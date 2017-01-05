#ifndef GUI_HXX
#define GUI_HXX

#ifdef __cplusplus

#include <QtGui>
#include <stdint.h>

class gui : public QMainWindow{
	Q_OBJECT
public:
	gui(void);
	~gui(void);

	QWidget *main_window;

private slots:
	void open_file();
	
private:
	char *rom_file;
	
	QMenuBar *menu_bar;
	QMenu *file;

	QFileDialog *file_picker;
	QWidget *file_info_window;

	QMenu *prog;
	QWidget *hex_window;
	QWidget *code_window;
	QWidget *registers_window;
	QWidget *ram_window;

	QAction *open_action;

	void start_emu(void);
};

extern "C" {
#endif
	void start_gui(void);
#ifdef __cplusplus
}
#endif

#endif
