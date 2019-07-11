import os
from shutil import copyfile

from jinja2 import Template

def render_template(templateName,CONFIG_LIST,outputFolder):
    SCRIPT_FOLDER=os.path.dirname( os.path.realpath(__file__) )
    TEMPLATE_FOLDER="%s/%s" % (SCRIPT_FOLDER,"template")

    tfile=open( "%s/%s/%s" % (TEMPLATE_FOLDER,templateName,"report_template.html") )
    t=Template(tfile.read())

    x = t.render(paramCollection=CONFIG_LIST)

    f=open("%s/%s" % (outputFolder,"report.html"),'w')
    f.write(x)

    files_to_copy=['invalid.png','report.css','report.js']
    for n in files_to_copy:
        copyfile("%s/%s/%s" % (TEMPLATE_FOLDER,templateName,n), "%s/%s" %(outputFolder,n))


