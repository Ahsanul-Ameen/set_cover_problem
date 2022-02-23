#!/usr/bin/env python
# coding: utf-8

# 

# ```
# import packages
# ```

# In[1]:


#get_ipython().system('pip install ortools')


# ```
# from ortools.linear_solver import pywraplp
# from ortools.init import pywrapinit
# ```

# 

# In[2]:


from ortools.linear_solver import pywraplp
from ortools.init import pywrapinit


# ```
# Read input as the form
# 
# 5 4
# 1 2 3 4 5
# 1.0 3.0 5.0 2.0
# 3  1 2 3
# 2  2 4
# 2  3 4
# 2  4 5
# ```

# In[3]:


with open('./sample_io.txt') as f:
    n, m = [int(x) for x in next(f).split()]
    universe = [int(x) for x in next(f).split()]
    costs = [float(x) for x in next(f).split()]
    family = [[int(x) for x in line.split()] for line in f]
    
    family = [x for x in family if x]
    
    for i in range(m):
        family[i].pop(0)
    
print(n, " ", m)
print(universe)
print(costs)
print(family)


# ```
# Solve the relaxed version of LP
# ```
# <img src=".images/lp.png">

# In[4]:


def solve_lp(n, m, universe, costs, family):
    # Create the linear solver with the GLOP backend.
    solver = pywraplp.Solver.CreateSolver('GLOP')

    # Create the variables xi.
    var_names = ["x_" + str(i) for i in range(m)] # ['x_0', 'x_1', 'x_2', 'x_3']
    vars = [solver.NumVar(0, 1, x) for x in var_names]
    print('Number of variables =', solver.NumVariables())

    # add constraints
    # solver.Add(vars[0] >= 1)
    for v in universe:
        xs = []
        for i, S in enumerate(family):
            if v in S:
                xs.append(vars[i])
        solver.Add(sum(xs) >= 1)

    print('Number of constraints =', solver.NumConstraints())

    # Create the objective function, 3 * x + y.
    objective = solver.Objective()
    for i, x in enumerate(vars):
        objective.SetCoefficient(x, costs[i])
    objective.SetMinimization()

    solver.Solve()
    print('Solution:')
    print('Objective value =', objective.Value())

    for i, x in enumerate(vars):
        print("\t", var_names[i], " : ", x.solution_value())

    return [x.solution_value() for x in vars]
    


# ```
# all x in x_star has x in [0, 1]
# ```

# In[5]:


x_star = solve_lp(n, m, universe, costs, family)
print("optimal fractional solution x_star = ", x_star)


# ```
# Unlike the case of vertex cover, we cannot round the x∗i to the nearest integer, 
# because if an element u belongs to 100 sets, it could be that x∗i = 1/100 for each of those sets, 
# and we would be rounding all those numbers to zero, leaving the element u not covered
# ```

# ```
# Implement the RandomPick algorithm
# ```
# <img src=".images/rp.png">
# 
# `note that our m is denoted as n here`

# In[6]:


# import random choice
import random
import numpy as np


def RandomPick(m, costs, x):
    flags = ['0'] * m
    cost = 0.0

    #draw = random.choices(population=[i for i in range(m)], k=m, weights=x)
    # print(x)
    draw = np.random.choice([i for i in range(m)], m, replace=True, p=x)
    # print(draw)
    for i in draw:
        flags[i] = '1'

    for i, f in enumerate(flags):
        if f == '1':
            cost += costs[i]


    return ''.join([str(elem) for elem in flags]), cost 
    


# ```
# pass the probabilities
# ```

# In[7]:


flags, cost =  RandomPick(m, costs, x=[float(x)/sum(x_star) for x in x_star])
print("Cost : " , cost)
print("flags : ", flags)


# ```
# Implement RandomizedRound
# ```
# <img src=".images/rr.png">

# In[8]:


def RandomizedRound(m, universe, family, costs, x):
    flags = ['0'] * m
    cost = 0.0

    uncovered = universe.copy()

    while len(uncovered) != 0:
        # draw = random.choices(population=[i for i in range(m)], k=m, weights=x)
        draw = np.random.choice([i for i in range(m)], m, replace=True, p=x)
        # print(draw)
        # we've picked them
        for i in draw:
            flags[i] = '1'
            # ith set of family would cover some items in universe
            for u in family[i]:
                if u in uncovered: 
                    uncovered.remove(u)

    for i, f in enumerate(flags):
        if f == '1':
            cost += costs[i]


    return ''.join([str(elem) for elem in flags]), cost 


# In[9]:


flags, cost =  RandomizedRound(m, universe, family, costs, x=[float(x)/sum(x_star) for x in x_star])
print("Cost : " , cost)
print("flags : ", flags)


# ```
# Combine all
# ```

# In[10]:


def execute(file_name):
    print("-------- Execution on ", file_name, "----------")

    with open(file_name) as f:
        n, m = [int(x) for x in next(f).split()]
        universe = [int(x) for x in next(f).split()]
        costs = [float(x) for x in next(f).split()]
        family = [[int(x) for x in line.split()] for line in f]
        
        family = [x for x in family if x]
        
        for i in range(m):
            family[i].pop(0)
    
    # print(n, " ", m)
    # print(universe)
    # print(costs)
    # print(family)

    x_star = solve_lp(n, m, universe, costs, family)
    print("optimal fractional solution x_star = ", x_star)

    print("\nRandomPick")
    flags, cost =  RandomPick(m, costs, x=[float(x)/sum(x_star) for x in x_star])
    print("Cost : " , cost)
    print("chosen sets : ", flags)

    print("\nRandomizedRound")
    flags, cost =  RandomizedRound(m, universe, family, costs, x=[float(x)/sum(x_star) for x in x_star])
    print("Cost : " , cost)
    print("chosen sets : ", flags, "\n\n")


# In[11]:


execute("../test/1.txt")


# In[12]:


execute("../test/2.txt")


# In[13]:


execute("../test/3.txt")


# In[14]:


execute("../test/4.txt")


# In[26]:


execute("../test/5.txt")


# In[ ]:




