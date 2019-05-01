import subprocess,sys,os

PROJECT_FOLDER="set-via-parameter"
BIN_FOLDER="set-in-read-input"
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


SHAPES=["triangle","square","pentagon","hexagon","ball","ellipse","flower"]
RADIUS=[3,5]
ITERATIONS=[100]
COMPUTATION_CENTER=["pixel","pointel","linel"]
COUNTING_MODE=["pixel"]
SPACE_MODE=["pixel","interpixel"]
PROFILE=["single","double","single-opt","double-opt","single-inner","double-inner"]
NEIGHBORHOOD=[4]
LEVELS=[-2,-3,2,3]
LENGTH_TERM=[0]
SQ_TERM=[1.0]
DATA_TERM=[0]
METHOD=["improve","probe"]
OPT_IN_COMPUTATION=[True,False]

CONFIG_LIST=[ (SHAPES,"shape"), (RADIUS,"radius"), (ITERATIONS,"iterations"),
              (COMPUTATION_CENTER,"computation_center"),
              (COUNTING_MODE,"counting_mode"), (SPACE_MODE,"space_mode"),
              (PROFILE,"profile"), (NEIGHBORHOOD,"neighborhood"),
              (LEVELS,"levels"), (LENGTH_TERM,"length"),
              (SQ_TERM,"sq_term"), (DATA_TERM,"data_term"), (METHOD,"method"),
              (OPT_IN_COMPUTATION,"opt_in_computation") ]


def valid_combination(c):
    _,_,_,cc,cm,sm,profile,_,levels,_,_,_,_,_ = c

    flag=True
    if cc=="pixel":
        flag=flag and cm=="pixel"

    if cc=="pointel" or cc=="linel":
        flag=flag and cm=="interpixel"

    if profile=="single-inner" or profile=="double-inner":
        flag=flag and cm=="linel"

    if sm=="interpixel":
        flag=flag and (levels>0)

    if sm=="pixel":
        flag=flag and (levels<0)

    return flag

def resolve_output_folder(shape,radius,iterations,cc,cm,sm,profile,neigh,levels,length,sq,data,method,opt):
    baseFolder = "%s/%s/%s/%s/%s/radius_%d" % (BASE_OUTPUT_FOLDER,shape,method,cc,profile,radius)
    outputFolder = "%s/level%d_%s" % (baseFolder,levels,"opt" if opt else "")

    return outputFolder

def boundary_correction(c):

    outputFolder = resolve_output_folder(*c)
    shape,radius,iterations,cc,cm,sm,profile,neigh,levels,length,sq,data,method,opt = c

    #print("output folder:",outputFolder)
    # print("shape:",shape)
    # print("radius:",radius)
    # print("iterations:",iterations)
    # print("cc:",cc)
    # print("cm:",cm)
    # print("sm:",sm)
    # print("profile:",profile)
    # print("neigh:",neigh)
    # print("levels:",levels)
    # print("length:",length)
    # print("sq:",sq)
    # print("data:",data)
    # print("method:",method)
    # print("opt:",opt)

    binary = "%s/%s" % (BIN_FOLDER,"shape-flow/shape-flow")
    subprocess.call( [binary,
                      outputFolder,
                      "%s%s" % ("-S",shape),
                      "%s%d" % ("-r",radius),
                      "%s%d" % ("-i",iterations),
                      "%s%s" % ("-a",cc),
                      "%s%s" % ("-c",cm),
                      "%s%s" % ("-s",sm),
                      "%s%s" % ("-p",profile),
                      "%s%d" % ("-n",neigh),
                      "%s%d" % ("-l",levels),
                      "%s%f" % ("-q",sq),
                      "%s%f" % ("-t",data),
                      "%s%f" % ("-g",length),
                      "%s%s" % ("-m",method),
                      "%s" % ("-o" if opt else "")
                      ] )

def read_input():
    if len(sys.argv)<2:
        print("Pass it the project folder!")
        exit(1)

    global PROJECT_FOLDER,BIN_FOLDER, BASE_OUTPUT_FOLDER
    PROJECT_FOLDER=sys.argv[1]
    BIN_FOLDER="%s/%s" % (PROJECT_FOLDER,"cmake-build-debug/modules/Applications")
    BASE_OUTPUT_FOLDER="%s/%s" % (PROJECT_FOLDER,"modules/lab/exp/output")

def total_combinations():
    total=0
    combs = combinations(CONFIG_LIST)
    for c in combs:
        if valid_combination(c):
            total+=1
    return total

def main():
    read_input()
    print("Total combinations: ",total_combinations())
    for c in combinations(CONFIG_LIST):
        if valid_combination(c):
            boundary_correction(c)



if __name__=='__main__':
    main()