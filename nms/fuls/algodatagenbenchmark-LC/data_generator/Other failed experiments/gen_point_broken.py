import shapefile
from shapely.geometry import Point, shape
from numpy.random import uniform
from collections import Counter 

# https://stackoverflow.com/questions/47692726/lightweight-tool-for-generating-random-coordinates-for-specific-region-country
shp = shapefile.Reader('shapefiles/TM_WORLD_BORDERS-0.3.shp', encoding='windows-1252')
# Adjust for your case:
EU3 = ['ARM', 'BIH', 'BIH', 'CYP', 'DNK', 'IRL', 'AUT', 'EST', 'CZE', 'FIN' 
      , 'FRA', 'DEU', 'GRC', 'HRV', 'HUN', 'ISL', 'ITA', 'LTU', 'LVA', 'BLR'
      , 'MLT', 'BEL', 'AND', 'GIB', 'LUX', 'MCO', 'NLD', 'NOR', 'POL', 'PRT'
      , 'ROU', 'MDA', 'ESP', 'CHE', 'GBR', 'SRB', 'SWE', 'ALB', 'MKD', 'MNE'
      , 'SVK', 'SVN'] # 'TUR'
EU = [(boundary, record) for boundary, record in 
             zip(shp.shapes(), shp.records()) if record[2] in EU3]

# Adjust the borders 
count = Counter()  # small optimisation to check for big shapes first
def sample(shapes, min_x=-11, max_x=26, min_y=37, max_y=71):
    while True:
        point = (uniform(min_x, max_x), uniform(min_y, max_y)) 
        for boundary, record in sorted(shapes, key=lambda x: -count[x[1][2]]):
            if Point(point).within(shape(boundary)): 
                count[record[2]] += 1
                return point


print(sample(EU3))