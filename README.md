# Multiplication of Matrix using threads

 -**Multiplication** of matrix does take time surely. Time complexity of matrix multiplication is O(n^3) using normal matrix multiplication. And Strassen algorithm improves it and its time complexity is O(n^(2.8074)).But, Is there any way to improve the performance of matrix multiplication using the normal method.
 
 
 -**Multi-threading** can be done to improve it. In multi-threading, instead of utilizing a single core of your processor, we utilizes all or more core to solve the problem. We create different threads, each thread evaluating some part of matrix multiplication. Depending upon the number of cores your processor has, you can create the number of threads required. Although you can create as many threads as you need, a better way is to create each thread for one core.In second approach,we create a separate thread for each element in resultant matrix. Using pthread_exit() we return computed value from each thread which is collected by pthread_join(). This approach does not make use of any global variables.
 
 
 **NOTE It is advised to execute the program in linux based system**
 `g++ -pthread ThreadMatrixMulti.cpp`
