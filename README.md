# Set Cover problem
This is the repository of our implementation of various algorithms to solve set cover problem in CSE_462 sessional

## command to run :
```
g++ -std=c++17 -Wshadow -Wall -o set_cover_dp set_cover_dp.cpp -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUGa && ./set_cover_dp
g++ -std=c++17 -Wshadow -Wall -o set_cover_greedy set_cover_greedy.cpp -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUGa && ./set_cover_greedy

time ./set_cover_dp

time ./set_cover_greedy

time python3 set_cover_LP.py

automatically access inputs
```

## Sample test cases

```
5

5 4
1 2 3 4 5
1.0 3.0 5.0 2.0
3  1 2 3
2  2 4
2  3 4
2  4 5


13 5
1 2 3 4 5 6 7 8 9 10 11 12 13
1 1 1 1 1 
2  1 2
4  2 3 4 5
8  6 7 8 9 10 11 12 13
7  1 3 5 7 9 11 13
7  2 4 6 8 10 12 13


5 3
1 2 3 4 5
5.0 10.0 3.0
3  4 3 1
2  2 5
4  1 4 3 2 


10 11
1 2 3 4 5 6 7 8 9 10
22.0 20.0 2.0 1.8 20.9 43.0 3.0 2.9 100.9 30.5 -30.2
4  1 2 3 4
4  2 3 4 5
4  3 4 5 6  
4  4 5 6 7
4  5 6 7 8
6  6 7 8 9 1 4
4  7 8 9 10
3  8 9 10
2  9 10
1  10
2  10 1

3 4
1 2 3
10.5 20.5 30.5 30.4
2  1 2
2  1 3
2  2 3
2  1 2 

```

```
IO Format :

n m
item_1  item_2 item_3 ...  item_n
cost_1 cost_2 ... cost_m
l1 s_11 s_12 ... s_1l1
l2 .................
.
.
lm  s_m1 s_m2 ... s_mlm


total_cost
10011....001 (bit string of length m)
```
