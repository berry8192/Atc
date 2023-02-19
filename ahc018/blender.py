import bpy
import bmesh
file_path = 'C:\\Users\\berry\\Downloads\\6bada50282\\tools\\onlys\\0009.txt'
with open(file_path) as f:
    data = f.read().split()

# Convert data to list of integers
data = [int(d)/1000 for d in data]
# Create grid object
bpy.ops.object.mode_set(mode='OBJECT')
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.mesh.primitive_grid_add(x_subdivisions=199, y_subdivisions=199, size=20)
# Wait for grid object to be fully created
bpy.context.view_layer.update()
# Apply height values to vertices
mesh = bpy.context.object.data
for i, vert in enumerate(mesh.vertices):
    x = i % 200
    y = i // 200
    vert.co.z = data[y * 200 + x]

