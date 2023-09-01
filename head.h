#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define OK 1
#define ERROR 0
#define FOUND 1
#define NOTFOUND 0
#define YES 1
#define NO 0

typedef int status;

typedef struct LiteralNode{
    int data;
    struct LiteralNode* next;
}LiteralNode;

typedef struct ClauseNode{
    int num;//这个子句的文字个数
    struct LiteralNode* right;//是变化用的
    struct LiteralNode* left;//是不变的
    struct ClauseNode* down;
}ClauseNode;

typedef struct To_Clause{
    int sign;//判断是删的子句还是文字
    ClauseNode* target;//指向子句头节点
    struct To_Clause* next;
}To_Clause;

typedef struct Order_Table{
    To_Clause* right;
}Order_Table;

ClauseNode* Cnf_Parser(int* literal_num, char* filename, int init);
char* ChooseExample(void);
void init(int literal_num,int* Hash,int* truth_table,Order_Table* ot,Order_Table* ct,int* stack);
void check(ClauseNode* s,int *truth_table);
void Make_Constant_Table(ClauseNode* s,Order_Table* ct,int literal_num);
status Dpll_Solver(ClauseNode* s,int* truth_table,int literal_num,Order_Table* ot,int* stack,Order_Table* ct,int* Hash);
void Cnf_print(ClauseNode* s,status ans,int* truth_table,char* filename,int literal_num,Order_Table* ot,int* stack,Order_Table* ct,int* Hash);
void Hanidoku_Transform(int n,int (*h_table)[11]);
void Hanidoku_Game(int n);
//dpll_solver
ClauseNode* HasUnitClause(ClauseNode* s);
void Remove_Unit(ClauseNode* s,int unit_data,Order_Table* ot,Order_Table* ct);
void DeleteLiteral(ClauseNode* s,int unit_data,Order_Table* ot);
ClauseNode* DeleteClause(ClauseNode* s,Order_Table* ot);
ClauseNode* HasEmptyClause(ClauseNode* s);
int PickVar(ClauseNode* s,int literal_num);
ClauseNode* Add_Unit_Clause(ClauseNode* s,int var);
void Back_Track(int operate_times,ClauseNode* s,int* stack,Order_Table* ot);
void Unit_Back_Track(ClauseNode* s,Order_Table* ot,int re_num);
//cnf_parser
status GetInfo(char* cnf_cut,int* literal_num,int* clause_num,FILE* fp);
ClauseNode* ReadClauses(char* cnf_cut,FILE* fp,int* literal_num,int clause_num);
ClauseNode* CreatClauseUnit(char* cnf_cut,FILE* fp);
LiteralNode* CreatLiteralUnit(char* cnf_cut);

#endif // HEAD_H_INCLUDED
