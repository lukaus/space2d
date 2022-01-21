# Script to scale distances of particle file
# Luke Stanley 2020

scale = input("Scaling factor: ")
scale = int(scale.strip())
filename = input("Path to file: ")
outfile = input("Path to which to save: ")

with open(filename, "r") as of:
    sf = open(outfile, "w")
    for line in of:
        line = line.strip().split(" ")
        count = 0

        if len(line) > 1:
            for field in line:
                field = field.strip()
                
                print(field, end=" ")
                if count == 1 or count == 2: 
                    field = float(field) * scale
                    
                elif count == 4 or count == 5:
                    field = float(field) * scale
                elif count == 6:
                    field = scale
                elif count == 10:
                    field = scale / 2

                sf.write(str(field) + " ")
                count += 1
        else:
            sf.write(" ".join(line))
        sf.write("\n")

    sf.close()
