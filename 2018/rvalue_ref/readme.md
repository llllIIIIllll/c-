Rvalue references solve at least two problems:
1. Implementig move semantics
2. Perfect forwarding

An lvalue is an expression that refers to a memory location and allows us to take the address of that memory location via the & operator.
An rvalue is an expression that is not an lvalue

Rvalue references allow a function to branch at compile time(via overload resoulution) on the codition "Am I being called on an lvalue or an rvalie?"

* the std::move "turns its argumets int an rvalue even if it isn't "
* archieves that by "hiding the name"

A& &   -> A&
A& &&  -> A&
A&& &  -> A&
A&& && -> A&&

