"""
Implements a functions that sorts tokens by line and index
"""

from src.utils.tokens import Token

def sort_tokens(tokens: list[Token]) -> list[Token]:
    return sorted(tokens, key=lambda x: (x.ln, x.token_idx))

    
