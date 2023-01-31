import requests
# User-Agent: (xavierokeefe.com, xaok7569@colorado.edu)

URL = "https://api.weather.gov/points/40.01422952671554,-105.27065495300589"

r = requests.get(URL).json()

temp = r['properties']['forecast']
griddata = r['properties']['forecastGridData']
r2 = requests.get(temp).json()
h_agent = requests.get(griddata).json()
humid_arr = []
humidity = h_agent['properties']['relativeHumidity']['values']
print(humidity[11]['value'])
temp2 = r2['properties']['periods']
for k in range(11):
    humid_arr.append(int(humidity[k]['value']))

for i in range(0, 14, 2):
    print("##################################################################################")
    print('Forecast for ' + temp2[i]['name'] + ': ')
    print(temp2[i]['detailedForecast'])
    print('Forecast for ' + temp2[i+1]['name'] + ': ')
    print(temp2[i+1]['detailedForecast'])
    
    if i == 0:
        print("Max humidity will be " + str(max(humid_arr)) + "%")
        print("Min humidity will be " + str(min(humid_arr)) + "%")
    # print("##################################################################################")
