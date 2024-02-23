# Program to generate cleaned country info for the world map.
import csv

newCountriesLines = []
newBordersLines = []

with open('countries.csv') as csvFile:
    next(csvFile)
    reader = csv.reader(csvFile)

    newCountriesLines.append('name,alpha2,number')

    for row in reader:
        countryName = row[0]
        countryAlpha2 = row[1]
        countryCode = str(int(row[3]))
        s = f'{countryName},{countryAlpha2},{countryCode}'
        newCountriesLines.append(s)

with open('borders.csv') as csvFile:
    next(csvFile)
    reader = csv.reader(csvFile)

    newBordersLines.append('code,bordercode')

    for row in reader:
        countryCode = row[0]
        borderCode = row[2]
        newBordersLines.append(f'{countryCode},{borderCode}')

with open('clean-countries.csv', 'w') as csvFile:
    for row in newCountriesLines:
        csvFile.write(row + '\n')

with open('clean-borders.csv', 'w') as csvFile:
    for row in newBordersLines:
        csvFile.write(row + '\n')