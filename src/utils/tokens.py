"""
Token class for the pytoc Python Transpiler
"""

class Token():
    def __init__(self, ln, token_idx, token_t, token_v=None):
        """
        Attributes:

        ln: The line the token is situated in
        token_idx: The index of the start of the token
        token_t: The tokentype of the token
        token_v: The value of the token (if it has one)
        """
        self.ln = ln
        self.token_idx = token_idx
        self.token_t = token_t
        self.token_v = token_v

    def __repr__(self):
        return f"{self.ln}:{self.token_idx}: {self.token_t}:{self.token_v}"