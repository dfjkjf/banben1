/*
# 代码质量要求

## 外貌长相：代码风格

## 衣着搭配：封装接口

## 工作能力：可重用代码

## 驾驭复杂局面的能力：可重入函数和线程安全

## 项目要求
实现可以广泛通用的命令行菜单子系统组件

```
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_MAX_LINE 32
#define DESC_LEN     128
#define CMD_NUM      10

int Help();
int Quit();

typedef struct DataNode
{
    char *cmd;
    char *desc;
    int (*handler)();
    struct DataNode *next;
}tDataNode;

static tDataNode head[] = 
{
    {"help", "this is help cmd!", Help, &head[1]},
    {"version", "menu program v1.0", NULL, &head[2]},
    {"quit", "Quit from menu", Quit, NULL}
};

int main(int argc, char const *argv[])
{
    while (1) {
        char cmd[CMD_MAX_LINE];
        printf("Input a cmd >");
        scanf("%s", cmd);
        tDataNode *p = head;
        while (p != NULL) {
            if (strcmp(p->cmd, cmd) == 0) {
                if (p->handler != NULL)
                    p->handler();
                else
                    printf("%s - %s\n", p->cmd, p->desc);
                break;
            }
            p = p->next;
        }
        if (p == NULL)
            printf("This is a wrong cmd!\n");
    }
    return 0;
}

int Help()
{
    printf("Menu List\n");
    tDataNode *p = head;
    while (p != NULL) {
        printf("%s - %s\n", p->cmd, p->desc);
        p = p->next;
    }
    return 0;
}

int Quit()
{
    exit(0);
}

1. 这段代码不错，但要使其符合封闭原则
2. 模块复用 和 系统复用
层级划分：一般分为 业务逻辑层 和 数据存储层。如上述代码，分为 遍历数据结构查询数据 和 命令逻辑设计
为使 数据存储层 适应多种数据结构，应抽象

linklist.h
```
typedef struct DataNode
{
    char *cmd;
    char *desc;
    int (*handler)();
    struct DataNode *next;
}tDataNode;

tDataNode *FindCmd(tDataNode *head, char *cmd);
int ShowAllCmd(tDataNode *head);
```

linklist.c
```
tDataNode *FindCmd(tDataNode *head, char *cmd)
{
    if (head == NULL || cmd == NULL)
        return NULL;
    tDataNode *p = head;
    while (p != NULL) {
        if (strcmp(p-cmd, cmd) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int ShowAllCmd(tDataNode *head)
{
    printf("Menu List\n");
    tDataNode *p = head;
    while (p != NULL) {
        printf("%s - %s\n", p->cmd, p->desc);
        p = p->next;
    }
}
```

menu.c
```
int Help();

static tDataNode head[] = 
{
    {"help", "this is help cmd!", Help, &head[1]},
    {"version", "menu program v1.0", NULL, &head[2]},
    {"quit", "Quit from menu", Quit, NULL}
};

int main(int argc, char const *argv[])
{
    while (1) {
        char cmd[CMD_MAX_LINE];
        printf("Input a cmd >");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if (p == NULL) {
            printf("This is a wrong cmd!\n");
            continue;
        }
        if (p->handler != NULL)
            p->handler();
        else
            printf("%s - %s\n", p->cmd, p->desc);
    }
    return 0;
}

int Help()
{
    ShowAllCmd(head);
    return 0;
}

```

# 代码设计规范
1. KISS(keep it simple & stupid)傻瓜化
一个函数或方法，只做一件事（事的定义由抽象层级不同而不同）
2. 设计与实现保持一致
*设计用伪代码来描述系统结构*
3. 不和陌生人说话
4. 合理利用控制结构和数据结构

bracket|base|percent
---:|---:|---:
0|0|0.10
10000|1000|0.12
20000|2200|0.15
30000|3700|0.18
40000|5500|0.20
```
typedef struct DataNode
{
    size_t bracket;
    size_t base;
    double percent;
}tDataNode;

static tDataNode head[][3] =
{
    {"help", "this is help cmd!", Help, &head[1]},
    {"version", "menu program v1.0", NULL, &head[2]},
    {"quit", "Quit from menu", Quit, NULL}
};
for (int i = 0, level = 0; i < 5 - 1; ++i)
    if (income > bracket[i])
        level = level + 1;
tax = base[level] + (income - bracket[level]) * percent[level];
```
5. 一定要有错误处理
实现基本功能才是第一步，成熟的产品还要花费4倍的时间调试优化，即二八原则
断言 VS 错误处理
肯定时使用断言；可能时使用错误处理
Assert(p != NULL);
int fd = fopen("1.txt", R);
if (fd == 0) {
    // error handling
} else {
    // use fd to do something
}

