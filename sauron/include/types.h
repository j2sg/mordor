#ifndef TYPES_H
#define TYPES_H

typedef enum BotStateEnum
{
    WaitingForCommand,
    Attack
} BotState;

typedef enum ColumnBotEnum
{
    ColumnBotId,
    ColumnBotIP,
    ColumnBotOS,
    ColumnBotStatus
} ColumnBot;

typedef enum ColumnAttackEnum
{
    ColumnAttackId,
    ColumnAttackUptime,
    ColumnAttackBots
} ColumnAttack;

#endif // TYPES_H
