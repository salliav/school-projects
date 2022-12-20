"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150427834
Name:       Salli Valkama
Email:      salli.valkama@tuni.fi

13.5 Kappaletavaralaskuri
"""

from tkinter import *


class Counter:
    def __init__(self):

        self.__main_window = Tk()
        self.__integer = 0


        self.__current_value_label = Label(self.__main_window, relief=GROOVE, text=int(self.__integer), borderwidth=2)
        self.__current_value_label.grid(row=0, column=0, columnspan=5, sticky=W+E)

        self.__reset_button = Button(self.__main_window, relief=RAISED, borderwidth=2, text="Reset", command=self.reset)
        self.__reset_button.grid(row=1, column=0)

        self.__increase_button = Button(self.__main_window, relief=RAISED, borderwidth=2, text="Increase", command=self.increase)
        self.__increase_button.grid(row=1, column=1)

        self.__decrease_button = Button(self.__main_window, relief=RAISED, borderwidth=2, text="Decrease", command=self.decrease)
        self.__decrease_button.grid(row=1, column=2)

        self.__quit_button = Button(self.__main_window, relief=RAISED, borderwidth=2, text="Quit", command=self.quit)
        self.__quit_button.grid(row=1, column=3)


        self.__main_window.mainloop()


    def reset(self):

        self.__integer = 0

        self.__current_value_label.configure(text=int(self.__integer))


    def increase(self):

        self.__integer += 1

        self.__current_value_label.configure(text=int(self.__integer))


    def decrease(self):

        self.__integer -= 1

        self.__current_value_label.configure(text=int(self.__integer))


    def quit(self):

        self.__main_window.destroy()



def main():
    # There is no need to modify the main function.
    # As a matter of fact, automated tests ignore main
    # once again.

    Counter()


if __name__ == "__main__":
    main()
