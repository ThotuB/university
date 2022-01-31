import math
import plotly.express as px

n = 100000

xs = []
ys = []
for k in range(1, 2000):
    prob = 1 - math.exp(-0.5 * k * (k - 1) / n)
    
    xs += [k]
    ys += [prob]
    
fig = px.line(x=xs, y=ys)
fig.show()