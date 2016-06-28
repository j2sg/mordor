#ifndef MESSAGE_H
#define MESSAGE_H

#include "core_global.h"
#include <QString>

#define NO_MSG_ID -1

class CORE_EXPORT Message
{
public:
    Message(int id, const QString& from, const QString& to);
    virtual ~Message() {}
    void setId(int id);
    int id() const;
    void setFrom(const QString& from);
    const QString& from() const;
    void setTo(const QString& to);
    const QString& to() const;
    static Message *createFromJson(const QString& json);
    virtual void fromJson(const QString& json) = 0;
    virtual QString toJson() const = 0;
protected:
    int _id;
    QString _from;
    QString _to;
private:
    static Message *getInstanceOf(const QString& type);
};

#endif // MESSAGE_H
