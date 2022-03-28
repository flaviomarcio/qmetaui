#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickImageProvider>

class MUImageCaptureAreaProvider:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        public QQuickImageProvider{
#else
        public QObject, QQuickImageProvider{
#endif
    Q_OBJECT
public:
    explicit MUImageCaptureAreaProvider(QObject*parent=nullptr);
    virtual ~MUImageCaptureAreaProvider();

    QQmlImageProviderBase*imageProvider();

    static MUImageCaptureAreaProvider&instance();

    static void init();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize);
public slots:
    void captureResourceAdd(QPixmap pixelmap);
private:
    QPixmap pixelmap, pixmapNo;
signals:
    void captureResource(const QString&fileName);
};
