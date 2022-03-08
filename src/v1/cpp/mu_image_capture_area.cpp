#include "./mu_image_capture_area.h"
#include "./mu_application.h"
#include "./private/p_mu_image_capture_area_provider.h"
#include "./private/p_mu_image_capture_area.h"


#define dPvt()\
auto&p = *reinterpret_cast<MUImageCaptureAreaPvt*>(this->p)



MUImageCaptureArea::MUImageCaptureArea(QObject *parent):QObject(parent)
{
    this->p=new MUImageCaptureAreaPvt(this);
    dPvt();
    QObject::connect(&p, &MUImageCaptureAreaPvt::captureResourceAdd, &MUImageCaptureAreaProvider::instance(), &MUImageCaptureAreaProvider::captureResourceAdd);
    QObject::connect(&MUImageCaptureAreaProvider::instance(), &MUImageCaptureAreaProvider::captureResource, this, &MUImageCaptureArea::captureResource);
}

MUImageCaptureArea::~MUImageCaptureArea()
{
    dPvt();
    delete&p;
}

void MUImageCaptureArea::captureScreen()
{
    auto&engine=MUApplication::engine();
    auto rootObjects=engine.rootObjects();
    auto windows= dynamic_cast<QQuickWindow*>(rootObjects.first());
    dPvt();
    p.pixmap = QPixmap::fromImage(windows->grabWindow());
}

void MUImageCaptureArea::captureRelease()
{
    dPvt();
    p.pixmap={};
}

void MUImageCaptureArea::captureScreenShot(int x, int y, int w, int h)
{
    dPvt();
    auto pixmap=p.pixmap.copy(x,y,w,h);
    emit p.captureResourceAdd(pixmap);
}

void MUImageCaptureArea::init()
{
    MUImageCaptureAreaProvider::init();
}
