class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

SHAPES=["triangle","square","ellipse","flower"]
METHOD=["probe","improve"]
RADIUS=[3,5,7]
LEVELS=[1,2,3,4,5,6,7]
GRID_STEP=[1.0,0.5]


def resolve_double(prefix,d):
    return "%s_%.2f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s_%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s_%s" % (prefix,s)


CONFIG_LIST=[ Param("Shape","sp","shape",SHAPES,resolve_std),
              Param("Method","mt","method",METHOD,resolve_std),
              Param("Radius","radius","radius",RADIUS,resolve_int),
              Param("Levels","level","levels",LEVELS,resolve_int),
              Param("Grid Step","gs","grid_step",GRID_STEP,resolve_double)
            ]
