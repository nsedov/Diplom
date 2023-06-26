import time
from myntl import ZZ, vec_ZZ, mat_ZZ

def read_from_file(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        matrix = mat_ZZ()
        matrix.SetDims(n, n)
        for i in range(n):
            row = list(map(int, f.readline().strip().split()))
            for j in range(n):
                matrix[i][j] = ZZ(row[j])
        vector = vec_ZZ()
        vector.SetLength(n)
        for i in range(n):
            vector[i] = ZZ(int(f.readline()))
    return matrix, vector

filename = "input.txt"
matrix, vector = read_from_file(filename)

# Create the result vectors
d = ZZ()
x = vec_ZZ()
x.SetLength(1000)

# Start the timer
start = time.time()

# Solve the system
mat_ZZ.solve(d, x, matrix, vector, 0)

# Stop the timer
end = time.time()

# Calculate the duration
duration = end - start

print(f'Time taken by solve: {duration} seconds')

# Check if the system is solvable
if d != 0:
    print('The system is solvable.')
else:
    print('The system is not solvable.')