class AppParam:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

SHAPES=["triangle","square","ellipse","flower","ball","wave","bean"]
RADIUS=[5,7]
LEVELS=[1,2,3,4,6,7]
GRID_STEP=[0.25]
ITERATIONS=[10]

def resolve_double(prefix,d):
    return "%s_%.2f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s_%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s_%s" % (prefix,s)

def valid_combination(c):
    shape,radius,levels,gs,iterations = c
    if levels['value'] > radius['value']:
        return False

    return True


CONFIG_LIST=[ AppParam("Shape","sp","shape",SHAPES,resolve_std),
              AppParam("Radius","radius","radius",RADIUS,resolve_int),
              AppParam("Levels","level","levels",LEVELS,resolve_int),
              AppParam("Grid Step","gs","grid_step",GRID_STEP,resolve_double),
              AppParam("Iterations","it","iterations",ITERATIONS,resolve_int),
            ]

