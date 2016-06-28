#ifndef TYPES_H
#define TYPES_H

#define NO_ATTACK_ID -1

typedef enum BotStateEnum
{
    UndefinedState,
    WaitingForCC,
    WaitingForCommand,
    AttackInProgress
} BotState;

#endif // TYPES_H
