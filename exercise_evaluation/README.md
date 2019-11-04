## 编程目标
编写一个C程序，实现给定输入文档和关键词，能高亮显示文档中相关句子的关键词

## 程序说明
[本程序](./highlight.c)主要分为3个函数

1. split函数：给定分割符，将一个长字符串分割为若干个字串。
  * 可以将query分割成关键词组、将doc_text分割成句组。
2. hightlight函数：
  * 循环对每个句子处理：首先将每个句子通过split分为词组   
  * 遍历，看看这个句子中是否有关键词  
    * 如果没有关键词，那么跳过这个句子  
    * 如果有关键词，那么判断关键词的前后是否是连续关键词，并且添加相应的html标签的前后缀即可
    
## 样例输入输出
输入：  
* `query` : `information retrieve`  
* `doc_text` : `There are tons of information for us to retrieve on Internet.We can search Internet for answers.Especially when we can not tackle the problem independently.So it is essential for us to master some skills about information retrieve likewise.Right?`  

输出：
```
===========================
all keywords are as follows:
information
retrieve


===========================
all input sentences are as follows:
There are tons of information for us to retrieve on Internet
We can search Internet for answers
Especially when we can not tackle the problem independently
So it is essential for us to master some skills about information retrieve likewise
Right?


===========================
highlighted sentences are as follows:
There are tons of <font color=#c60a00> information </font> for us to <font color=#c60a00> retrieve </font> on Internet.
So it is essential for us to master some skills about <font color=#c60a00> information retrieve </font> likewise.

```
