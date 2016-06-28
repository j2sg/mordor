#ifndef TYPES_H
#define TYPES_H

typedef enum BotStateEnum
{
    UndefinedState,
    WaitingForCC,
    WaitingForCommand,
    AttackInProgress
} BotState;

#endif // TYPES_H
