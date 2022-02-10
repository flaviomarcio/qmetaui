#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickImageProvider>

class MUImageCaptureArea:public QObject
{
    Q_OBJECT
public:
    explicit MUImageCaptureArea(QObject*parent=nullptr);
    Q_INVOKABLE void printCapture();
    Q_INVOKABLE void printRelease();
    Q_INVOKABLE void screenShot(int x, int y, int w, int h);

    static void init();

    QPixmap pixmap;
signals:
    void resourceChanged(const QString&fileName);
    void resourceAdd(QPixmap pixelmap);
};
