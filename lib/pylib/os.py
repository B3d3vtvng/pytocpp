#Only works for Unix-based systems at the moment :(

def os_run_with_pipe(command):
    fcreate("/tmp/osrwptemp")
    os_run(command + " >/tmp/osrwptemp")
    output = fread("/tmp/osrwptemp")
    os_run("rm /tmp/osrwptemp")
    return output

def os_remove(fname):
    os_run("rm " + fname)
    return None

def os_listdir(dirname):
    dircontent = os_run_with_pipe("ls")
    cur_fname = ""
    fnames = []
    for char in dircontent:
        if char == "\n":
            fnames = fnames + [cur_fname]
            cur_fname = ""
            continue
        cur_fname = cur_fname + char
    
    return fnames
