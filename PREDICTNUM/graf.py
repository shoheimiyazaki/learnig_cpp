import matplotlib.pyplot as plt

with open('results.text',"r") as f:
    lines = f.readlines()
    X=[]
    Y=[]
    for line in lines:
        datas=line.split('   ')
        x=float(datas[0])
        y=float(datas[1].replace("\n",""))
        X.append(x)
        Y.append(y)
        
        #print(x,'  ',y)
    
    print(len(X))
    print(len(Y))
    plt.plot(X, Y, 'o')
    plt.show()

