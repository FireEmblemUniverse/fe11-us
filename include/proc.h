#ifndef PROC_H
#define PROC_H

#include "types.h"

enum
{
    PROC_CMD_END = 0x00,
    PROC_CMD_01 = 0x01,
    PROC_CMD_02 = 0x02,
    PROC_CMD_03 = 0x03,
    PROC_CMD_04 = 0x04,
    PROC_CMD_ONEND = 0x05,
    PROC_CMD_06 = 0x06,
    PROC_CMD_CALL = 0x07,
    PROC_CMD_CALL_ARG = 0x08,
    PROC_CMD_WHILE = 0x09,
    PROC_CMD_WHILE_ARG = 0x0A,
    PROC_CMD_0B = 0x0B,
    PROC_CMD_REPEAT = 0x0C,
    PROC_CMD_WHILE_EXISTS = 0x0D,
    PROC_CMD_START_CHILD = 0x0E,
    PROC_CMD_START_CHILD_BLOCKING = 0x0F,
    PROC_CMD_START_IN_TREE = 0x10,
    PROC_CMD_11 = 0x11,
    PROC_CMD_12 = 0x12,
    PROC_CMD_LABEL = 0x13,
    PROC_CMD_GOTO = 0x14,
    PROC_CMD_GOTO_IF_YES = 0x15,
    PROC_CMD_GOTO_IF_NO = 0x16,
    PROC_CMD_JUMP = 0x17,
    PROC_CMD_SLEEP = 0x18,
    PROC_CMD_MARK = 0x19,
    PROC_CMD_1A = 0x1A,
    PROC_CMD_1B = 0x1B,
    PROC_CMD_1C = 0x1C,
    PROC_CMD_NOP_1D = 0x1D, // maybe PROC_CMD_NAME?
    PROC_CMD_1E = 0x1E,
    PROC_CMD_1F = 0x1F,
    PROC_CMD_20 = 0x20,
    PROC_CMD_21 = 0x21,
    PROC_CMD_22 = 0x22,
    PROC_CMD_23 = 0x23,
    PROC_CMD_OVERLAY = 0x24,
    PROC_CMD_25 = 0x25,
};

struct ProcCmd
{
    /* 00 */ s16 opcode;
    /* 02 */ s16 dataImm;
    /* 04 */ void * dataPtr;
};

struct Proc;

typedef void (*ProcFunc)(struct Proc *);

struct ProcFuncTable
{
    /* 00 */ ProcFunc unk_00; // End Callback?
    /* 04 */ ProcFunc unk_04; // ?
    /* 08 */ ProcFunc unk_08; // Init?
    /* 0C */ ProcFunc unk_0C; // Main Loop?
};

struct Proc
{
    /* 00 */ struct ProcFuncTable * proc_funcTable;
    /* 04 */ struct ProcCmd * proc_script;
    /* 08 */ struct ProcCmd * proc_scrCur;
    /* 0C */ ProcFunc proc_endCb;
    /* 10 */ ProcFunc proc_idleCb;
    /* 14 */ ProcFunc unk_14;
    /* 18 */ struct Proc * proc_parent;
    /* 1C */ struct Proc * proc_child;
    /* 20 */ struct Proc * proc_next;
    /* 24 */ struct Proc * proc_prev;
    /* 28 */ void * unk_28; // maybe child?
    /* 2C */ void * unk_2c;
    /* 30 */ s16 proc_sleepTime;
    /* 32 */ u16 proc_flags;
    /* 34 */ u8 proc_mark;
    /* 35 */ u8 proc_lockCnt;
    STRUCT_PAD(0x36, 0x38);
    /* 38 */ void (*unk_38)(void *);
    STRUCT_PAD(0x3C, 0x58);
    /* 58 */ s16 unk_58;
    STRUCT_PAD(0x5A, 0x78);
};

struct Unknown02190ce0
{
    /* 00 */ struct Proc ** unk_00;
    /* 04 */ void * unk_04;
    /* 08 */ void * unk_08;
};

struct Proc * func_01ffbc90(u32 treeNum);
BOOL IsRootProcess(struct Proc * proc);
void RunProcessScript(struct Proc * proc);
struct Proc * AllocateProcess(void);
void func_01ffbda4(struct Proc * proc);
void InsertRootProcess(struct Proc * proc, s32 treeNum);
void InsertChildProcess(struct Proc * proc, struct Proc * parent);
void func_01ffbe3c(struct Proc * proc);
struct Proc * Proc_StartExt(struct ProcCmd * script, struct Proc * parent, void * arg_2);
struct Proc * Proc_Start(struct ProcCmd * script, struct Proc * parent);
struct Proc * func_01ffbf90(struct ProcCmd * script, struct Proc * parent);
void func_01ffbfd0(struct Proc * proc);
struct Proc * Proc_StartBlockingExt(struct ProcCmd * script, struct Proc * parent, void * arg_2);
struct Proc * Proc_StartBlocking(struct ProcCmd * script, struct Proc * parent);
struct Proc * func_01ffc030(struct ProcCmd * script, struct Proc * parent);
void func_01ffc068(struct Proc * proc);
void func_01ffc0a0(struct Proc * proc);
void func_01ffc0e8(struct Proc * proc);
void Proc_End(struct Proc * proc);
void RunProcessRecursive(struct Proc * proc);
void func_01ffc2f4(struct Proc * proc);
void Proc_Run(u32 treeNum);
void Proc_Break(struct Proc * proc, s32 arg_1);
void func_01ffc3f4(struct Proc * proc);

