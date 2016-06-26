#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>

#define NO_RES_ID -1

class Response
{
public:
    Response(int id, const QString& from);
    virtual ~Response() {}
    void setId(int id);
    int id() const;
    void setFrom(const QString& from);
    const QString& from() const;
    static Response *createFromType(const QString& type);
    static Response *createFromJson(const QString& json);
    virtual void fromJson(const QString& json) = 0;
    virtual QString toJson() const = 0;
protected:
    int _id;
    QString _from;
};

#endif // RESPONSE_H
