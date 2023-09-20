//
// Created by 58226 on 2023/7/14.
//

#ifndef ATTACHABLE_H
#define ATTACHABLE_H
#include <QSharedPointer>
#include <QString>
#include <QHash>



///useage:
///get: Attachable<T, EX>::attach(XX).get("key",defaultData);
///set: Attachable<T, EX>::attach(XX).set("key",defaultData);
template<typename T,typename EX>
class Attachable
{
public:
    static Attachable<T,EX>& attach(QSharedPointer<T> sender)
    {
        auto it = attachCaches.find(sender);
        if(it==attachCaches.end())
        {
            it = attachCaches.insert(sender,Attachable<T,EX>(sender));
        }
        return it.value();
    }


    void set(const QString& key,const EX& properties)
    {
        m_data.insert(key,properties);
    }

    EX get(const QString& key,const EX& defaultValue)
    {
        return m_data.value(key,defaultValue);
    }

private:

    explicit Attachable(QSharedPointer<T> sender):m_attachedObj(sender){}

    ///static attach cache
    static QMultiHash<QSharedPointer<T>,Attachable<T,EX>> attachCaches;

    QSharedPointer<T> m_attachedObj;

    ///actual data storage
    QMultiHash<QString,EX> m_data;

};
template<typename T,typename EX>
QMultiHash<QSharedPointer<T>,Attachable<T,EX>> Attachable<T,EX>::attachCaches;


#endif//ATTACHABLE_H
