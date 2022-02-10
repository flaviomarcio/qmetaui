#include "./p_mu_image_capture_area_provider.h"
#include "../mu_application.h"

static void staticInit()
{
    auto&engine=MUApplication::engine();
    engine.addImageProvider("muimagecapturearea", MUImageCaptureAreaProvider::instance().imageProvider());
}

Q_GLOBAL_STATIC(MUImageCaptureAreaProvider,muImageCaptureArea)

MUImageCaptureAreaProvider::MUImageCaptureAreaProvider(QObject *parent):QObject(parent), QQuickImageProvider(Pixmap)
{
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
    QPixmap result = (id=="")?this->pixmapNo:this->pixelmap;


    if(result.isNull()) {
        result = pixmapNo;
    }

    if(size) {
        *size = result.size();
    }

    return result;
}

void MUImageCaptureAreaProvider::resourceAdd(QPixmap pixelmap)
{
    static int i=0;
    this->pixelmap=pixelmap;
    emit changedResource(QString("image://muimagecapturearea/image%1").arg(++i));
}
