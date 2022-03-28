#include "./p_mu_image_capture_area_provider.h"
#include "../mu_application.h"
#include <QPixmap>
#include <QStm>

static void staticInit()
{
    auto&engine=MUApplication::engine();
    engine.addImageProvider(qsl("muimagecapturearea"), MUImageCaptureAreaProvider::instance().imageProvider());
}

static MUImageCaptureAreaProvider*muImageCaptureArea=nullptr;

static void init()
{
    muImageCaptureArea=new MUImageCaptureAreaProvider();
}

Q_COREAPP_STARTUP_FUNCTION(init)


MUImageCaptureAreaProvider::MUImageCaptureAreaProvider(QObject *parent)
    :
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
      QObject(parent), QQuickImageProvider(Pixmap)
#else
      QQuickImageProvider(Pixmap)
#endif
{
    Q_UNUSED(parent)
    this->pixmapNo=QPixmap::fromImage(QImage(10,10,QImage::Format_Mono));
}

MUImageCaptureAreaProvider::~MUImageCaptureAreaProvider()
{

}

QQmlImageProviderBase *MUImageCaptureAreaProvider::imageProvider()
{
    return this;
}

MUImageCaptureAreaProvider &MUImageCaptureAreaProvider::instance()
{
    return*muImageCaptureArea;
}

void MUImageCaptureAreaProvider::init()
{
    staticInit();
}

QPixmap MUImageCaptureAreaProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{

    Q_UNUSED(requestedSize)
    Q_UNUSED(id)
    Q_UNUSED(size)
    QPixmap result = (id==qsl_null)?this->pixmapNo:this->pixelmap;


    if(result.isNull()) {
        result = pixmapNo;
    }

    if(size) {
        *size = result.size();
    }

    return result;
}

void MUImageCaptureAreaProvider::captureResourceAdd(QPixmap pixelmap)
{
    static int i=0;
    this->pixelmap=pixelmap;
    emit captureResource(qsl("image://muimagecapturearea/image%1").arg(++i));
}
