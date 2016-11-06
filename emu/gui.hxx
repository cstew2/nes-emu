#ifndef GUI_HXX
#define GUI_HXX

#ifdef __cplusplus

QWidget *register_window_init();

extern "C" {
#endif
	int main_gui(void);
#ifdef __cplusplus
}
#endif

#endif
