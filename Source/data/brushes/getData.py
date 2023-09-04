from os import listdir

files = listdir(".")

images = [f for f in files if f.endswith('.png')]
data = [f for f in files if f.endswith('.dat')]

images.sort()
keys = set()

dataContents = []
for i in images:
    dataname = i[:-4] + '.dat'
    if dataname in data:
        with open(dataname) as f:
            lines = f.readlines()
            d = {}
            for line in lines:
                line = line.strip()
                if "=" in line:
                    parts = line.split("=")
                    d[parts[0]] = parts[1]
                    keys.add(parts[0])
                else:
                    d[line] = 1
                    keys.add(line)
            dataContents.append(d)
    else:
        dataContents.append({})
for key in keys:
    print(f"const std::array<int, NUM_BRUSHES> brush_{key} = {{", end="")
    for i in dataContents:
        if key in i:
            print(f"{i[key]}, ", end="")
        else:
            print(f"0, ", end="")
    print("\b\b};")