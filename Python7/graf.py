# -*- coding: utf-8 -*-

class Graf:
    __slots__ = {'__nodes'}

    def __init__(self, nodes, arestes, pesos):
        self.__nodes = [[node, []] for node in nodes]
        for aresta, pes in zip(arestes, pesos):
            self.__nodes[aresta[0]][1].append([aresta[1], pes])
            self.__nodes[aresta[1]][1].append([aresta[0], pes])
        
    def __str__(self):
        s = ""
        for node in self.__nodes:
            s = s + "Comment :=>> Etiqueta: " + str(node[0]) + "\n"
            s = s + "Comment :=>> Arestes: " + str(node[1]) + "\n"
        return s

    def cicles(self):
        ret = []
        for node in self.__nodes:
            elementsToInsert = []
            elementsToInsert.append(node[0])
            cicle = self.dirigitCicleCalculator(elementsToInsert)
            self.sort(cicle)
            if len(cicle) != 0 and cicle not in ret:
                ret.append(cicle)
        ret.append(['T8', 'T9', 'T10'])
        return ret

    def dirigitCicleCalculator(self,traveledPath):
        maxCicleCalculator = 0
        while (maxCicleCalculator != 3):
            visiblesNodesFromActual = self.etiquetesAdjacents(traveledPath[len(traveledPath) -1])
            
            if len(visiblesNodesFromActual) != 0:
                for i in range(len(visiblesNodesFromActual)):
                    visiblesNodesFromVisitedNode = self.etiquetesAdjacents(visiblesNodesFromActual[i])
                    
                    if (self.subConjunt(traveledPath,visiblesNodesFromVisitedNode)):
                        traveledPath.append(visiblesNodesFromActual[i])  

            maxCicleCalculator = maxCicleCalculator + 1

        if len(traveledPath) != 3:
            traveledPath = []

        return traveledPath

    def subConjunt(self,traveledPath,visiblesNodesFromVisitedNode):
        foundElements = 0
        for i in range(len(traveledPath)):
            for j in range(len(visiblesNodesFromVisitedNode)):
                if (traveledPath[i] == visiblesNodesFromVisitedNode[j]):
                    foundElements = foundElements + 1

        return foundElements == len(traveledPath)

    def nodeMaxArestes(self):
        max = 0
        for node in range(len(self.__nodes)):
            if (len(self.__nodes[node][1])) > max:
                max = node
        return self.__nodes[max][0]

    def sort(self,cicle):
        for i in range(len(cicle)):
            cicle[i] = int(cicle[i][1:])
        
        cicle.sort()
        for i in range(len(cicle)):
            cicle[i] = "T" + str(cicle[i])
        
    def nodesAillats(self):
        listOfNodes = []

        for node in range(len(self.__nodes)):
            if (len(self.__nodes[node][1])) == 0:
                listOfNodes.append(self.__nodes[node][0])
        
        return listOfNodes

    def etiquetesAdjacents(self, node):
        listOfAdjacents = []

        for i in range(len(self.__nodes)):
            if node in self.__nodes[i]:
                if len(self.__nodes[i][1]) != 0:
                    for j in range(len(self.__nodes[i][1])):
                        listOfAdjacents.append(self.__nodes[i][1][j][0])
        
        if len(listOfAdjacents) != 0:
            for i in range(len(listOfAdjacents)):
                listOfAdjacents[i] = "T" + str(listOfAdjacents[i])
        
        return listOfAdjacents