import os

def create_pos_n_neg():
    for img in os.listdir('D:/trian1/neg'):
        line = 'neg' + '/' + img + '\n'
        with open('neg.txt', 'a') as f:
            f.write(line)
    for img in os.listdir('D:/trian1/pos'):
        line = 'pos' + '/' + img + ' 1 0 0 120 50\n'
        with open('pos.txt', 'a') as f:
            f.write(line)

if __name__ == '__main__':
    create_pos_n_neg()
