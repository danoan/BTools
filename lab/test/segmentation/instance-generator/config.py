class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

GC_OBJECT=["coala/gc-object.xml"]
RADIUS=[7]
DATA_TERM=[0,0.5]
SQ_TERM=[0,0.5]
LENGTH_TERM=[0,0.5]
LEVELS=[1,2,3,4,5,6,7]
ITERATIONS=[10]


def resolve_double(prefix,d):
    return "%s_%.2f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s_%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s_%s" % (prefix,s)

def resolve_gcobject(prefix,gcobject):
    return gcobject.split("/")[0]

def valid_combination(c):
    gcobject,radius,dt,sq,lt,levels,iterations = c
    if levels['value'] > radius['value']:
        return False

    return True


CONFIG_LIST=[ Param("Image","img","Image",GC_OBJECT,resolve_gcobject),
              Param("Radius","radius","radius",RADIUS,resolve_int),
              Param("Data Term","data","data-term",DATA_TERM,resolve_double),
              Param("Sqc Term","sq","sqc-term",SQ_TERM,resolve_double),
              Param("Length Term","length","length-term",LENGTH_TERM,resolve_double),
              Param("Levels","levels","levels",LEVELS,resolve_int),
              Param("Iterations","it","iterations",ITERATIONS,resolve_int)
            ]

