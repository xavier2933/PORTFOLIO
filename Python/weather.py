#############################################################################################
#   weather.py
#   Author: Xavier O'Keefe
#
#   Program to parse NWS API and deliver forecast in easy to read format, pretty simple
#############################################################################################

import requests
# User-Agent: (xavierokeefe.com, xaok7569@colorado.edu)

URL = "https://api.weather.gov/points/40.01422952671554,-105.27065495300589"

# Make vars for required agents and desired fields
days = 7
r = requests.get(URL).json()
griddata = r['properties']['forecastGridData']
forecast = requests.get(r['properties']['forecast']).json()
h_agent = requests.get(griddata).json()
humid_arr = []
humidity = h_agent['properties']['relativeHumidity']['values']
periods = forecast['properties']['periods']

# Get humidity values for relevant days, chose to hardcode for better user experience
for k in range(11):
    humid_arr.append(int(humidity[k]['value']))

# Print everything for desired range of days
for i in range(0, days*2, 2):
    print()
    print("##################################################################################")
    print()
    print('Forecast for ' + periods[i]['name'] + ': ')
    print(periods[i]['detailedForecast'])
    print('Forecast for ' + periods[i+1]['name'] + ': ')
    print(periods[i+1]['detailedForecast'])
    
    if i == 0:
        print("Max humidity will be " + str(max(humid_arr)) + "%")
        print("Min humidity will be " + str(min(humid_arr)) + "%")

print()
