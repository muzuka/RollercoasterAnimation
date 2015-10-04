
# script to output curve control points
# Steps
#   -> get Scene
#   -> get Curve
#   -> get Control Points
#   -> open file
#   -> Write control points to file
#
#

import bpy

count = 0

obj = bpy.data.objects["NurbsCurve"]

curve = obj.data

file = open('UltimateCurve.txt', 'w')

for spline in curve.splines:
    print(type(spline))
    for point in spline.points:
        count += 1
        p = str.replace(str(point.co), '<Vector (', '')
        p = str.replace(p, ')>', '')
        p = str.replace(p, ',', '')
        file.write('f ' + p + '\n')
        print(p)

print(count)

file.close()