#include "./mu_image_capture_area.h"
#include "./mu_application.h"
#include "./private/p_mu_image_capture_area_provider.h"

MUImageCaptureArea::MUImageCaptureArea(QObject *parent):QObject(parent)
{
    QObject::connect(this, &MUImageCaptureArea::resourceAdd, &MUImageCaptureAreaProvider::instance(), &MUImageCaptureAreaProvider::resourceAdd);
    QObject::connect(&MUImageCaptureAreaProvider::instance(), &MUImageCaptureAreaProvider::changedResource, this, &MUImageCaptureArea::resourceChanged);
}

void MUImageCaptureArea::printCapture()
{
    auto&engine=MUApplication::engine();
    auto rootObjects=engine.rootObjects();
    auto windows= dynamic_cast<QQuickWindow*>(rootObjects.first());
    this->pixmap = QPixmap::fromImage(windows->grabWindow());
}

void MUImageCaptureArea::printRelease()
{
    this->pixmap={};
}

void MUImageCaptureArea::screenShot(int x, int y, int w, int h)
{
    auto map=this->pixmap.copy(x,y,w,h);
    emit resourceAdd(map);
}

void MUImageCaptureArea::init()
{
    MUImageCaptureAreaProvider::init();
}
