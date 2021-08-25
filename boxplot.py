import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys

df = pd.DataFrame()

dadosA = [float(line.replace('\n', ''))
          for line in open("boxplot.txt", 'r').readlines()]

df['custos'] = dadosA
df['count'] = [i for i in range(len(dadosA))]

sns.set(style="darkgrid")
sns.boxplot(y=df["custos"], color='blue')
plt.title('Média dos custos')
plt.savefig(f'graphs/f{sys.argv[1]}_box_novo.png')
# plt.show()
