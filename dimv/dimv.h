#ifndef DIMV_H
#define DIMV_H

#include <QtGui/QMainWindow>
#include "ui_dimv.h"
#include <QGraphicsScene>

class dimv : public QMainWindow
{
	Q_OBJECT

public:
	dimv(QWidget *parent = 0, Qt::WFlags flags = 0);
	~dimv(){};

private slots:
	void openLeft();
	void openRight();
	
	void left();
	void right();
	void up();
	void down();
	void zoomIn();
	void zoomOut();
	
	void normalSize();
	void about();

private:
	Ui::dimvClass ui;

	QGraphicsScene sceneLeft;
	QGraphicsScene sceneRight;

	QAction *openLeftAct;
	QAction *openRightAct;
	QAction *exitAct;
	
	QAction *leftAct;
	QAction *rightAct;
	QAction *upAct;
	QAction *downAct;
	QAction *zoomInAct;
	QAction *zoomOutAct;
	
	QAction *normalSizeAct;
	QAction *aboutAct;
	
	double scaleFactor;
	int translationStep;
	double translationHor;
	double translationVert;

	void createActions();
	void createMenus();
	void scaleImages(double factor);
	void offsetImages(int hor, int vert);
	void adjustView(float imW, float imH, QGraphicsView *view);
};


#endif // DIMV_H
