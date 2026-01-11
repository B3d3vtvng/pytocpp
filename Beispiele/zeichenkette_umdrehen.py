# Zu transpilieren mit "python3 main.py Beispiele/zeichenkette_umdrehen.py"

def zeichenkette_umdrehen(string):
    if string == "":
        return ""
    if len(string) == 1:
        return string
    new_string = ""
    for _char in string:
        new_string = _char + new_string
    return new_string

print(zeichenkette_umdrehen("Hello World"))
