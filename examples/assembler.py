TOKENS = ["inc", "dec", "jmp", "tst", "hlt"]


def has_jmpval(token_name):
    return token_name == "jmp" or token_name == "tst"

def has_numval(token_name):
    return token_name == "inc" or token_name == "dec"

def make_token(line):
    token = []
    line = strip(line)
    opcode = line[:3]

    if opcode not in TOKENS:
        print("Invalid Opcode")
        return -1

    token[0] = opcode

    if opcode == "hlt":
        return token
    
    val = strip(line[3:])
    if val == "":
        print("Invalid token value")
        return -1
    
    token[1] = int(val)

    return token

def make_tokens(raw_input):
    tokens = []
    for line in raw_input:
        cur_token = make_token(line)
        if cur_token == -1:
            return -1
        tokens += [cur_token]

    return tokens

def read_input(fname):
    raw_input = freadlines(fname)
    return raw_input

def main():
    if argc < 2:
        print("Error: No filename provided")
        return 1
    raw_input = read_input(argv[1])
    tokens = make_tokens(raw_input)
    if tokens == -1:
        return -1
    print(tokens)

    return 0

error_code = main()
exit(error_code)