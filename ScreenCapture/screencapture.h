#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QtWidgets/QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QApplication>
#include <qdesktopwidget>
#include <QPainter>
#include <QImage>
#include <QMessageBox>
#include <QRgb>
#include <qclipboard>
#include <qfiledialog>
#include "ui_screencapture.h"

class ScreenCapture : public QMainWindow
{
	Q_OBJECT

public:
	ScreenCapture(QWidget *parent = 0);
	~ScreenCapture();
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void contextMenuEvent(QContextMenuEvent * event);
	public slots:
	void closeAnyway(){ closing = true; close(); }
	void captureScreen();
	void trayActiveResponse(QSystemTrayIcon::ActivationReason);
	void save2Clipboard();
	void saveAsFile();
protected:
	
	QImage& getCropArea();
private:
	Ui::ScreenCaptureClass ui;
	QSystemTrayIcon *tray;
	bool closing = false;
	bool captured = false;
	bool dragging = false;

	int mouseX0 = 0;
	int mouseY0 = 0;
	int mouseX1 = 0;
	int mouseY1 = 0;

	int cropRange[4];

	QMenu* contextMenu;

	QImage* img;
};

#endif // SCREENCAPTURE_H
