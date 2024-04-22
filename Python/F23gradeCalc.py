############################################################################################
"""
Final grade calculator for my fall 2023 semester
"""
############################################################################################

class gradeCalc:
    
    def __init__(self, classNumber):
        if classNumber == "1":
            print("Aerodynamics grader\/\/\/\/\/\/\/")
            exam1Score = input("input exam  1 score: > ")
            exam3Score = input("Input exam 3 socre: > ")
            finalScore = float(((float(exam3Score) + float(exam1Score) + 85)/300)*100)
            print("Final score: ", finalScore)
            self.weights = {
                "Exam 1": (15, exam1Score), # (weight, score)
                "Exam 2": (15, 85),
                "Exam 3": (15, exam3Score),
                "Final": (25, str(finalScore)),
                "Homework": (10, 100),
                "Quizzes": (10, 98),
                "Clicker": (10, 81.48)
            }

        elif classNumber == "2":
            print("Structures grader\/\/\/\/\/\/\/")
            finalGrade = input("input final grade: > ")
            self.weights = {
                "Clicker": (10, 93.81),
                "Quizzes": (10, 100),
                "Homework": (10, 103.08),
                "Exams": (20, 104),
                "Final": (50, finalGrade)
            }

        elif classNumber == "3":
            print("Thermo grader\/\/\/\/\/\/\/")
            finalGrade = input("input final grade: > ")
            self.weights = {
                "Quizzes": (20, 100),
                "Homework": (20, 93.5),
                "Exam1": (12, 78.25),
                "Exam2": (13, 88.25),
<<<<<<< HEAD
                "Exam3": (15, 69.5),
=======
                "Exam3": (15, 71.5),
>>>>>>> 1b5d4eed8db2c56c06947d20f06796bb7404a8e0
                "Final": (20, finalGrade)
            }

        elif classNumber == "4":
            print("Systems Grader/\/\/\/\/\/\/\/")
            examGrade = input("input exam grade: > ")
            examGrade = (97+94.3+69.8+float(examGrade))/4
            self.weights = {
                "Labs": (42, 95),
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
    inputStr = input("Enter last number of class code: > ")
    gc = gradeCalc(inputStr)
    gc.calc()
    exit()
