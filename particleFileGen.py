import solarsystem
import math


AU = 149597900 / 1000000    # Astronomical distance unit
G  = 6.67430E-20            # Gravitational constant
u = 1.32712440042E11

# Mean orbital distance 
planet_vals = {
        "Mercury"     : {"m": 1.989E30, "a": 57.91E6, "color": [219,206,202]},
    "Venus"       : {"m": 4.867E24, "a": 108.21E6, "color": [201,160,220] },
    "Earth"       : {"m": 5.97237E24, "a": 149.60E6, "color": [0,128,255] },
    "Mars"        : {"m": 6.417E23, "a": 227.92E6, "color": [250,100,100] },
    "Jupiter"     : {"m": 1.89819E27, "a": 778.57E6, "color": [200,200,100] },
    "Saturn"      : {"m": 5.6834E26, "a": 1433.53E6, "color": [180,150,100] },
    "Uranus"      : {"m": 8.6813E25, "a": 2872.46E6, "color": [0,180,200] },
    "Neptune"     : {"m": 1.02413E26, "a": 4495.06E6, "color": [180,150,200] },
    "Pluto"       : {"m": 1.303E22, "a": 5906.38E6, "color": [180,180,200] },
    "Ceres"       : {"m": 9.39300E20, "a": 2.768 * AU * 1000000, "color": [0,0,0] },
    "Chiron"      : {"m": 4.000E19, "a": 13.637 * AU * 1000000, "color": [0,0,0] },
    "Eris"        : {"m": 1.66E22, "a": 67.864 * AU * 1000000, "color": [0,0,0] }
}


dstr = input("Target date(DD/MM/YYYY, 01/01/2000 default): ")
if dstr.strip() == "":
    day = 1
    month = 1
    year = 2000
else:
    day = int(dstr.split("/")[0])
    month = int(dstr.split("/")[1])
    year = int(dstr.split("/")[2])

dstr = input("Target time(HH:MM, 00:00 default): ")
if dstr.strip() == "":
    hour = 0
    minute = 0
else:
    hour = dstr.strip().split(":")[0]
    minute = dstr.strip().split(":")[1]

outfile = input("Output file (blank for out.dat): ")
if outfile.strip() == "":
    outfile = "out.dat"


H = solarsystem.Heliocentric(year=year, month=month, day=day, hour=hour, minute=minute, view="rectangular" )


planets = H.planets()
print("Planet\t\t| X\t\t\t|Y\t\t\t| v")
with open(outfile, 'w') as fp:
    fp.write(f"YEAR={year}\nMONTH={month}\nDAY={day}\nHOUR={hour}\nMINUTE={minute}\nSECOND=0\n")
    fp.write("Sun 250 250 1.989E30 0 0 1 255 255 0\n")
    for p in planets:
        print("{:<7}".format(p) +": " , end="\t")
        print( planets[p][0] * AU, end="\t")
        print( planets[p][1] * AU, end="\t")
       
        r = math.sqrt( pow(planets[p][0]*AU,2) + pow(planets[p][1]*AU,2)) * 1000000
        #print("r = " + str(r), end="\t")
        velocity = math.sqrt(u * ((2/r) - (1/planet_vals[p]["a"]))) / 100 # KM
        print( velocity, end="\t")
        x = planets[p][0]
        y = planets[p][1]
        angle = math.atan2(0,0) - math.atan2(y,x)
        print("angle= " + str(angle), end="\n")
        yvel = math.cos(angle) * velocity / 10000
        xvel = math.sin(angle) * velocity / 10000
        fp.write(f"{p} {planets[p][0]*AU + 250} {planets[p][1]*AU + 250} {planet_vals[p]['m']} {xvel} {yvel} 1 {planet_vals[p]['color'][0]} {planet_vals[p]['color'][1]} {planet_vals[p]['color'][2]} 0.5 50 50 50\n") # Name, X, Y, Mass, XVEL, YVEL, Radius, R, G, B, TrailRadius, trailRed, trailGreen, trailBlue


