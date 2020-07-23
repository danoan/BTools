class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

SHAPES=["triangle","square","ellipse","flower","ball","wave","bean"]
RADIUS=[5]
LEVELS=[2,4]
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


CONFIG_LIST=[ Param("Shape","sp","shape",SHAPES,resolve_std),
              Param("Radius","radius","radius",RADIUS,resolve_int),
              Param("Levels","level","levels",LEVELS,resolve_int),
              Param("Grid Step","gs","grid_step",GRID_STEP,resolve_double),
              Param("Iterations","it","iterations",ITERATIONS,resolve_int),
            ]

