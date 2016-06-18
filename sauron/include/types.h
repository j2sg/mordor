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
    ColumnBotStatus,
    ColumnBotCount
} ColumnBot;

typedef enum ColumnAttackEnum
{
    ColumnAttackId,
    ColumnAttackUptime,
    ColumnAttackBots
} ColumnAttack;

typedef enum CommandTypeEnum
{
    NoOp,
    GetBotnetStatus
} CommandType;

#endif // TYPES_H
