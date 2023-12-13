from googleplaces import GooglePlaces, types, lang
from geopy.geocoders import Nominatim
import requests
import json
import random
  
class food:
    def __init__(self, key):
        self.API_KEY = key

    def getparams(self):
        print("""
            Welcome to random food generator! Please follow instructions to 
            pick a place to eat dinner.
        """)
        self.address = input("Input your current address: ")
        print()
        distance_raw = input("How far will you drive (in miles): ")
        self.distance_meters = 1609.34 * float(distance_raw)
        print()
        
    def placesearch(self):
        google_places = GooglePlaces(self.API_KEY)
        url = "https://maps.googleapis.com/maps/api/place/textsearch/json?"
        r = requests.get(url + 'query=' + self.address +
                        '&key=' + self.API_KEY).json()  

        lat = r['results'][0]['geometry']['location']['lat']
        lon = r['results'][0]['geometry']['location']['lng']

        

        self.query_result = google_places.nearby_search(
            lat_lng ={'lat': lat, 'lng': lon},
            radius = self.distance_meters,
            types =[types.TYPE_RESTAURANT])

        if len(self.query_result.places) == 0:
            print("No places found near you! Try increasing your range")
            self.run()
        else:
            # print("Here is your dinner location: ")
            index = random.randint(0, len(self.query_result.places)-1)
            # print(self.query_result.places[index].name)
            self.query_result.places.pop(index)
            print("Here is your dinner location: " + self.query_result.places[index].name)
            print()
            self.rejection()

    def rejection(self):
        print("""
            If you are unsatisfied with this location, press 2 and hit enter.
            Otherwise press 1 to exit.
        """)
        choice = input('> ')
        while choice:
            try:
                val = int(choice)
                if int(choice) == 1:
                    print()
                    print("Exiting . . .")
                    print()
                    exit()
                elif int(choice) == 2:
                    if len(self.query_result.places) > 0:
                        self.retry()
                    else:
                        print("Out of new places! Trying again . . . ")
                        self.placesearch()
                break
                

            except ValueError:
                print("Please enter either 1 or 2.")
                choice = input('> ')

        
    def retry(self):
        print()
        # print("New dinner location: ")
        index = random.randint(0, len(self.query_result.places)-1)
        print("New dinner location: " + self.query_result.places[index].name)  
        self.query_result.places.pop(index)
        self.rejection()

    def run(self):
        self.getparams()
        self.placesearch()

init = food('////// REDACTED \\\\\\')  
init.run()
     
  

  
