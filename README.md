# DNFMinimizer
The project is included in the practical work of FTL ;)
# What is DNF?
Disjunctive normal form (DNF) - in Boolean logic is a normal form in which a Boolean formula has the form of a disjunction of conjunctions of literals. The formula of Any Boolean can be given in DNF.[1] To do this, you can use the law of double negation, De Morgan's law, and the law of distributivity. [wiki](https://ru.wikipedia.org/wiki/%D0%94%D0%B8%D0%B7%D1%8A%D1%8E%D0%BD%D0%BA%D1%82%D0%B8%D0%B2%D0%BD%D0%B0%D1%8F_%D0%BD%D0%BE%D1%80%D0%BC%D0%B0%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D1%84%D0%BE%D1%80%D0%BC%D0%B0)

$\neg(A \lor B)=\neg A \land \neg B$ - De Morgan's law

$\neg(\neg A) = A$ - law of double negation

$A \land (B \lor C) = A \land B \lor A \land C$ - law of distributivity

# What is DNF minimization?
DNF solves the problem of simplifying logical functions. But a function can have many DNFs.
Let us denote the length of the DNF **$L(F())$** as the number of variables used.

**$F(x, y, z) = x \land \neg y \land z \lor x \land y$**

**$L(F(x, y, z)) = 5$**

The minimum DNF has the shortest length $L(F())$. There may be several such DNFs

# Minimization algorithm
A Boolean function can be uniquely specified by its number and number of variables. 
There are Boolean functions of $n$ variables $2^n$
1) Convert the function number to double form and pad leading zeros to length $2^n$. This line will be a column of function values.
2) Construct a table with all conjunctions.
3) Cross out lines with value 0 in a column F
4) In each column, cross out all sets that are numerically the same as those already crossed out.
5) Use the law of absorption on the remaining sets.
6) let's sort through all the DNFs from the remaining sets

$x \lor x \land y = x \land (1 \lor y) = x$ - law of absorption

![image](https://github.com/LKolinko/DNFMinimizer/assets/131384241/307bd52e-749b-4e6e-8982-bef315307ad2)

# Installation
1) Clone the repo

   `git clone https://github.com/LKolinko/DNFMinimizer`

2) Use cmake

   `cd ./DNFMinimizer`

   `cmake .`

   `cmake --build ./`

3) Launch and enjoy :)

   `./DNFMinimizer`
