import pandas as pd
import matplotlib.pyplot as plt
import sys


linhas = [linha for linha in open(
    'convergencia.txt', 'r').readlines()]
temp = []
cost = []
for i in linhas:
    a = i.split(',')
    temp.append(int(a[0]))
    cost.append(float(a[1]))

df = pd.DataFrame()
df['temp'] = temp
df['cost'] = cost

plt.plot('temp', 'cost', data=df, color='blue')
# plt.gca().invert_xaxis()
plt.xlabel('Iterações')
plt.ylabel('Custo')
plt.title(
    'Cf = {}'.format(round(df['cost'].min(), 2)))
# plt.savefig('est{}-grafico{}'.format(sys.argv[2], sys.argv[1]))
plt.savefig('est-grafico.png')
