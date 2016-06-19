#ifndef TYPES_H
#define TYPES_H

typedef enum BotStateEnum
{
    WaitingForCC,
    WaitingForCommand,
    Attack
} BotState;

typedef enum CommandTypeEnum
{
    NoOp,
    GetBotnetStatus
} CommandType;

#endif // TYPES_H
