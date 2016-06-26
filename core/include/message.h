#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

#define NO_MSG_ID -1

class Message
{
public:
    Message(int id, const QString& from);
    virtual ~Message() {}
    void setId(int id);
    int id() const;
    void setFrom(const QString& from);
    const QString& from() const;
    static Message *createFromType(const QString& type);
    static Message *createFromJson(const QString& json);
    virtual void fromJson(const QString& json) = 0;
    virtual QString toJson() const = 0;
protected:
    int _id;
    QString _from;
};

#endif // MESSAGE_H
