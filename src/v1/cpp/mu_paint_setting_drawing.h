#ifndef MUPaintSettingDrawing_H
#define MUPaintSettingDrawing_H

#include "./mu_global.h"
#include "./mu_string_util.h"

class Q_MU_EXPORT MUPaintSettingDrawing : public QObject
{
    Q_OBJECT
    friend class Q_MU_EXPORT MUPaintSettingState;
public:
    MU_DECLARE_MUStringUtil()

    Q_PROPERTY(int      fontSize         MEMBER fontSize    )
    Q_PROPERTY(QString  fontFamily       MEMBER fontFamily  )
    Q_PROPERTY(QColor   fontColor        MEMBER fontColor   )
    Q_PROPERTY(bool     fontItalic       MEMBER fontItalic  )
    Q_PROPERTY(bool     fontBold         MEMBER fontBold    )
    Q_PROPERTY(QColor   color            MEMBER color       )
    Q_PROPERTY(QColor   borderColor      MEMBER borderColor )
    Q_PROPERTY(QVariant borderWidth      MEMBER borderWidth )

    Q_INVOKABLE explicit MUPaintSettingDrawing(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUPaintSettingDrawing(const MUPaintSettingDrawing &parent) : QObject(nullptr){
        Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
                    setProperty( prop.constData(), parent.property( prop.constData() ) );
    }
    ~MUPaintSettingDrawing();

    Q_INVOKABLE void replaceInvalid(MUPaintSettingDrawing &baseObject);

private:
    int fontSize = 9;
    QString fontFamily = "Sans Serif";
    QColor fontColor= Qt::gray;
    bool fontItalic = false;
    bool fontBold = false;
    QColor color = Qt::white;
    QColor borderColor = Qt::lightGray;
    QVariant borderWidth = 0;

signals:
    void refresh();
};

Q_DECLARE_METATYPE(MUPaintSettingDrawing    )

#endif // MUPaintSettingDrawing_H
