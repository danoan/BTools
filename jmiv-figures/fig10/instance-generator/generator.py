import subprocess,sys,os,time

from param_combinator import *
from config import *

SCRIPT_FOLDER="set in read  input"
BINARY_FOLDER="set in read  input"
INPUT_FOLDER="set in read input"

def realpath_gcobject(gcobject):
    return "%s/%s" % (INPUT_FOLDER,gcobject)

def resolve_output_folder(c):
    output_folder="%s/%s" % (SCRIPT_FOLDER,"output")
    for e in c:
        output_folder += "/" + e['path']

    return output_folder

def boundary_correction(c):
    gcobject,method,radius,dt,sq,lt,iterations = c

    outputFolder=resolve_output_folder(c)

    print("Running experiment: ",*c)

    tstart = time.time()
    binary = "%s/%s" % (BINARY_FOLDER,"boundary-correction-app")
    subprocess.call( [binary,
                      realpath_gcobject(gcobject['value']),
                      "%s%d" % ("-r",radius['value']),
                      "%s%d" % ("-i",iterations['value']),
                      "%s%f" % ("-q",sq['value']),
                      "%s%f" % ("-t",dt['value']),
                      "%s%f" % ("-g",lt['value']),
                      "%s%s" % ("-m",method['value']),
                      "%s%s" % ("-o",outputFolder)])
    tend=time.time()

    print("*****Done in: %f seconds" % (tend-tstart,))

def export_seed_mask(c):
    gcobject,method,radius,dt,sq,lt,iterations = c

    outputFolder=resolve_output_folder(c)

    binary = "%s/%s" % (BINARY_FOLDER,"export-seed-mask")
    subprocess.call( [binary,
                      realpath_gcobject(gcobject['value']),
                      "%s/%s" % (outputFolder,"seeds.png")])

def read_input():
    if len(sys.argv)<2:
        print("Parameters missing! BTOOLS_BIN_FOLDER")
        exit(1)

    global SCRIPT_FOLDER,BINARY_FOLDER,INPUT_FOLDER

    SCRIPT_FOLDER = os.path.dirname( os.path.realpath(__file__) )
    BINARY_FOLDER = sys.argv[1]
    INPUT_FOLDER = "%s/%s" % (SCRIPT_FOLDER,"input")

def valid(c):
    gcobject,method,radius,dt,sq,lt,iterations = c
    if dt['value']==0 and sq['value']==0 and lt['value']==0:
        return False

    return True

def main():
    read_input()
    for c in combinations(CONFIG_LIST):
        if valid(c):
            boundary_correction(c)
            export_seed_mask(c)


if __name__=='__main__':
    main()