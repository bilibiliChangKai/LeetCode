# 证精确的4SAT是NP-完全问题

> 此题源于《算法概论》（清华大学出版社）课后习题8.8

---

## 题目解释

精确4SAT（EXACT 4SAT）问题是这样的：输入为一组字句，每个字句都是恰好4个文字的析取，且每个变量最多在每个字句出现一次。目标是求它的满足赋值——如果该赋值存在。

总结下来，EXACT 4SAT问题是SAT的一个变种，即有约束条件的SAT。但是，我们仍然可以进行SAT -> EXACT 4SAT的归约，归约过程如下。

---

## SAT -> EXACT 4SAT归约

####**首先，证明任意一个SAT问题都能映射成EXACT 4SAT问题：**

设函数$F$表示字句的变量数目，例如：$F(a \vee b) = 2$

对任意一个SAT问题，先将字句中的相同变量约去，很明显，$a \vee a$可以约成$a$ ，$a \vee \overline{a}$恒为真，可以约去。约去相同变量后，它的任意一个字句p可能有三种情况：

1. $F(p) < 4$ ：

   对该字句，新加入一个变量x，可得：

   $p \equiv p \land (x \vee \overline{x}) \equiv (p \vee x) \land (p \vee \overline{x})$

   我们因此就可以把一个字句p转换成两个字句q1，q2，其中$F(q1) = F(q2) = F(p) + 1$

   反复几次上述操作，即可将一个$F(p) < 4$的字句转换成多个字句q1...qn，其中$F(q1) = F(q2) = ... = F(qn) = 4$

2.  $F(p) = 4$：

   该字句符合EXACT 4SAT的字句，无需转换。

3. $F(p) > 4$ ：

   假设该字句其中有两个变量，分别为a，b，即$p = (a \vee b\ \vee \ ...)$

   新加入一个变量x，让x替代$a \vee b$ ，得到新的字句$q = (x \vee\ ...)$

   目前出现了一个新的问题，即$x$和$a \vee b$并不等价，接下来我们通过新加入额外的字句来解决这个问题。

   由于SAT问题中，变量只能取使最终结果为T的布尔值，当变量取值使最终结果为F则无法取值，我们利用这个特点，当$x, a, b$ 的取值使$x \neq a \vee b$时，最终结果为F，这样剩下的$x, a, b$取值必定满足$x = a \vee b$ 。

   先构造出$x, a, b$的真值表：

   | x    | a    | b    | $x = a \vee b$ |
   | :--- | :--- | :--- | :------------- |
   | T    | T    | T    | T              |
   | T    | T    | F    | T              |
   | T    | F    | T    | T              |
   | T    | F    | F    | F              |
   | F    | T    | T    | F              |
   | F    | T    | F    | F              |
   | F    | F    | T    | F              |
   | F    | F    | F    | T              |

   用析取范式表达该真值表，可得：
   $$
   (\overline{x} \vee a \vee b) \land (x \vee \overline{a} \vee \overline{b}) \land (x \vee \overline{a} \vee b) \land (x \vee a \vee\overline{b})
   $$
   因此，字句p就能用五个其他字句代替：（四个字句分别命名为q1, q2, q3, q4）
   $$
   p  \equiv q \land q1 \land q2 \land q3 \land q4 \equiv q \land (\overline{x} \vee a \vee b) \land (x \vee \overline{a} \vee \overline{b}) \land (x \vee \overline{a} \vee b) \land (x \vee a \vee\overline{b})
   $$
   其中$F(q) = F(p) - 1$ ，$F(q1) = F(q2) = F (q3) = F(q4) = 3$

   对q反复进行1和3中的操作，即可将一个$F(p) > 4$的字句转换成多个字句q1...qn，其中$F(q1) = F(q2) = ... = F(qn) = 4$

对SAT问题中的每一个字句都进行上述转换，任意一个SAT问题都能映射成EXACT 4SAT问题，证毕。

####**其次，证明映射的EXACT 4SAT问题的解可转化为原SAT的解：**

这个步骤很好证明，由于我们新加入的变量仅仅是用于填补和制约，因此新加入的变量的解对原SAT问题的解没有影响，当我们得到EXACT 4SAT问题的解，抛弃掉所有新加入的变量，即为原SAT问题的解。

####**最后，证明该问题转换的时间复杂度是多项式时间的：**

设原SAT问题有n个字句，每个字句都有数量不等的不同变量，字句里总共有m个变量（包含相同变量）。

定义$p1, p2...pn$为SAT问题中的不同字句，$t1 = F(p1), t2 = F(p2)... tn = F(pn)$ ，即$m = \sum_{i = 1}^{n}ti$

同理，对其中任意字句$pi \in \{p1, p2...pn\}$ ，：

1. $ti < 4$ ：

   由于$F(pi)$每加1就需要翻倍，因此，字句p最多转换成8个符合EXACT 4SAT的字句，所花的时间复杂度不超过$O(8 \cdot ti)$

2. $ti = 4$ ：

   无需转换。

3. $ti > 4$ ：

   由于$F(pi)$每减1就需要生成4个辅助字句，将4个辅助字句转换成符合EXACT 4SAT的字句又需要翻倍，因此，$F(pi)$每减1就需要生成8个符合EXACT 4SAT的字句，所花的时间复杂度也不超过$O(8 \cdot ti)$

因此，将所有的字句转换后，所花的时间复杂度不超过$O(8 \cdot m)$ ，证毕。

---

## 总结

之前已经证明，SAT问题可以归约成EXACT 4SAT问题，由于SAT问题是NP-完全问题，因此EXACT 4SAT问题也是NP-完全问题，证毕。



