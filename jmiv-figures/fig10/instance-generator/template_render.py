from shutil import copyfile
import os
from jinja2 import Template

from config import *

tfile=open("template/report_template.html")
t=Template(tfile.read())

x = t.render(paramCollection=CONFIG_LIST)

f=open("output/report.html",'w')
f.write(x)

copyfile("template/invalid.png", "output/invalid.png")
copyfile("template/report.css", "output/report.css")
copyfile("template/report.js", "output/report.js")

