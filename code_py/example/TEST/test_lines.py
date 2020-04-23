import threading as td
from time import *
from datetime import datetime 
tickets = [['2018.8.1'],['2018.8.2'],['2018.8.3']]
  


#cpython  /Jython IronPython PyPy DO LINES
def buy_ticket(num):
    print("tick",tickets[num])
    return 0




if __name__=='__main__':
    t1 = td.Thread(target=buy_ticket(0))
    t2 = td.Thread(target=buy_ticket(1))
    t3 = td.Thread(target=buy_ticket(2))
    t1.start()
    t2.start()
    t3.start()
    t1.join()
    t2.join()
    t3.join()




