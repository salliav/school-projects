"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150427834
Name:       Salli Valkama
Email:      salli.valkama@tuni.fi

Program for calculating the amount of stitches for a new knitwork.
"""


from tkinter import *

class User_interface():
    """
    A User interface for a program that calculates the amount of stitches for
    a new knitwork. The user gives the size (cm) of a knitwork and selects the
    name of a yarn he/she is about to use for that work. Options are stored
    in a library (a dictionary of yarn names and knitting tensions) and
    displayed in a menu. The program calculates the amount of stitches needed
    for users knitwork by using the inputs.

    The user may also add new data for the yarn library. The user gives
    the name and the knitting tension of a new yarn and the program stores it
    into the dictionary and displays it in the options of the yarn menu.
    The program is quite simple, because it is not possible to save the added
    data for a later use.
    """

    def __init__(self):
        """
        The constructor of the user interface. The user Interface is initiated
        with a main window (self.__mainw) containing labels, buttons, an entry
        and an option menu. The result label (self.__result_label) displays
        the result and error messages. The other labels direct the user with
        instruction texts. The entry (self.__size_entry) is for a user input,
        size of a knitwork (cm). The option menu (self.__yarns_menu) displays
        the yarn names. The buttons are for calculation
        (self.__calculate_button), for terminating the program
        (self.__exit_button) and for adding new data into the yarn library.

        The user interface is also initiated with a dictionary
        (self.__yarns_dict), containing
        data about yarns (name and knitting tension), and  a variable for
        users choice (self.__choice) which is empty (value None) when starting
        the program. The choice stores the selected option (yarn name) of
        the user needed in the calculation.
        """

        self.__mainw = Tk()
        self.__mainw.title("Stitches for Knitwork")
        self.__mainw.geometry("600x500")
        self.__mainw["background"] = "#f1b199"


        self.__yarns_dict = {"Nalle": 22, "Isoveli": 15, "Nordic wool": 22,
                             "Venla": 28, "7 veljestä": 18
                             }
        self.__choice = None




        # Heading label
        self.__heading_label = Label(self.__mainw, text="How many stitches for"
                                                    " a new knitwork?",
                                                    background="#f1b199")
        self.__heading_label.grid(row=0, column=0, rowspan=2, padx=20, pady=20)
        self.__heading_label.configure(font=8)



        # Instruction labels for the size input
        self.__instruction_label = Label(self.__mainw,
                                         text="Make the measurment needed for "
                                              "your knitwork and choose the "
                                              "yarn.", background="#f1b199")
        self.__instruction_label.grid(row=3, column=0, sticky=W, padx=40,
                                      pady=20)


        self.__size_label = Label(self.__mainw, text="Size ",
                                  background="#f1b199")
        self.__size_label.grid(row=4, column=0, padx=(40,0), pady=(0, 20),
                               sticky=W)


        self.__cm_label = Label(self.__mainw, text="cm", background="#f1b199")
        self.__cm_label.grid(row=4, column=2, padx=(0, 20), pady=(0,20))



        # Entry for the size input
        self.__size_entry = Entry(self.__mainw)
        self.__size_entry.grid(row=4, column=0, padx=(0,0), pady=(0, 20),
                               sticky=E)



        # Instruction label for the selection of a yarn
        self.__choose_yarn = Label(self.__mainw, text="Used yarn ",
                                   background="#f1b199")
        self.__choose_yarn.grid(row=6, column=0, padx=(20, 0), sticky=W)



        # Optionmenu containing the keys (yarn names) of the dict
        self.__variable = StringVar(self.__mainw)
        self.__yarns_menu = OptionMenu(self.__mainw, self.__variable,
                                      *self.__yarns_dict.keys(),
                                      command=self.display_selected)
        self.__yarns_menu.grid(row=6, column=0, padx=(0, 20), sticky=E)



        # Label for the result and error texts
        self.__result_label = Label(self.__mainw, text=None, relief=GROOVE,
                                    background="#fcd2c2")
        self.__result_label.grid(row=9, column=0, padx=20, pady=(0, 40))


        # Button to calculate the result
        self.__calculate_button = Button(self.__mainw, text="OK",
                                         command=self.calculate_stitches)
        self.__calculate_button.grid(row=8, column=1, pady=40)


        # Button to exit the program
        self.__exit_button = Button(self.__mainw, text="Exit",
                                    command=self.exit)
        self.__exit_button.grid(row=11, column=0, padx=20, sticky=W)


        # Button to open a new window for adding new yarns into the library
        self.__add__to_library_button = Button(self.__mainw,
                                               text="Add to library",
                                               command=self.open_library_window)
        self.__add__to_library_button.grid(row=10, column=0, padx=20,
                                           pady=(0, 20), sticky=W)




    def open_library_window(self):
        """
        Opens a new window (self.__libraryw) for adding new yarns to the
        dictionary of yarns (self.__yarns_dict). The window (Toplevel) contains
        instruction labels for the user input and error messages, an entry for
        a name of a new yarn, an entry for a knitting tension (the user gets
        that value from the paper belt of the yarn ball), a button for
        adding the data into the dictionary and a button to exit the window.
        """

        self.__libraryw = Toplevel(self.__mainw)
        self.__libraryw.geometry("300x300")
        self.__libraryw["background"] = "#caa398"



        # Instruction labels for the user input
        self.__name_label = Label(self.__libraryw,
                                  text="Name of a yarn ",
                                  background="#caa398")
        self.__name_label.grid(column=0, row=0, padx=20, pady=(20, 0))


        self.__tension_label = Label(self.__libraryw,
                                     text="Tension, stitches per 10 cm ",
                                     background="#caa398")
        self.__tension_label.grid(column=0, row=2, padx=20, pady=(20, 0))



        # Entry for name of a new yarn
        self.__name_entry = Entry(self.__libraryw)
        self.__name_entry.grid(column=0, row=1, padx=20)


        # Entry for tension of a new yarn.
        self.__tension_entry = Entry(self.__libraryw)
        self.__tension_entry.grid(column=0, row=3, padx=20, pady=(0, 20))


        # Label for error texts
        self.__error_label = Label(self.__libraryw, text=None,
                                   background="#f0d0c7")
        self.__error_label.grid(column=0, row=4)


        # Button for adding data of a new yarn into the library.
        self.__add_button = Button(self.__libraryw, text="Add",
                           command=self.add_to_library)
        self.__add_button.grid(column=0, row=5, padx=20, pady=20)


        # Button to exit the library window (self.__libraryw)
        self.__back_button = Button(self.__libraryw, text="Back",
                                    command=self.back_to_mainw)
        self.__back_button.grid(column=0, row=6, padx=20)




    def add_to_library(self):
        """
        Takes the user input and adds the new yarn in the dictionary
        (self.__yarns_dict). Updates the Optionmenu (self.__yarn_menu)
        containing the keys of the dictionary. Raises error messages if
        the yarn name already exists in the library, if the tension value
        is not an integer or if the adding fails.

        :return: None
        """

        try:
            new_tension = int(self.__tension_entry.get())
        except ValueError:
            self.__error_label.configure(text="Tension must be an integer.")
            return


        new_yarn_name = self.__name_entry.get()
        if new_yarn_name in self.__yarns_dict:
            self.__error_label.configure(text="Name already exists in "
                                              "the library.")
            return


        self.__yarns_dict[new_yarn_name] = new_tension



        try:
            self.__variable = StringVar(self.__mainw)
            self.__yarn_menu = OptionMenu(self.__mainw, self.__variable,
                                      *self.__yarns_dict.keys(),
                                      command=self.display_selected)
            self.__yarn_menu.grid(row=6, column=1, sticky=W)


            self.__error_label.configure(text="Added successfully.")


        except AttributeError:
            self.__error_label.configure(text="Adding failed.")



    def back_to_mainw(self):
        """
        Closes the library window (self.__libraryw).
        """

        self.__libraryw.destroy()



    def display_selected(self, choice):
        """
        Takes the selected yarn name (a key of the dictionary) and stores it
        into a variable for later use (to get the dictionary value and use it
        in the calculation).

        :param choice: string, Selected option of the OptionMenu
        (self.__yarns_menu).
        :return: None
        """

        self.__yarn = choice



    def calculate_stitches(self):
        """
        Calculates the amount of stitches for a new knitwork. Raises error
        messages if the value of the size is not a float or an integer or if
        the user did not select a yarn name. Displays the result in the result
        label.
        """

        try:
            size = float(self.__size_entry.get())
        except ValueError:
            self.__result_label.configure(
                text=f"Give the measurement in numbers, 0 or 0.0")
            return


        try:
            tension = float(self.__yarns_dict[self.__yarn])
        except AttributeError:
            self.__result_label.configure(
                text=f"Choose the yarn.")
            return


        stitches = tension / 10 * size
        self.__result_label.configure(
            text=f"Create {round(stitches)} stitches.")




    def exit(self):
        """
        Ends the execution of the program.
        """
        self.__mainw.destroy()


    def start(self):
        """
        Starts the mainloop.
        """
        self.__mainw.mainloop()


def main():

    ui = User_interface()
    ui.start()


if __name__ == "__main__":
    main()