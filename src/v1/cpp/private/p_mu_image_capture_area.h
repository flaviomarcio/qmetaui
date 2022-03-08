#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickImageProvider>
#include <QPixmap>

class MUImageCaptureAreaPvt:public QObject{
    Q_OBJECT
public:
    QPixmap pixmap;
    explicit MUImageCaptureAreaPvt(QObject*parent=nullptr);

    virtual ~MUImageCaptureAreaPvt();
signals:
    void captureResourceAdd(QPixmap pixelmap);
};
