#include "screencapture.h"

ScreenCapture::ScreenCapture(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	tray = new QSystemTrayIcon(this);
	tray->setToolTip("Screen Capture");
	tray->show();
	//tray->showMessage("Hello!", "Screen Capturer On", QSystemTrayIcon::Information, 100);
	tray->setIcon(QIcon(":/ScreenCapture/APPICON.ico"));
	QMenu *trayMenu = new QMenu();
	QAction *quit = new QAction("Quit", this);
	QAction *capture = new QAction("Capture Screen", this);
	trayMenu->addAction(capture);
	trayMenu->addAction(quit);
	tray->setContextMenu(trayMenu);

	connect(quit, SIGNAL(triggered()), this, SLOT(closeAnyway()));
	connect(capture, SIGNAL(triggered()), this, SLOT(captureScreen()));
	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), 
		this, SLOT(trayActiveResponse(QSystemTrayIcon::ActivationReason)));
	

	contextMenu = new QMenu();
	QAction *actSaveAs = new QAction("Save As", this);
	contextMenu->addAction(actSaveAs);
	connect(actSaveAs, SIGNAL(triggered()), this, SLOT(saveAsFile()));
}

ScreenCapture::~ScreenCapture()
{

}

void ScreenCapture::closeEvent(QCloseEvent* event)
{
	if (!closing)
	{	
		event->ignore();
		hide();
		delete img;
	}
}

void ScreenCapture::trayActiveResponse(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Unknown:
		break;
	case QSystemTrayIcon::Context:
		break;
	case QSystemTrayIcon::DoubleClick:
		captureScreen();
		break;
	case QSystemTrayIcon::Trigger:
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		break;
	}
}

void ScreenCapture::captureScreen()
{
	showFullScreen();
	ui.menuBar->hide();
	ui.mainToolBar->hide();

	img =new QImage((QPixmap::grabWindow(QApplication::desktop()->winId())).toImage());

	//captured = true;
}

void ScreenCapture::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, *img);
	if (dragging)
	{
		QPen pen;
		pen.setWidth(3);
		pen.setColor(QColor(0, 0, 255));
		painter.setPen(pen);
		painter.drawRect(qMin(mouseX0,mouseX1), qMin(mouseY0,mouseY1), abs(mouseX1-mouseX0), abs(mouseY1-mouseY0));

		painter.setBrush(QColor(128, 128, 128, 128));
		painter.setPen(QColor(128, 128, 128, 128));
		painter.drawRect(0, 0, qMin(mouseX0, mouseX1), qMin(mouseY0, mouseY1));
		painter.drawRect(qMin(mouseX0, mouseX1), 0, abs(mouseX1 - mouseX0), qMin(mouseY0, mouseY1));
		painter.drawRect(qMax(mouseX0, mouseX1), 0, width() - qMax(mouseX0, mouseX1), qMin(mouseY0, mouseY1));
		painter.drawRect(0, qMin(mouseY0, mouseY1), qMin(mouseX0, mouseX1), abs(mouseY1 - mouseY0));
		painter.drawRect(qMax(mouseX0, mouseX1), qMin(mouseY0, mouseY1), width() - qMax(mouseX0, mouseX1), abs(mouseY1 - mouseY0));
		painter.drawRect(0, qMax(mouseY0,mouseY1), qMin(mouseX0, mouseX1), height()-qMax(mouseY0, mouseY1));
		painter.drawRect(qMin(mouseX0, mouseX1), qMax(mouseY0, mouseY1), abs(mouseX1 - mouseX0), height() - qMax(mouseY0, mouseY1));
		painter.drawRect(qMax(mouseX0, mouseX1), qMax(mouseY0, mouseY1), width() - qMax(mouseX0, mouseX1), height() - qMax(mouseY0, mouseY1));
		cropRange[0] = qMin(mouseX0,mouseX1);
		cropRange[1] = qMin(mouseY0,mouseY1);
		cropRange[2] = qMax(mouseX1,mouseX0);
		cropRange[3] = qMax(mouseY1,mouseY0);
	}
}


void ScreenCapture::mouseMoveEvent(QMouseEvent *event)
{
	if (dragging)
	{
		mouseX1 = event->x();
		mouseY1 = event->y();
	}
	update();
}

void ScreenCapture::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragging = true;
		captured = false;
		mouseX0 = event->x();
		mouseY0 = event->y();
	}
}

void ScreenCapture::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragging = false;
		mouseX0 = 0;
		mouseY0 = 0;
		mouseX1 = 0;
		mouseY1 = 0;
		captured = true;
	}

}

void ScreenCapture::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (captured)
	{
		save2Clipboard();
		close();
	}
}

void ScreenCapture::saveAsFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
		QDir::homePath() + "/Pictures/",
		tr("(*.png);;(*.xpm);;(*.jpg);;(*.tiff);;(*.bmp)"));
	getCropArea().save(filename);
	close();
	
}

QImage& ScreenCapture::getCropArea()
{
	QImage* ret = new QImage(cropRange[2] - cropRange[0] + 1, cropRange[3] - cropRange[1] + 1, img->format());
	for (int x = 0; x < ret->width(); x++)
	{
		for (int y = 0; y < ret->height(); y++)
		{
			ret->setPixel(x, y, img->pixel(x + cropRange[0], y + cropRange[1]));
		}
	}
	return *ret;
}

void ScreenCapture::save2Clipboard()
{
	
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setImage(getCropArea());
}

void ScreenCapture::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		dragging = false;
		mouseX0 = 0;
		mouseY0 = 0;
		mouseX1 = 0;
		mouseY1 = 0;
		update();
	default:
		break;
	}
}

void ScreenCapture::contextMenuEvent(QContextMenuEvent *event)
{
	if (captured)
	{
		if (event->x() >= cropRange[0] && event->x() <= cropRange[2] 
			&& event->y() >= cropRange[1] && event->y() <= cropRange[3])
			contextMenu->exec(QPoint(event->x(), event->y()));
		else
		{
			captured = false;
			mouseX0 = 0;
			mouseY0 = 0;
			mouseX1 = 0;
			mouseY1 = 0;
			update();
		}
	}
	else
	{
		event->ignore();
		close();
	}
}