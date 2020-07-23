from __init__ import *
import subprocess,sys,os,time

from param_combinator import *
from config import *

SCRIPT_FOLDER="set in read  input"
BINARY_FOLDER="set in read  input"
BASE_OUTPUT_FOLDER="set in read  input"

def resolve_output_folder(c):
    output_folder=BASE_OUTPUT_FOLDER
    for e in c:
        output_folder += "/" + e['path']

    return output_folder


def regions_of_interest(c):
    outputFolder = resolve_output_folder(c)
    shape,radius,levels,gs,iterations = c

    outputFilepath="%s/%s" % (outputFolder,"odr.svg")

    binary = "%s/%s" % (BINARY_FOLDER,"regions-of-interest")
    subprocess.call( [binary,
                      "%s%s" % ("-S",shape['value']),
                      "%s%d" % ("-r",radius['value']),
                      "%s%d" % ("-l",levels['value']),
                      "%s%f" % ("-h", gs['value']),
                      outputFilepath
                      ] )

def shape_flow(c):

    outputFolder = resolve_output_folder(c)
    shape,radius,levels,gs,iterations = c


    binary = "%s/%s" % (BINARY_FOLDER,"shape-flow")
    subprocess.call( [binary,
                      "%s%s" % ("-S",shape['value']),
                      "%s%d" % ("-r",radius['value']),
                      "%s%d" % ("-i",iterations['value']),
                      "%s%d" % ("-l",levels['value']),
                      "%s%f" % ("-q",1),
                      "%s%f" % ("-g",0),
                      "%s%f" % ("-h", gs['value']),
                      "%s%s" % ("-o",outputFolder)
                      ] )

def summary_flow(c):
    binary = "%s/%s" % (BINARY_FOLDER,"summary-flow")
    flow_images_folder_path=resolve_output_folder(c)

    shape=c[0]
    jump=5
    subprocess.call( [binary,
                      flow_images_folder_path,
                      "%s/summary.svg" % (flow_images_folder_path,),
                      str(jump)])

    subprocess.call( [binary,
                      flow_images_folder_path,
                      "%s/summary.eps" % (flow_images_folder_path,),
                      str(jump)])


def read_input():
    if len(sys.argv)<3:
        print("Parameters missing! BTOOLS_BIN_FOLDER BASE_OUTPUT_FOLDER")
        exit(1)

    global SCRIPT_FOLDER,BINARY_FOLDER,BASE_OUTPUT_FOLDER

    SCRIPT_FOLDER = os.path.dirname( os.path.realpath(__file__) )
    BINARY_FOLDER = sys.argv[1]
    BASE_OUTPUT_FOLDER = sys.argv[2]


def total_combinations():
    total=0
    combs = combinations(CONFIG_LIST)
    for c in combs:
        total+=1
    return total

def main():
    read_input()
    print("Total combinations: ",total_combinations())
    for c in combinations(CONFIG_LIST):
        if(valid_combination(c)):
            shape_flow(c)
            regions_of_interest(c)
            summary_flow(c)

if __name__=='__main__':
    main()
