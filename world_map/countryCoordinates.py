import sys
import re

def main():
    countries_scraped = 0
    
    # Pattern for finding all country info
    country_info_pattern = re.compile(r'class=\"([a-z ]+)\" d=\"m ([0-9]{1,4}.[0-9]{1,4}),([0-9]{1,5}.[0-9]{1,5})')
    
    # Pattern for finding 2-letter code Eg. US for United States, CA for Canada.
    iso2_pattern = re.compile("[a-z]{2}$")
    
    #List of lines
    lines = []
    
    for i, line in enumerate(open('World Map.svg')):
        for match in re.finditer(country_info_pattern, line):    
            iso2 = iso2_pattern.search(match.group(1)).group(0)
            this_line = f'{iso2},{match.group(2)},{match.group(3)}\n'
            lines.append(this_line)
            countries_scraped += 1
    
    print(f'Scraped {countries_scraped} countries')

    with open('countrypositions.csv', 'w', newline='') as csvfile:
        for line in lines:
            csvfile.write(line)
            
    return 0
    
if __name__ == "__main__":
    sys.exit(main())