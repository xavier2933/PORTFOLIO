

class gradeCalc:
    
    def __init__(self, classNumber):
        if classNumber == "8":
            print("Aircraft grader\/\/\/\/\/\/\/")
            finalScore = input("input final score: > ")
            print("Final score: ", finalScore)
            self.weights = {
                "Exam 1": (22, 71.54),
                "Exam 2": (22, 90.833),
                "In class Quizes": (5, 100),
                "Reading Quizzes": (5,90),
                "Final": (30, str(finalScore)),
                "Homework": (16, 90),
            }

        elif classNumber == "7":
            print("Orbital grader\/\/\/\/\/\/\/")
            orbitalMid = input("input orbital midterm grade: > ")
            finalGrade = input("input final grade: > ")
            self.weights = {
                "Attitude mid": (15, 91.84),
                "Attitude final": (20, 94.5),
                "Homework": (15, 96),
                "orbital mid": (15, orbitalMid),
                "orbital final": (20, finalGrade),
                "orbital hw": (15, 94)
            }

        elif classNumber == "3":
            print("electronics grader\/\/\/\/\/\/\/")
            finalGrade = input("input final grade: > ")
            self.weights = {
                "Quizzes": (5, 100),
                "Practical": (10, 100),
                "Exam1": (18.3333, 87),
                "Exam2": (18.3333, 91),
                "Peer eval": (5, 100),
                "Lab reports": (20, 95),
                "Pre lab": (5,99),
                "Final": (18.3333, finalGrade)
            }

        elif classNumber == "4":
            print("Systems Grader/\/\/\/\/\/\/\/")
            # labGrade = input("input lab grade: > ")
            examGrade = input("input exam grade: > ")
            self.weights = {
                "Labs": (42, 92.667),
                "Exams": (48, examGrade),
                "Quiz": (10, 96.833)
            }

        else:
            print("Invalid")
            exit()

    def calc(self):
        grade = 0
        for i in self.weights:
            grade += self.weights[i][0] * (float(self.weights[i][1]) * 0.01)

        print("Grade is: ", grade)


if __name__ == "__main__":
    inputStr = input("Enter last number of class code: ")
    gc = gradeCalc(inputStr)
    gc.calc()
    exit()
