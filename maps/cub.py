def generate_large_map(filename, width=100, height=100):
    with open(filename, 'w') as f:
        for y in range(height):
            line = ""
            for x in range(width):
                if y == 0 or y == height - 1 or x == 0 or x == width - 1:
                    line += "1"
                elif x == width // 2 and y == height // 2:
                    line += "N"
                else:
                    line += "0"
            f.write(line + "\n")

generate_large_map("large_map.cub")
