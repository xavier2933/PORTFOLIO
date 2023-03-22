#################################################################
# formAutomation.py
# Author: Xavier O'Keefe
# 
# This uses Selenium to automate my weekly time sheet for my lab.
#################################################################
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.common.by import By
from selenium.webdriver.support.select import Select
import time
import csv

class readData:
    # Set initial params for data that is not easily read from csv file
    def __init__(self):
        self.days = ["Sun", "Mon", "Tues", "Weds", "Thurs", "Fri", "Sat"]
        self.browser = webdriver.Chrome(service=Service(ChromeDriverManager().install()))
        self.endDate = "2/23"
        self.totalHoursWorkedWeek1 = 5
        self.totalHoursWorkedWeek2 = 6
        self.bigTotalWorked = 11
        self.url = "www.google.com"

    # Load the browser
    def getBrowser(self):
        self.browser.get(self.url)
        time.sleep(15)

    # Function to read the CSV file and add data into the form
    def addData(self):
        self.getBrowser()
        name = Select(self.browser.find_element(By.NAME, "realname"))
        name.select_by_visible_text("Xavier O'keefe")
        email = self.browser.find_element(By.NAME, "email")
        email.send_keys("xaok7569@colorado.edu")
        jackName = Select(self.browser.find_element(By.NAME, "Supervisor"))
        jackName.select_by_visible_text("Jack Burns")
        jackEmail = Select(self.browser.find_element(By.NAME, "recipient"))
        jackEmail.select_by_visible_text("jack.burns@colorado.edu")
        hours1 = self.browser.find_element(By.NAME, "Total_Hours_Week1")
        hours1.send_keys(str(self.totalHoursWorkedWeek1))
        hours2 = self.browser.find_element(By.NAME, "Total_Hours_Week2")
        hours2.send_keys(str(self.totalHoursWorkedWeek2))
        bigTotal = self.browser.find_element(By.NAME, "Total_Hours_for_Pay_Period")
        bigTotal.send_keys(str(self.bigTotalWorked))
        endDate = self.browser.find_element(By.NAME, "Pay_Period_End_Date")
        endDate.send_keys(str(self.endDate))

        i = 0
        j = 0
        with open('data.csv') as csvFile:
            csvReader = csv.reader(csvFile, delimiter=',')
            for row in csvReader:
                if(i < 7):
                    (date, inner, out, total) = row
                    date1 = self.browser.find_element(By.NAME, "Date_" + self.days[i] + "_Week1")
                    date1.send_keys(str(date))
                    in1 = self.browser.find_element(By.NAME, "In_" + self.days[i] + "_Week1")
                    in1.send_keys(str(inner))
                    out1 = self.browser.find_element(By.NAME, "Out_" + self.days[i] + "_Week1")
                    out1.send_keys(str(out))
                    total1 = self.browser.find_element(By.NAME, "Total_Hours_" + self.days[i] + "_Week1")
                    total1.send_keys(str(total))
                    i += 1
                else:
                    (date, inner, out, total) = row
                    date2 = self.browser.find_element(By.NAME, "Date_" + self.days[j] + "_Week2")
                    date2.send_keys(str(date))
                    in2 = self.browser.find_element(By.NAME, "In_" + self.days[j] + "_Week2")
                    in2.send_keys(str(inner))
                    out2 = self.browser.find_element(By.NAME, "Out_" + self.days[j] + "_Week2")
                    out2.send_keys(str(out))
                    total2 = self.browser.find_element(By.NAME, "Total_Hours_" + self.days[j] + "_Week2")
                    total2.send_keys(str(total))
                    j +=1          
        time.sleep(100)

    # Quits the browser
    def quitBrowser(self):
        self.browser.quit()

if __name__ == "__main__":
    read = readData()
    read.addData()
    read.quitBrowser()

