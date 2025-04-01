import tkinter as tk
from tkinter import ttk

fio_list = [
    {
        "FIO": "Иванов Петр Сидорович",
        "Addresses": [
            {
                "town": "Брест",
                "street": "Московская",
                "house": 208
            },
            {
                "town": "Брест",
                "street": "Машерова",
                "house": 17
            }
        ]
    },
    {
        "FIO": "Кузьменко Даниил Эдуардович",
        "Addresses": [
            {
                "town": "Минск",
                "street": "Независимости",
                "house": 34
            }
        ]
    },
    {
        "FIO": "Матусевич Евгения Владимировна",
        "Addresses": [
            {
                "town": "Гомель",
                "street": "Советская",
                "house": 56
            },
            {
                "town": "Гомель",
                "street": "Ленина",
                "house": 78
            }
        ]
    }
]


def update_addresses(event=None):
    if listbox.curselection():
        selected_user = listbox.get(listbox.curselection())
        for user in fio_list:
            if user["FIO"] == selected_user:
                treeview.delete(*treeview.get_children())
                if show_addresses.get():
                    for address in user["Addresses"]:
                        treeview.insert('', 'end', values=(address["town"], address["street"], address["house"]))


def initialize_data():
    for user in fio_list:
        listbox.insert(tk.END, user["FIO"])


def reset_data():
    listbox.delete(0, tk.END)
    treeview.delete(*treeview.get_children())


root = tk.Tk()
root.geometry('600x500')

label_users = tk.Label(root, text='Список пользователей')
label_users.pack()

listbox = tk.Listbox(root, width=40, height=10)
listbox.bind('<<ListboxSelect>>', update_addresses)
listbox.pack()

label_adr = tk.Label(root, text='Адрес выбранного пользователя')
label_adr.pack()

columns = ("Город", "Улица", "Дом")
treeview = ttk.Treeview(root, columns=columns, show='headings')
for column in columns:
    treeview.heading(column, text=column)
treeview.pack()

button_frame = tk.Frame(root)
button_frame.pack()

initialize_button = tk.Button(button_frame, text="Инициализировать данные", command=initialize_data)
initialize_button.pack(side=tk.LEFT)

reset_button = tk.Button(button_frame, text="Сбросить данные", command=reset_data)
reset_button.pack(side=tk.LEFT)

show_addresses = tk.BooleanVar(button_frame, value=True)
checkbutton = tk.Checkbutton(root, text="Показать адреса", variable=show_addresses, command=update_addresses)
checkbutton.pack()

menubar = tk.Menu(root)
menu = tk.Menu(menubar, tearoff=0)
menu.add_command(label="Инициализировать данные", command=initialize_data)
menu.add_command(label="Сбросить данные", command=reset_data)
menubar.add_cascade(label="Меню", menu=menu)
root.config(menu=menubar)

root.mainloop()
