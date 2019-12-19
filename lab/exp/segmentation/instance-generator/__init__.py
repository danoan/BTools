import sys,os

SCRIPT_FOLDER = os.path.dirname( os.path.realpath(__file__) )
BTOOLS_FOLDER = SCRIPT_FOLDER
for i in range(4):
    BTOOLS_FOLDER = os.path.dirname(BTOOLS_FOLDER)

REPORT_GENERATOR_FOLDER="%s/%s" % (BTOOLS_FOLDER,"repGen")
print("Including directory: %s in Python search path" % (REPORT_GENERATOR_FOLDER,))
sys.path.append(REPORT_GENERATOR_FOLDER)