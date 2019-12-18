# -*- coding: utf-8 -*-
"""
Created on Wed Jan 24 10:43:25 2018

@author: ernest
"""
import random

def afegeixSinonim(diccionari, paraula, sinonim):
    if paraula not in diccionari.keys():
        diccionari[paraula] = [sinonim]
    
    else:
        if sinonim not in diccionari[paraula]:
            diccionari[paraula].append(sinonim)



def conversioSinonims(frase, diccionari):
    fraseToRet = []

    for word in frase:
        if word in diccionari.keys():
            if len(diccionari[word]) == 1:
                fraseToRet.append(diccionari[word][0])
                
            else:
                fraseToRet.append(diccionari[word][1])
        else:
            fraseToRet.append(word)
    
    return fraseToRet

    
