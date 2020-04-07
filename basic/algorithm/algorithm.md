[TOC]

#C语言陷阱
1. 内存重叠的处理
2. 临时变量太多或者没安全释放
3. 没有测试内存越界
4. 指针操作不熟悉

#面试考察的编程基本功
1. 程序风格（缩进，括号，变量名）
2. 编码习惯（异常检查，边界处理）
3. 沟通（让面试官时刻明白你的意图）
4. 测试（主动写出合理的Testcase）

从一个入门题说起
```
void *memmove(void * dst, const void *src,size_t n)
{
    char *p1 = dst;
    const char *p2 = src;

    if (p2 > p1) {
        p2 += n;
        p1 += n;
        while (n-- != 0) {
            *--p1 = *--p2;
        } 
    } else {
        while (n-- != 0) {
            *p1++ = *p2++;
        }
    }

    return p1;
}
```
一个递归题
```
class Solution {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (root == NULL) {
            return NULL;
        }

        TreeNode *tmpNode = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(tmpNode);
        return root;
    }
};
```
