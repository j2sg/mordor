#ifndef BOT_H
#define BOT_H

class Bot
{
public:
    static Bot *instance();
private:
    Bot() {}
    Bot(const Bot& /*bot*/) {}
    Bot& operator=(const Bot& /*bot*/) { return *this; }
    ~Bot() {}
};

#endif // BOT_H