void Proc_Init(void);
struct Proc * Proc_Find(struct ProcCmd * script);
struct Proc * func_02018d40(struct ProcCmd * script);
struct Proc * func_02018d9c(struct ProcCmd * script, struct Proc * proc);
struct Proc * func_02018df4(struct ProcCmd * script, struct Proc * proc);
struct Proc * func_02018e4c(u32 mark);
struct Proc * func_02018e90(struct ProcCmd * script, u32 mark);
void Proc_SetMark(struct Proc * proc, u32 mark);
void Proc_Goto(struct Proc * proc, s32 label, s32 unk);
void Proc_GotoScript(struct Proc * proc, struct ProcCmd * script);
void Proc_SetEndFunc(struct Proc * proc, ProcFunc func);
void func_02018f54(struct Proc * proc, void * unk_14);
void * func_02018f5c(struct Proc * proc);
void Proc_ForEach(struct ProcCmd * script, ProcFunc func);
void func_02018fa4(struct ProcCmd * script, ProcFunc func);
void Proc_BreakEach(struct ProcCmd * script);
void func_0201900c(struct ProcCmd * script);
void Proc_EndEach(struct ProcCmd * script);
void func_02019034(struct ProcCmd * script);
void Proc_EndEachMarked(u32 mark);
void Proc_Lock(struct Proc * proc);
void Proc_Release(struct Proc * proc);
BOOL IsProcLocked(struct Proc * proc);
struct ProcCmd * func_020190c4(struct Proc * proc);
struct Proc * func_020190cc(struct Proc * proc);
void func_020190ec(struct Proc * proc);
void func_02019124(struct Proc * proc);
void func_02019164(struct Proc * proc);
struct Proc * Proc_GetChild(struct Proc * proc);
BOOL func_02019190(struct Proc * proc, u32 flags);
BOOL func_02019230(struct Proc * proc, u32 flags);
void func_020192d0(struct Proc * proc);
void func_020192f4(struct Proc * proc);
void func_02019310(void * func, struct Proc * parent);
void func_0201932c(struct Proc * proc);
void func_0201933c(void * func, struct Proc * parent);
BOOL ProcCmd_End(struct Proc * proc);
BOOL func_02019368(struct Proc * proc);
BOOL func_02019370(struct Proc * proc);
BOOL func_02019378(struct Proc * proc);
BOOL ProcCmd_SetEndFunc(struct Proc * proc);
BOOL func_020193b4(struct Proc * proc);
BOOL ProcCmd_Call(struct Proc * proc);
BOOL ProcCmd_CallArg(struct Proc * proc);
BOOL ProcCmd_While(struct Proc * proc);
BOOL ProcCmd_WhileArg(struct Proc * proc);
void func_0201949c(void * arg_0, void * arg_1);
void func_020194fc(void * unused);
BOOL func_0201951c(struct Proc * proc);
BOOL ProcCmd_Repeat(struct Proc * proc);
BOOL ProcCmd_WhileExists(struct Proc * proc);
BOOL ProcCmd_SpawnChild(struct Proc * proc);
BOOL ProcCmd_SpawnLockChild(struct Proc * proc);
BOOL ProcCmd_SpawnChildInTree(struct Proc * proc);
BOOL func_020196f8(struct Proc * proc);
BOOL func_02019734(struct Proc * proc);
BOOL ProcCmd_Goto(struct Proc * proc);
BOOL ProcCmd_GotoIfYes(struct Proc * proc);
BOOL ProcCmd_GotoIfNo(struct Proc * proc);
BOOL ProcCmd_Jump(struct Proc * proc);
void SleepRepeatFunc(struct Proc * proc);
BOOL ProcCmd_Sleep(struct Proc * proc);
BOOL ProcCmd_Mark(struct Proc * proc);
BOOL func_020198c4(struct Proc * proc);
BOOL func_020198f8(struct Proc * proc);
BOOL func_0201992c(struct Proc * proc);
BOOL func_02019954(struct Proc * proc);
BOOL func_02019968(struct Proc * proc);
BOOL func_020199b8(struct Proc * proc);
BOOL func_02019a08(struct Proc * proc);
BOOL func_02019a58(struct Proc * proc);
BOOL func_02019aa8(struct Proc * proc);
BOOL func_02019af8(struct Proc * proc);
BOOL ProcCmd_Overlay(struct Proc * proc);
BOOL func_02019b84(struct Proc * proc);
void func_02019bac(struct Proc * proc);
void func_02019bc0(struct Proc * proc);

extern struct Proc gProcArray[0x80];
extern struct Proc * gProcAllocList[0x80 + 1];
extern struct Proc * gProcTreeRootArray[14];
extern struct Unknown02190ce0 data_02190ce0;

#endif // PROC_H
