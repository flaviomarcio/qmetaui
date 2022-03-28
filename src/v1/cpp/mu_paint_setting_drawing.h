#pragma once

#include "./mu_global.h"
#include "./mu_string_util.h"

class Q_MU_EXPORT MUPaintSettingDrawing : public QObject
{
    Q_OBJECT
    friend class Q_MU_EXPORT MUPaintSettingState;
public:
    MU_DECLARE_MUStringUtil()

    Q_PROPERTY(int      fontSize         MEMBER fontSize    NOTIFY fontSizeChanged)
    Q_PROPERTY(QString  fontFamily       MEMBER fontFamily  NOTIFY fontFamilyChanged)
    Q_PROPERTY(QColor   fontColor        MEMBER fontColor   NOTIFY fontColorChanged)
    Q_PROPERTY(bool     fontItalic       MEMBER fontItalic  NOTIFY fontItalicChanged)
    Q_PROPERTY(bool     fontBold         MEMBER fontBold    NOTIFY fontBoldChanged)
    Q_PROPERTY(QColor   color            MEMBER color       NOTIFY colorChanged)
    Q_PROPERTY(QColor   borderColor      MEMBER borderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QVariant borderWidth      MEMBER borderWidth NOTIFY borderWidthChanged)

    Q_INVOKABLE explicit MUPaintSettingDrawing(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUPaintSettingDrawing(const MUPaintSettingDrawing &parent);
    ~MUPaintSettingDrawing();

    Q_INVOKABLE void replaceInvalid(MUPaintSettingDrawing &baseObject);

private:
    int fontSize = 9;
    QString fontFamily = QStringLiteral("Sans Serif");
    QColor fontColor= Qt::gray;
    bool fontItalic = false;
    bool fontBold = false;
    QColor color = Qt::white;
    QColor borderColor = Qt::lightGray;
    QVariant borderWidth = 0;

signals:
    void fontSizeChanged();
    void fontFamilyChanged();
    void fontColorChanged();
    void fontItalicChanged();
    void fontBoldChanged();
    void colorChanged();
    void borderColorChanged();
    void borderWidthChanged();
};

Q_DECLARE_METATYPE(MUPaintSettingDrawing    )
