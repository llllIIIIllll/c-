#include <iostream>
#include <taskflow/taskflow.hpp>

int main()
{
    tf::Taskflow tf(std::thread::hardware_concurrency());
    auto [A, B, C, D] = tf.silent_emplace(
    [] () { std::cout << "TaskA\n"; },               //  the taskflow graph
    [] () { std::cout << "TaskB\n"; },               // 
    [] () { std::cout << "TaskC\n"; },               //          +---+          
    [] () { std::cout << "TaskD\n"; }                //    +---->| B |-----+   
    );                                               //    |     +---+     |
                                                     //  +---+           +-v-+ 
    A.precede(B);  // B runs after A                 //  | A |           | D | 
    A.precede(C);  // C runs after A                 //  +---+           +-^-+ 
    B.precede(D);  // D runs after B                 //    |     +---+     |    
    C.precede(D);  // D runs after C                 //    +---->| C |-----+    
                                                     //          +---+          
    tf.wait_for_all();  // block until finished

    return 0;

}
