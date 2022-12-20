"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150427834
Name:       Salli Valkama
Email:      salli.valkama@tuni.fi

13.7 Painoindeksilaskuri

Program that calculates users body mass index value.
"""

from tkinter import *


class Userinterface:
    """
    User interface for program that calculates users bio mass index. With given
    wight and height the program calculates BMI value and gives an explanation
    about the result.
    """

    def __init__(self):
        """
        Constructor. UI is initiated with two entries, one for users
        weight (kg) and one for height (cm). Labels instruct the user about
        the inputs. After filling the entries the user uses the calculation
        button to start the BMI calculation. The results are shown in two
        other labels: the BMI value and the explanation text. The user can
        exit the program by stop button.
        """

        self.__mainwindow = Tk()

        # Entries and labels for users weight and height
        self.__weight_text = Label(self.__mainwindow, text="Enter your weight (kg):", borderwidth=2)
        self.__weight_value = Entry(self.__mainwindow, borderwidth=2)

        self.__height_text = Label(self.__mainwindow, text="Enter your height (cm):", borderwidth=2)
        self.__height_value = Entry(self.__mainwindow, borderwidth=2)


        # Button for calculation
        self.__calculate_button = Button(self.__mainwindow, text="Calculate your BMI", background="green",
                                         relief=GROOVE, borderwidth=2, command=self.calculate_BMI,)

        # Labels for the result
        self.__result_label = Label(self.__mainwindow, text="Your BMI:")
        self.__result_text = Label(self.__mainwindow, text=(None), borderwidth=2, relief=GROOVE)

        self.__explanation_label = Label(self.__mainwindow, text="Explanation:")
        self.__explanation_text = Label(self.__mainwindow, text=(None), borderwidth=2, relief=GROOVE)

        # Button for quitting the program
        self.__stop_button = Button(self.__mainwindow, text="Stop", command=self.stop, borderwidth=2, relief=GROOVE)


        # Placing the components in the GUI
        self.__weight_text.grid(row=0, column=0)
        self.__weight_value.grid(row=0, column=1)
        self.__height_text.grid(row=1, column=0)
        self.__height_value.grid(row=1, column=1)
        self.__calculate_button.grid(row=2, column=0)
        self.__result_label.grid(row=3, column=0, sticky=W+E)
        self.__result_text.grid(row=4, column=0, columnspan=3)
        self.__explanation_label.grid(row=5, column=0)
        self.__explanation_text.grid(row=6, column=0, columnspan=4)
        self.__stop_button.grid(row=7, column=0)


    def calculate_BMI(self):
        """
        This method calculates the BMI of the user and
        displays it. First the method will get the values of
        height and weight from the GUI components
        self.__height_value and self.__weight_value.  Then the
        method will calculate the value of the BMI and show it in
        the element self.__result_text.

        Last, the method will display a verbal
        description of the BMI in the element
        self.__explanation_text.
        """

        try:
            users_weight = int(self.__weight_value.get())
            users_height = int(self.__height_value.get())

        except ValueError:
            self.__explanation_text.configure(text="Error: height and weight must be numbers.")
            self.reset_fields()
            return

        if users_weight <= 0 or users_height <= 0:
            self.__explanation_text.configure(text="Error: height and weight must be positive.")
            self.reset_fields()
            return

        users_height = users_height / 100
        users_BMI = users_weight / (users_height * users_height)
        self.__result_text.configure(text=round(users_BMI, 2))

        if users_BMI > 25.00:
            self.__explanation_text.configure(
                text="You are overweight.")
        if users_BMI < 18.50:
            self.__explanation_text.configure(
                text="You are underweight.")
        if users_BMI < 25.00 and users_BMI > 18.50:
            self.__explanation_text.configure(
                text="Your weight is normal.")


    def reset_fields(self):
        """
        In error situations this method will zeroize the elements
        self.__result_text, self.__height_value, and self.__weight_value.
        """
        self.__result_text.configure(text=None)
        self.__height_value.delete(0, END)
        self.__weight_value.delete(0, END)


    def stop(self):
        """
        Ends the execution of the program.
        """

        self.__mainwindow.destroy()


    def start(self):
        """
        Starts the mainloop.
        """
        self.__mainwindow.mainloop()


def main():
    # Notice how the user interface can be created and
    # started separately.  Don't change this arrangement,
    # or automatic tests will fail.
    ui = Userinterface()
    ui.start()


if __name__ == "__main__":
    main()
