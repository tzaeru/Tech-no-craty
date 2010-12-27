#ifndef APPLICATION_H
#define APPLICATION_H

#include "../include/main.h"

class Application : public QGLWidget {
private:
	/* All libraries available for GUI environment
	 * are listed in the enum in main.h
	 */
	int gui_library;
	
	/* Included for event signals et cetera*/
	Q_OBJECT
	
public:
	Application(QWidget *parent = NULL);
	
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
};

#endif // APPLICATION_H
