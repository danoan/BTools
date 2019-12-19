class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

GC_OBJECT=["coala/gc-object.xml"]
METHOD=["improve"]
RADIUS=[5,9]
DATA_TERM=[0,0.1,0.5,1.0,2.0,5.0]
SQ_TERM=[0,0.5,1.0]
LENGTH_TERM=[0,0.1,0.5,1.0,2.0]
LEVELS=[1,2,3,4,5,6,7,8,9]
OPT_BAND=[1,2,3]
UNIFORM_PERIMETER=[True,False]
ITERATIONS=[20,50]


def resolve_double(prefix,d):
    return "%s_%.2f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s_%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s_%s" % (prefix,s)

def resolve_gcobject(prefix,gcobject):
    return gcobject.split("/")[0]

def valid_combination(c):
    gcobject,method,radius,dt,sq,lt,levels,optband,up,iterations = c
    if levels['value'] > radius['value']:
        return False

    if levels['value'] < radius['value']-4:
        return False

    if optband['value']*2 > radius['value']:
        return False

    return True


CONFIG_LIST=[ Param("Image","img","Image",GC_OBJECT,resolve_gcobject),
              Param("Method","mt","method",METHOD,resolve_std),
              Param("Radius","radius","radius",RADIUS,resolve_int),
              Param("Data Term","data","data-term",DATA_TERM,resolve_double),
              Param("Sqc Term","sq","sqc-term",SQ_TERM,resolve_double),
              Param("Length Term","length","length-term",LENGTH_TERM,resolve_double),
              Param("Levels","levels","levels",LEVELS,resolve_int),
              Param("Optimization Band","opt-band","opt-band",OPT_BAND,resolve_int),
              Param("Uniform Perimeter","up","uniform-perimeter",UNIFORM_PERIMETER,resolve_std),
              Param("Iterations","it","iterations",ITERATIONS,resolve_int)
            ]

