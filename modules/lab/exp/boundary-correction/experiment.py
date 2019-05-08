#!/use/bin/python3
import subprocess,sys,os,time

PROJECT_FOLDER="set in read input"
BINARY_FOLDER="set in read  input"
INPUT_FOLDER="set in read input"

GC_OBJECT=["butterfly/gc-object.xml","cow/gc-object.xml","giraffe/gc-object.xml","honeybee/gc-object.xml"]
RADIUS=[3]
ITERATIONS=[10,20,50,100]
SQ_TERM=[1.0]
DATA_TERM=[0,0.1,0.5,1.0,2.0,5.0]
LENGTH_TERM=[0,0.5,1.0,2.0]
METHOD=["improve"]

CONFIG_LIST=[ (GC_OBJECT,"gc_object"), (RADIUS,"radius"), (ITERATIONS,"iterations"),
			  (SQ_TERM,"sq_term"), (DATA_TERM,"data_term"), (LENGTH_TERM,"length"), (METHOD,"method") ]

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

def resolve_gcobject(c):
	gcobject,radius,iterations,sq,dt,lt,method = c
	return "%s/%s" % (INPUT_FOLDER,gcobject)

def resolve_output_folder(c):
	gcobject,radius,iterations,sq,dt,lt,method = c
	image_name = gcobject.split("/")[0]
	output_folder = "%s/%s/%s/%s/radius_%d/data_%.2f/sq_%.2f/lt_%.2f/it_%d" % (PROJECT_FOLDER,
																			"modules/lab/exp/boundary-correction/output",
																			image_name,
																			method,
																			radius,
																			dt,
																			sq,
																			lt,
																			iterations)
	return output_folder

def boundary_correction(c):
	gcobject,radius,iterations,sq,dt,lt,method = c

	outputFolder=resolve_output_folder(c)

	print("Running experiment: ",*c)

	tstart = time.time()
	binary = "%s/%s" % (BINARY_FOLDER,"boundary-correction-app")
	subprocess.call( [binary,
			  resolve_gcobject(c),
			  "%s%d" % ("-r",radius),
			  "%s%d" % ("-i",iterations),
			  "%s%f" % ("-q",sq),
			  "%s%f" % ("-t",dt),
			  "%s%f" % ("-g",lt),
			  "%s%s" % ("-m",method),
			  "%s%s" % ("-o",outputFolder)])
	tend=time.time()

	print("*****Done in: %f seconds" % (tend-tstart,))

def export_seed_mask(c):
	gcobject,radius,iterations,sq,dt,lt,method = c

	outputFolder=resolve_output_folder(c)

	binary = "%s/%s" % (BINARY_FOLDER,"export-seed-mask")
	subprocess.call( [binary,
					  resolve_gcobject(c),
					  "%s/%s" % (outputFolder,"seeds.png")])


def read_input():
	if len(sys.argv)<2:
		print("Parameters missing! PROJECT_FOLDER")
		exit(1)

	global PROJECT_FOLDER,BINARY_FOLDER,INPUT_FOLDER

	PROJECT_FOLDER=sys.argv[1]
	BINARY_FOLDER="%s/%s" % (PROJECT_FOLDER,"export/bin")
	INPUT_FOLDER="%s/%s" % (PROJECT_FOLDER,"modules/lab/exp/boundary-correction/input")

def main():
	read_input()
	for c in combinations(CONFIG_LIST):
		boundary_correction(c)
		export_seed_mask(c)


if __name__=='__main__':
	main()



