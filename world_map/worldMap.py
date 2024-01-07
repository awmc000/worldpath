# Program to generate C code for the world map.

import csv
from countryinfo import CountryInfo

alpha2ToNameInserts = []
nameToAlpha2Inserts = []
vertices = []
pointers = []
alpha2ToNumeric = []
edges = []


# For each country C...
with open('countries.csv') as csvFile:
	next(csvFile)
	csvReader = csv.reader(csvFile)
	
	
	for row in csvReader:
		countryName = row[0]
		countryAlpha2 = row[1]
		countryAlpha3 = row[2]
		countryCode = str(int(row[3]))
		# Add the country's name and ISO3 code to the code->name mapping
		alpha2ToNameInserts.append(f'dictionary_insert(alpha2_to_name, strdup("{countryAlpha2}"), strdup("{countryName}"));')
		nameToAlpha2Inserts.append(f'dictionary_insert(name_to_alpha2, strdup("{countryName}"), strdup("{countryAlpha2}"));')
		country = CountryInfo(countryName)
		# Add the country as a vertex
		vertices.append(f'struct Vertex * country_{countryAlpha2} = construct_vertex({countryCode}, "{countryAlpha2}");')
		pointers.append(f'countryVertices[{countryCode}] = country_{countryAlpha2};')
		alpha2ToNumeric.append(f'dictionary_insert(alpha2_to_numeric, "{countryAlpha2}", "{countryCode}");')

with open('borders.csv') as csvFile:
	next(csvFile)
	csvReader = csv.reader(csvFile)

	for row in csvReader:
		firstAlpha2 = row[0]
		secondAlpha2 = row[2]
		if len(secondAlpha2) > 1:
			edges.append(f'add_edge(country_{firstAlpha2}, country_{secondAlpha2});')


print(*alpha2ToNameInserts, sep='\n')
print(*nameToAlpha2Inserts, sep='\n')
print(*vertices, sep='\n')
print(*pointers, sep='\n')
print(*alpha2ToNumeric, sep='\n')
print(*edges, sep='\n')

