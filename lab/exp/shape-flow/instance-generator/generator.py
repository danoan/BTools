from __init__ import *
import subprocess,sys,os,time

from param_combinator import *
from config import *
from template_render import *

SCRIPT_FOLDER="set in read  input"
BINARY_FOLDER="set in read  input"

def resolve_output_folder(c):
    output_folder="%s/%s" % (os.path.dirname(SCRIPT_FOLDER),"output")
    for e in c:
        output_folder += "/" + e['path']

    return output_folder


def regions_of_interest(c):
    outputFolder = resolve_output_folder(c)
    shape,method,radius,levels,gs = c

    outputFilepath="%s/%s" % (outputFolder,"odr.svg")

    binary = "%s/%s" % (BINARY_FOLDER,"regions-of-interest")
    subprocess.call( [binary,
                      "%s%s" % ("-S",shape['value']),
                      "%s%d" % ("-r",radius['value']),
                      "%s%s" % ("-p","double"),
                      "%s%d" % ("-n",4),
                      "%s%d" % ("-l",levels['value']),
                      "%s%f" % ("-h", gs['value']),
                      outputFilepath
                      ] )

def shape_flow(c):

    outputFolder = resolve_output_folder(c)
    shape,method,radius,levels,gs = c


    binary = "%s/%s" % (BINARY_FOLDER,"shape-flow")
    subprocess.call( [binary,
                      "%s%s" % ("-S",shape['value']),
                      "%s%d" % ("-r",radius['value']),
                      "%s%d" % ("-i",200),
                      "%s%s" % ("-p","double"),
                      "%s%d" % ("-n",4),
                      "%s%d" % ("-l",levels['value']),
                      "%s%f" % ("-q",1),
                      "%s%f" % ("-t",0),
                      "%s%f" % ("-g",0),
                      "%s%s" % ("-m",method['value']),
                      "%s%f" % ("-h", gs['value']),
                      outputFolder
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
    if len(sys.argv)<2:
        print("Parameters missing! BTOOLS_BIN_FOLDER")
        exit(1)

    global SCRIPT_FOLDER,BINARY_FOLDER

    SCRIPT_FOLDER = os.path.dirname( os.path.realpath(__file__) )
    BINARY_FOLDER = sys.argv[1]


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
        shape_flow(c)
        regions_of_interest(c)
        summary_flow(c)

    render_template("shape-flow",CONFIG_LIST,"%s/%s" % (os.path.dirname(SCRIPT_FOLDER),"output"))

if __name__=='__main__':
    main()