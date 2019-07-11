import os
from shutil import copyfile

from jinja2 import Template

from config import *

SCRIPT_FOLDER=os.path.dirname( os.path.realpath(__file__) )
TEMPLATE_FOLDER="%s/%s" % (SCRIPT_FOLDER,"template")
OUTPUT_FOLDER="%s/%s" % (SCRIPT_FOLDER,"output")

tfile=open( "%s/%s" % (TEMPLATE_FOLDER,"report_template.html") )
t=Template(tfile.read())

x = t.render(paramCollection=CONFIG_LIST)

f=open("%s/%s" % (OUTPUT_FOLDER,"report.html"),'w')
f.write(x)

files_to_copy=['invalid.png','report.css','report.js']
for n in files_to_copy:
    copyfile("%s/%s" % (TEMPLATE_FOLDER,n), "%s/%s" %(OUTPUT_FOLDER,n))


