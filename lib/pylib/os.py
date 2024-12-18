#Only works for Unix-based systems at the moment :(

def os_run_with_pipe(command):
    fcreate("/tmp/osrwptemp")
    os_run(command + " >/tmp/osrwptemp")
    output = fread("/tmp/osrwptemp")
    os_run("rm /tmp/osrwptemp")
    return output