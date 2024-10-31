"""
Implements functions necessary for typechecking in parser.py
"""

import itertools

def get_sublists(tup: tuple) -> list[tuple]:
    """
    Purpose: Creates a list of tuples containing all permutations in all orders of the given tuple

    First obtains all possible combinations of the list
    Then adds all permutations of those combinations

    Returns those permutations
    """
    result = []
    
    for r in range(len(tup) + 1):
        result.extend(itertools.combinations(tup, r))
    
    for r in range(1, len(tup) + 1):
        for combo in itertools.combinations(tup, r):
            result.extend(itertools.permutations(combo))
    
    return result

def get_combinations(tup1: tuple, tup2: tuple) -> list[tuple]:
    """
    Returns the cartesian product of the two tuples
    """
    return itertools.product(tup1, tup2)