import subprocess,sys,os

PROJECT_FOLDER="set-via-parameter"
BIN_FOLDER="set-in-read-input"
SCRIPT_FOLDER="set-in-read-input"
BASE_OUTPUT_FOLDER="set-in-read-input"

def recCombinations(maxList,curr,combList):

    if len(maxList)==0:
        combList.append(curr)
        return

    for el in range(0,maxList[0]):
        recCombinations(maxList[1:],curr+[el],combList)

def combinations(configList):
    numParams = len(configList)
    maxList = [ len(el) for el,_ in configList ]

    combList=[]
    recCombinations(maxList,[],combList)

    for c in combList:
        yield tuple( configList[i][0][c[i]] for i in range(numParams) )


GRID_STEP=[1.0,0.5,0.25]
SHAPES=["wave","triangle","square","ellipse","flower"]#"ball","pentagon","heptagon"]
RADIUS=[1,2,3,5]
ITERATIONS=[100]
PROFILE=["single","double"]#,"single-opt","double-opt"]
NEIGHBORHOOD=[4,8]
LEVELS=[1,2,-1,-2]#2,3,-3,-2,-1]
LENGTH_TERM=[0,0.1]
SQ_TERM=[1.0]
DATA_TERM=[0]
METHOD=["improve"]
OPT_IN_COMPUTATION=[False]#True,False]
IGNORE_OPT_POINTS_COMPUTATION_AREA=[False]#True,False]

CONFIG_LIST=[ (GRID_STEP,"grid_step"),
              (SHAPES,"shape"), (RADIUS,"radius"), (ITERATIONS,"iterations"),
              (PROFILE,"profile"), (NEIGHBORHOOD,"neighborhood"),
              (LEVELS,"levels"), (LENGTH_TERM,"length"),
              (SQ_TERM,"sq_term"), (DATA_TERM,"data_term"), (METHOD,"method"),
              (OPT_IN_COMPUTATION,"opt_in_computation"),
              (IGNORE_OPT_POINTS_COMPUTATION_AREA,"ignore_opt_points") ]


def valid_combination(c):
    _,_,radius,_,profile,_,levels,_,_,_,_,opt,_ = c

    flag=True

    if radius==1:
        flag=flag and (levels==1 or levels==-1)

    if profile=="single-opt" or profile=="double-opt":
        flag=flag and (levels==1)
        flag=flag and (opt==True)


    return flag

def resolve_output_folder(gs,shape,radius,iterations,profile,neigh,levels,length,sq,data,method,opt,ignoreOptApp):
    outputFolder = "%s/%s/%s/%s/neigh_%d/radius_%d/level_%d/%s/%s/gs_%.2f" % (BASE_OUTPUT_FOLDER,shape,method,
                                                                                 profile,neigh,radius,levels,
                                                                                 "opt" if opt else "no-opt",
                                                                                 "ignore-optApp" if ignoreOptApp else "count-optApp",gs)

    return outputFolder

def regions_of_interest(c):
    outputFolder = resolve_output_folder(*c)
    gs,shape,radius,iterations,profile,neigh,levels,length,sq,data,method,opt,ignoreOptApp = c

    outputFilepath="%s/%s" % (outputFolder,"odr.svg")

    binary = "%s/%s" % (BIN_FOLDER,"regions-of-interest/regions-of-interest")
    subprocess.call( [binary,                  
                      "%s%s" % ("-S",shape),
                      "%s%d" % ("-r",radius),
                      "%s%s" % ("-p",profile),
                      "%s%d" % ("-n",neigh),
                      "%s%d" % ("-l",levels),
                      "%s" % ("-o" if opt else ""),
                      "%s%f" % ("-h", gs),
		      outputFilepath	
                      ] )

def shape_flow(c):

    outputFolder = resolve_output_folder(*c)
    gs,shape,radius,iterations,profile,neigh,levels,length,sq,data,method,opt,ignoreOptApp = c

    binary = "%s/%s" % (BIN_FOLDER,"shape-flow/shape-flow")
    subprocess.call( [binary,                      
                      "%s%s" % ("-S",shape),
                      "%s%d" % ("-r",radius),
                      "%s%d" % ("-i",iterations),
                      "%s%s" % ("-p",profile),
                      "%s%d" % ("-n",neigh),
                      "%s%d" % ("-l",levels),
                      "%s%f" % ("-q",sq),
                      "%s%f" % ("-t",data),
                      "%s%f" % ("-g",length),
                      "%s%s" % ("-m",method),
                      "%s" % ("-o" if opt else ""),
                      "%s" % ("-x" if ignoreOptApp else ""),
                      "%s%f" % ("-h", gs),
		      outputFolder	
                      ] )

def summary_flow(c):
    binary = "%s/%s" % (BIN_FOLDER,"summary-flow/summary-flow")
    flow_images_folder_path=resolve_output_folder(*c)
    shape=c[1]
    jump=5
    subprocess.call( [binary,
                      flow_images_folder_path,
                      shape,
                      str(jump)])

    subprocess.call( [binary,
                      flow_images_folder_path,
                      shape,
                      str(jump),"eps"])

def create_plots(shape,output_folder):
    binary = "%s/%s" % (SCRIPT_FOLDER,"create-plots.sh")
    data_folder=BASE_OUTPUT_FOLDER
    mode=0

    subprocess.call( [binary,
                      shape,
                      data_folder,
                      output_folder,
                      str(mode)])

def total_combinations():
    total=0
    combs = combinations(CONFIG_LIST)
    for c in combs:
        if valid_combination(c):
            total+=1
    return total

def read_input():
    if len(sys.argv)<3:
        print("Parameters missing! PROJECT_FOLDER RELATIVE_BUILD_FOLDER")
        exit(1)

    global PROJECT_FOLDER,BIN_FOLDER, BASE_OUTPUT_FOLDER, SCRIPT_FOLDER
    PROJECT_FOLDER=sys.argv[1]
    BIN_FOLDER="%s/%s/%s" % (PROJECT_FOLDER,sys.argv[2],"modules/Applications")
    SCRIPT_FOLDER="%s/%s" % (PROJECT_FOLDER,"modules/lab/exp/shape-flow/plot-scripts")
    BASE_OUTPUT_FOLDER="%s/%s" % (PROJECT_FOLDER,"modules/lab/exp/shape-flow/output")

def main():
    read_input()
    print("Total combinations: ",total_combinations())
    for c in combinations(CONFIG_LIST):
        if valid_combination(c):
            shape_flow(c)
            summary_flow(c)
            regions_of_interest(c)


    for shape in SHAPES:
        create_plots(shape,"%s/%s" % (BASE_OUTPUT_FOLDER,"plots") )


if __name__=='__main__':
    main()
