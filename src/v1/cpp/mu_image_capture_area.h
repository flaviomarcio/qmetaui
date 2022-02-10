#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQuickImageProvider>
#include "./mu_global.h"

//!
//! \brief The MUImageCaptureArea class
//!
class Q_MU_EXPORT MUImageCaptureArea:public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief MUImageCaptureArea
    //! \param parent
    //!
    explicit MUImageCaptureArea(QObject*parent=nullptr);

    ~MUImageCaptureArea();

    //!
    //! \brief captureScreen
    //!
    Q_INVOKABLE void captureScreen();

    //!
    //! \brief captureRelease
    //!
    Q_INVOKABLE void captureRelease();

    //!
    //! \brief captureScreenShot
    //! \param x
    //! \param y
    //! \param w
    //! \param h
    //!
    Q_INVOKABLE void captureScreenShot(int x, int y, int w, int h);

    //!
    //! \brief init
    //!
    static void init();
private:
    void*p=nullptr;
signals:
    //!
    //! \brief captureResource
    //! \param fileName
    //!
    void captureResource(const QString&fileName);
};
