#include "./mu_string_util.h"
#include "./mu_object_util.h"
#include "./mu_cache_util.h"
#include "./mu_variant_util.h"
#include <../../qstm/includes/QStm>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QBitArray>
#include <QDateTime>
#include <QUrl>
#include <QUuid>
#include <QColor>
#include <QQuickItem>


Q_GLOBAL_STATIC_WITH_ARGS(QString, specialMaskChar,("(){}[]/-*+.,;"))
Q_GLOBAL_STATIC(MUStringUtil, __i)

MUStringUtil::MUStringUtil(QObject *parent):QObject{parent}
{

}

MUStringUtil::~MUStringUtil()
{

}

MUStringUtil &MUStringUtil::i()
{
    return *__i;
}

bool MUStringUtil::isDebug()
{
    return MUObjectUtil::isDebug();
}

const QVariant MUStringUtil::getEnv(const QVariant &env, const QVariant &defaultValue)
{
    QVariant v=getenv(env.toByteArray());
    v=v.toString().isEmpty()?defaultValue:v;
    return v;
}

const QVariant MUStringUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUStringUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUStringUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}

bool MUStringUtil::isEmpty(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QString:
    case QMetaType_QChar:
    case QMetaType_QByteArray:
        return v.toString().trimmed().isEmpty();
    default:
        return true;
    }
}

QVariant MUStringUtil::isEmptySet(const QVariant &vThen, const QVariant &vElse)
{
    return isEmpty(vThen)?vElse:vThen;
}

const QVariantMap MUStringUtil::toMap(const QVariant &v)
{
    return MUVariantUtil::toMap(v);
}

const QByteArray MUStringUtil::toMd5(const QVariant &v)
{
    return MUVariantUtil::toMd5(v);
}

const QString MUStringUtil::toStr(const QVariant &v, QString defaultValue)
{
    return MUVariantUtil::toStr(v, defaultValue);
}

const QString MUStringUtil::toStrNumber(const QVariant &v)
{
    return MUVariantUtil::toStrNumber(v);
}

const QString MUStringUtil::toStrPhone(const QVariant &v)
{
    auto text=v.toString();
    auto textValid=qsl("+01234567890");
    QString output;
    for(auto&c:text){
        if(textValid.contains(c))
            output+=c;
    }
    return output;
}

const QString MUStringUtil::toStrDouble(const QVariant &v)
{
    return MUVariantUtil::toStrNumber(v);
}

const QString MUStringUtil::toStrAlignLeft(int width, const QVariant&fill, const QVariant &v)
{
    width=(width<0)?width:0;
    auto vv=v.toString().trimmed();
    auto c=fill.toChar();
    return vv.leftJustified(width,c,false);
}

const QString MUStringUtil::toStrAlignRight(int width, const QVariant&fill, const QVariant &v)
{
    width=(width<0)?width:0;
    auto vv=v.toString().trimmed();
    auto c=fill.toChar();
    return vv.rightJustified(width,c,false);
}

const QVariant MUStringUtil::toVar(const QVariant &v)
{
    return MUVariantUtil::toVar(v);
}

bool MUStringUtil::toBoo(const QVariant &v)
{
    return MUVariantUtil::toBoo(v);
}

const QByteArray MUStringUtil::toJson(const QVariant &v)
{
    return MUVariantUtil::toJson(v);
}

const QByteArray MUStringUtil::toCBor(const QVariant &v)
{
    return MUVariantUtil::toCBor(v);
}

const QColor MUStringUtil::toColor(const QVariant &v, const QColor&defaultValue)
{
    return MUVariantUtil::toColor(v, defaultValue);
}

qlonglong MUStringUtil::toInt(const QVariant &v, QVariant defaultValue)
{
    return MUVariantUtil::toInt(v, defaultValue);
}

double MUStringUtil::toDouble(const QVariant &v, QVariant defaultValue)
{
    return MUVariantUtil::toDouble(v, defaultValue);
}


const QVariant MUStringUtil::convertVar(const QVariant &v, const int type)
{
    return MUVariantUtil::convertVar(v, type);
}

const QVariant MUStringUtil::toAlignment(const QVariant &v, Qt::Alignment alignment)
{
    return MUVariantUtil::toAlignment(v, alignment);
}

//int MUStringUtil::toVariantType(const QVariant &v)
//{
//    return MUVariantUtil::toVariantType(v);
//}

//const QByteArray MUStringUtil::toVariantTypeName(int v)
//{
//    return QMetaType::typeName(v);
//}

const QByteArray MUStringUtil::loadFile(const QString &file)
{
    return MUCacheUtil::loadFile(file);
}

const QVariant MUStringUtil::loadFileMap(const QString &file)
{
    return MUCacheUtil::loadFileMap(file);
}

const QVariant MUStringUtil::loadJsonFile(const QString &file)
{
    return MUCacheUtil::loadJsonFile(file);
}

const QVariant MUStringUtil::loadCBorFile(const QString &file)
{
    return MUCacheUtil::loadCBorFile(file);
}

const QString MUStringUtil::inputText(const QString &value)
{
    QString mValue;
    for(auto&c:value){
        if(!specialMaskChar->contains(c))
            mValue+=c;
    }
    return mValue;
}

const QString MUStringUtil::inputMaskClean(const QString &mask)
{
    auto mMask=mask;
    for (auto&cc:mMask) {
        if(!specialMaskChar->contains(cc))
            cc=' ';
    }
    return mMask.trimmed();
}

const QString MUStringUtil::inputMaskFormat(const QString &mask, const QString &value)
{
    static QChar param = '#';
    if (!mask.contains(param))// verifica se é a máscara certa para aplicar, senão retorna o mesmo valor digitado
        return value;

    int size = mask.count(param); // qtd de digitos que precisam ser inseridos

    QString editable = value;
    QString editableMask = mask;
    editableMask.remove(qsl(";_"));
    editable.replace(qsl_space, qsl_null); // os espaços atrapalham a lógica

    for (auto item: editableMask) editable.remove(item); // os caracteres especiais da máscara atrapalham a lógica
    if ( editable.isEmpty()) // se está vazio com as validações retorna o que foi digitado
        return value;

    if ( editable.length() > size ) editable.resize(size); // se tem mais caracteres do que precisa pra mascara, remove os últimos
    int i = 0;
    for(auto cada: editable){ // vai substituindo o # por um caractere digitado na máscara a  partir da último preencido.
         i = editableMask.indexOf('#',i);
         editableMask.replace(i,1,cada);
    }
    i++;
    editableMask.remove(i, mask.count() - 1 );// remove a parte não preenchida da máscara
    return editableMask;
}

int MUStringUtil::inputMaskLength(const QString &mask, const QString &value)
{
    auto text=inputMaskFormat(mask, value);
    return text.length();
}

int MUStringUtil::inputMaskCursorPosition(const QString &mask, const QString &value)
{
    auto mMask=inputMaskClean(mask);
    mMask=!mMask.contains(qsl(";"))?mMask: mMask.mid(0,mMask.lastIndexOf(qsl(";")));
    auto space=' ';
    auto text=inputMaskFormat(mask, value).leftJustified(mMask.length(), space);
    int r=0;
    for (auto&c:text) {
        if(specialMaskChar->contains(c))
            ++r;
        else if(c!=space)
            ++r;
        else
            break;
    }
    //r=(r>0)?r+1:r;
    r=(r>mMask.length())?mMask.length():r;
    return r;
}

QString MUStringUtil::isUuidString(const QString &value)
{
    QUuid uuid(value);
    if (uuid.isNull())
        return {};
    return uuid.toString();
}
