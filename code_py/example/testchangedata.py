import numpy as np
 
#load data
file=open("D:\data.txt")
lines=file.readlines()
rows=len(lines)
 
datamat = np.zeros((rows,15))
 
row=0
for line in lines:
    line=line.strip().split('\t')
    datamat[row,:]=line[::]
    row+=1
 
print(datamat)
print(datamat.shape) 