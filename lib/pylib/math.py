def pow(base, exp):
    if exp == 0:
        return 1
    if exp == 1:
        return base
    res = base
    for i in range(exp):
        res = res * base

    return res