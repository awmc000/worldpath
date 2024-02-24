# Program to generate C code for the world map.

import csv

from signal import signal, SIGPIPE, SIG_DFL  
signal(SIGPIPE,SIG_DFL) 

nameStrings = []
alpha2Strings = []
alpha2ToNameInserts = []
nameToAlpha2Inserts = []
vertices = []
pointers = []
alpha2ToNumeric = []
edges = []
nameFrees = []
alpha2Frees = []

# TODO: Generate string variables made with strdup and deleted with free for full names and 2-letter codes!
# Form: ALPHA2_name, ALPHA2_alpha2
# Eg.: CA_name = strdup("Canada"); CA_alpha2 = strdup("CA");

# For each country C...
with open('clean-countries.csv') as csvFile:
	next(csvFile)
	csvReader = csv.reader(csvFile)
	
	# name,alpha2,number
	for row in csvReader:
		countryName = row[0]
		countryAlpha2 = row[1]
		countryCode = str(int(row[2]))
		# Add a string with the country's name
		nameString = f'char * {countryAlpha2}_name = strdup("{countryName}");'
		nameStrings.append(nameString)

		nameFree = f'free({countryAlpha2}_name);'
		nameFrees.append(nameFree)

		# Add a string with the country's alpha2
		alpha2String = f'char * {countryAlpha2}_alpha2 = strdup("{countryAlpha2}");'
		alpha2Strings.append(alpha2String)

		alpha2Free = f'free({countryAlpha2}_alpha2);'
		alpha2Frees.append(alpha2Free)

		# Add the country's name and ISO3 code to the code->name mapping
		alpha2ToNameInserts.append(f'dictionary_insert(alpha2_to_name, {countryAlpha2}_alpha2, {countryAlpha2}_name);')
		nameToAlpha2Inserts.append(f'dictionary_insert(name_to_alpha2, {countryAlpha2}_name, {countryAlpha2}_alpha2));')
		# Add the country as a vertex
		vertices.append(f'struct Vertex * country_{countryAlpha2} = construct_vertex({countryCode}, "{countryAlpha2}");')
		pointers.append(f'countryVertices[{countryCode}] = country_{countryAlpha2};')
		alpha2ToNumeric.append(f'dictionary_insert(alpha2_to_numeric, "{countryAlpha2}", "{countryCode}");')

# code,bordercode
with open('clean-borders.csv') as csvFile:
	next(csvFile)
	csvReader = csv.reader(csvFile)

	for row in csvReader:
		firstAlpha2 = row[0]
		secondAlpha2 = row[1]
		if len(secondAlpha2) > 1:
			edges.append(f'add_edge(country_{firstAlpha2}, country_{secondAlpha2});')

print(*nameStrings, sep = '\n')
print(*alpha2Strings, sep = '\n')
print(*alpha2ToNameInserts, sep='\n')
print(*nameToAlpha2Inserts, sep='\n')
print(*vertices, sep='\n')
print(*pointers, sep='\n')
print(*alpha2ToNumeric, sep='\n')
print(*edges, sep='\n')
print(*nameFrees, sep='\n')
print(*alpha2Frees, sep='\n')

