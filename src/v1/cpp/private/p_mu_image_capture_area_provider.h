#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickImageProvider>

class MUImageCaptureAreaProvider:public QObject, QQuickImageProvider{
    Q_OBJECT
public:
    explicit MUImageCaptureAreaProvider(QObject*parent=nullptr);
    ~MUImageCaptureAreaProvider();

    QQmlImageProviderBase*imageProvider();

    static MUImageCaptureAreaProvider&instance();

    static void init();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize);
public slots:
    void resourceAdd(QPixmap pixelmap);
private:
    QPixmap pixelmap, pixmapNo;
signals:
    void changedResource(const QString&fileName);
};
