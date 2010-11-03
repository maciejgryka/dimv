#include "dimv.h"
#include <QFileDialog>
#include <QMessageBox>

dimv::dimv(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.viewLeft->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui.viewRight->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	createActions();
	createMenus();

	ui.viewLeft->setTransformationAnchor(QGraphicsView::NoAnchor);
	ui.viewRight->setTransformationAnchor(QGraphicsView::NoAnchor);
	ui.labelLeft->setText("");
	ui.labelRight->setText("");

	ui.viewLeft->setScene(&sceneLeft);
	ui.viewRight->setScene(&sceneRight);

	scaleFactor = 1.0;
}

void dimv::openLeft() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

	if (!fileName.isEmpty()) {
		QImage image(fileName);
		if (image.isNull()) {
			QMessageBox::information(this, tr("dimv"), tr("Cannot load %1.").arg(fileName));
			return;
		}

		sceneLeft.clear();
		sceneLeft.addPixmap(QPixmap(fileName));

		ui.labelLeft->setText(fileName);

		adjustView(image.width(), image.height(), ui.viewLeft);
	}
}

void dimv::openRight() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

	if (!fileName.isEmpty()) {
		QImage image(fileName);
		if (image.isNull()) {
			QMessageBox::information(this, tr("dimv"), tr("Cannot load %1.").arg(fileName));
			return;
		}

		sceneRight.clear();
		sceneRight.addPixmap(QPixmap(fileName));

		ui.labelRight->setText(fileName);

		adjustView(image.width(), image.height(), ui.viewRight);
	}
}

void dimv::offsetImages(int hor, int vert) {
	ui.viewLeft->translate(hor, vert);
	ui.viewRight->translate(hor, vert);
}

void dimv::left() {
	offsetImages(translationStep, 0);
}

void dimv::right() {
	offsetImages(-translationStep, 0);
}

void dimv::up() {
	offsetImages(0, translationStep);
}

void dimv::down() {
	offsetImages(0, -translationStep);
}

void dimv::scaleImages(double factor) {
	scaleFactor *= factor;

	ui.viewLeft->scale(factor, factor);
	ui.viewRight->scale(factor, factor);
}

void dimv::zoomIn() {
	scaleImages(1.25);
}

void dimv::zoomOut() {
	scaleImages(0.8);
}

void dimv::normalSize() {
	scaleImages(1.0/scaleFactor);
}

void dimv::createActions() {
	openLeftAct = new QAction(tr("Open left..."), this);
	openLeftAct->setShortcut(tr("Ctrl+L"));
	connect(openLeftAct, SIGNAL(triggered()), this, SLOT(openLeft()));

	openRightAct = new QAction(tr("Open right..."), this);
	openRightAct->setShortcut(tr("Ctrl+R"));
	connect(openRightAct, SIGNAL(triggered()), this, SLOT(openRight()));

	zoomInAct = new QAction(tr("Zoom in"), this);
	zoomInAct->setShortcut(Qt::Key_Plus);
	connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

	zoomOutAct = new QAction(tr("Zoom out"), this);
	zoomOutAct->setShortcut(Qt::Key_Minus);
	connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

	normalSizeAct = new QAction(tr("Original size"), this);
	normalSizeAct->setShortcut(tr("Ctrl+0"));
	connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

	leftAct = new QAction(this);
	leftAct->setShortcut(Qt::Key_Left);
	connect(leftAct, SIGNAL(triggered()), this, SLOT(left()));

	rightAct = new QAction(this);
	rightAct->setShortcut(Qt::Key_Right);
	connect(rightAct, SIGNAL(triggered()), this, SLOT(right()));

	upAct = new QAction(this);
	upAct->setShortcut(Qt::Key_Up);
	connect(upAct, SIGNAL(triggered()), this, SLOT(up()));

	downAct = new QAction(this);
	downAct->setShortcut(Qt::Key_Down);
	connect(downAct, SIGNAL(triggered()), this, SLOT(down()));

	exitAct = new QAction(tr("Close"), this);
	exitAct->setShortcut(Qt::Key_Escape);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void dimv::createMenus() {
	ui.menuFile->addAction(openLeftAct);
	ui.menuFile->addAction(openRightAct);
	ui.menuFile->addSeparator();
	ui.menuFile->addAction(aboutAct);
	ui.menuFile->addSeparator();
	ui.menuFile->addAction(exitAct);

	ui.menuView->addAction(zoomInAct);
	ui.menuView->addAction(zoomOutAct);
	ui.menuView->addAction(normalSizeAct);

	ui.menuBar->addAction(leftAct);
	ui.menuBar->addAction(rightAct);
	ui.menuBar->addAction(upAct);
	ui.menuBar->addAction(downAct);
}

void dimv::about() {
	QMessageBox::about(this, tr("About"), 
		tr("<b>d</b>ual <b>im</b>age <b>v</b>iewer"
		"<p>v 0.0.01</p>"
		"<p>mady by <a href='http://maciejgryka.com'>Maciej Gryka</a>"));
}

void dimv::adjustView(float imW, float imH, QGraphicsView *view) {
	view->resetMatrix();
	translationStep = imW*0.05;

	float viewW = view->width() - 5,
		  viewH = view->height() - 5;
	
	if (imW > imH) {
		if (imW > viewW) {
			view->scale(viewW/imW, viewW/imW);
		}
	} else {
		if (imH > viewH) {
			view->scale(viewH/imH, viewH/imH);
		}
	}
}