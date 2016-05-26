#include "bot.h"

Bot *Bot::instance()
{
    static Bot bot;

    return &bot;
}
