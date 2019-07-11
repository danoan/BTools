#!/use/bin/python3

def recCombinations(maxList,curr,combList):

    if len(maxList)==0:
        combList.append(curr)
        return

    for el in range(0,maxList[0]):
        recCombinations(maxList[1:],curr+[el],combList)

def combinations(configList):
    numParams = len(configList)
    maxList = [ len(param.items) for param in configList ]

    combList=[]
    recCombinations(maxList,[],combList)

    for c in combList:
        yield tuple( configList[i].items[c[i]] for i in range(numParams) )



