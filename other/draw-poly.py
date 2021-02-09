import matplotlib.path as mpath
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

def read_polygon():
	xs = []
	ys = []
	n = int(input())
	for i in range(n):
		x, y = (float(i) for i in input().split())
		xs.append(x)
		ys.append(y)
	return list(zip(xs, ys))


ax = plt.subplot()
def draw_poly(vertices, line_style = 'go-'):
	global ax
	if len(vertices) < 1:
		return
	path_data = [ (mpath.Path.MOVETO, vertices[0])]
	for i in vertices[1:]:
		path_data.append( (mpath.Path.LINETO, i))
	path_data.append((mpath.Path.CLOSEPOLY, vertices[0]))
	codes, verts = list(zip(*path_data))
	path = mpath.Path(verts, codes)
	x, y = list(zip(*path.vertices))
	line, = ax.plot(x, y, line_style)

poly = read_polygon()
draw_poly(poly)

ax.grid()
ax.axis('equal')
plt.show()

