############### FINAL GRADE CALCULATOR ##################
#Made for fun 
#I used a class here just to get more practice with them, 
#definitely not neccessary
#########################################################

class Vars:
    def __init__(self, prompt):
        self.prompt = prompt

#take in user input, call appropriate function, return if invalid input
    def get_inputs(self):
        print(
            """
            Welcome to grade calculator!
            I hope this program brings you joy rather than tears.
            What would you like to do today?
            1: Calculate the required score on a test for a certain letter grade
            2: Find out what you got in the class
            3: FOR MATERIAL SCIENCE ONLY
            Enter the number that you would like to execute
            """)
        choice = float(input(self.prompt))

        if choice == 1:
            self.req_score()
            

        if choice == 2:
            self.find_grade()
            
        if choice == 3:
            self.matsci()

        else:
            print("Invalid input! try again")
            self.get_inputs()

#Print score neccesary for given grade, check for edge cases
    def req_score(self):
        print("How much is the final worth? (in %)")
        worth = float(input(self.prompt))/100
        if 0 > worth or worth >= 1:
            print("You entered a score that was out-of-bounds. Please try again")
            self.req_score()
        print("What grade do you want in the class?")
        want = float(input(self.prompt))
        if 0 > want:
            print("You entered a score that was out-of-bounds. Please try again")
            self.req_score()
        print("What is your current grade?")
        current = float(input(self.prompt))
        final = (want - current*(1-worth))/worth
        print(f"You need at least a {final} to get a {want}% in the class") 
        exit()

#Print grade based on performance on final, check for edge cases
    def find_grade(self):
        print("How much is the final worth? (in %)")
        worth = float(input(self.prompt))/100
        if 0 > worth or worth >= 1:
            print("You entered a score that was out-of-bounds. Please try again")
            self.find_grade()
        print("What did you get on the final?")
        want = float(input(self.prompt))
        if 0 > want:
            print("You entered a score that was out-of-bounds. Please try again")
            self.find_grade()
        print("What is your current grade?")
        current = float(input(self.prompt))
        final = current*(1-worth) + worth*want
        print(f"You got a {final} in the class!") 
        exit()
   
#This was the original function, I made this for one specific class to calculate grade b/c canvas was locked
    def matsci(self):
        prompt = self.prompt
        print("Input your quiz 1 score")
        quiz1 = float(input(prompt))
        print("Input your quiz 2 score")
        quiz2 = float(input(prompt))
        print("Input your quiz 3 score")
        quiz3 = float(input(prompt))
        print("Input your quiz 4 score")
        quiz4 = float(input(prompt))
        print("Input your quiz 5 score")
        quiz5 = float(input(prompt))
        print("Input your quiz 6 score")
        quiz6 = float(input(prompt))
        print("Enter your homework average")
        hw = float(input(prompt))

        grade = (((quiz1 + quiz2 + quiz3 + quiz4 + quiz5 + quiz6)/6) * 0.84) + (hw * .16)
        print(f"Final grade is {grade}.")

#call functions
init = Vars('< ')
init.get_inputs()


