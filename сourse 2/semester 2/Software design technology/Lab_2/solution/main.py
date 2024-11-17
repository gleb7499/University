import os
import sqlite3 as sq

if os.path.exists("data.db"):
    try:
        os.remove("data.db")
    except os.error:
        print("\t***Ошибка удаления базы!***")
        exit(-1)

GroupInfo = ['Construction', 'Services', 'Manufacturing']
Region = ['North', 'South', 'Central']
Contractor = [('ABC Construction', 'Construction', 'South', '123456789', '123 Main St'),
              ('XYZ Services', 'Manufacturing', 'North', '987654321', '456 Elm St'),
              ('LMN Manufacturing', 'Services', 'Central', '555555555', '789 Oak Ave')]
Affiliate = [('ABC Construction', 'ABC Mart', '100 Market St'),
             ('XYZ Services', 'XYZ Warehouse', '200 Industrial Ave'),
             ('LMN Manufacturing', 'LMN Factory', '300 Factory Rd')]
Account = [('ABC Construction', 'Bank A', '12345678', 'USD'),
           ('XYZ Services', 'Bank B', '98765432', 'EUR'),
           ('LMN Manufacturing', 'Bank C', '55555555', 'JPY')]
NameTable = ['GroupInfo', 'Region', 'Contractor', 'Affiliate', 'Account']

con = None
try:
    con = sq.connect("data.db")
    con.execute("PRAGMA foreign_keys = ON;")
    cursor = con.cursor()
    cursor.execute("""CREATE TABLE IF NOT EXISTS GroupInfo (
        GroupID INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT
        )""")
    cursor.execute("""CREATE TABLE IF NOT EXISTS Region (
        RegionID INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT
        )""")
    cursor.execute("""CREATE TABLE IF NOT EXISTS Contractor (
        ContractorID INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT,
        GroupID INTEGER,
        RegionID INTEGER,
        UNN TEXT,
        Adr TEXT,
        FOREIGN KEY (GroupID) REFERENCES GroupInfo (GroupID),
        FOREIGN KEY (RegionID) REFERENCES Region (RegionID)
        )""")
    cursor.execute("""CREATE TABLE IF NOT EXISTS Affiliate (
        AffiliateID INTEGER PRIMARY KEY AUTOINCREMENT,
        ContractorID INTEGER,
        Name TEXT,
        Adr TEXT,
        FOREIGN KEY (ContractorID) REFERENCES Contractor (ContractorID)
        )""")
    cursor.execute("""CREATE TABLE IF NOT EXISTS Account (
        AccountID INTEGER PRIMARY KEY AUTOINCREMENT,
        ContractorID INTEGER,
        Bank TEXT,
        Account TEXT,
        Currency TEXT,
        FOREIGN KEY (ContractorID) REFERENCES Contractor (ContractorID)
        )""")

    cursor.executemany("INSERT INTO GroupInfo VALUES(NULL, ?)", [(item,) for item in GroupInfo])
    cursor.executemany("INSERT INTO Region VALUES(NULL, ?)", [(item,) for item in Region])
    for contractor in Contractor:
        name, group_name, region_name, unn, adr = contractor
        cursor.execute("SELECT RegionID FROM Region WHERE Name = ?", (region_name,))
        try:
            region_id = cursor.fetchone()[0]
        except TypeError:
            print("\t***Регион не найден в таблице Region!***")
            exit(-1)
        cursor.execute("SELECT GroupID FROM GroupInfo WHERE Name = ?", (group_name,))
        try:
            group_id = cursor.fetchone()[0]
        except TypeError:
            print("\t***Группа не найдена в таблице Group!***")
            exit(-1)
        cursor.execute("INSERT INTO Contractor VALUES(NULL, ?, ?, ?, ?, ?)", (name, group_id, region_id, unn, adr))
    for affiliate in Affiliate:
        contractor_name, name, adr = affiliate
        cursor.execute("SELECT ContractorID FROM Contractor WHERE Name = ?", (contractor_name,))
        try:
            contractor_id = cursor.fetchone()[0]
        except TypeError:
            print("\a***Подрядчик не найден в таблице Contractor!***")
            exit(-1)
        cursor.execute("INSERT INTO Affiliate VALUES(NULL, ?, ?, ?)", (contractor_id, name, adr))
    for account in Account:
        contractor_name, bank, acc, currency = account
        cursor.execute("SELECT ContractorID FROM Contractor WHERE Name = ?", (contractor_name,))
        try:
            contractor_id = cursor.fetchone()[0]
        except TypeError:
            print("\a***Подрядчик не найден в таблице Contractor!***")
            exit(-1)
        cursor.execute("INSERT INTO Account VALUES(NULL, ?, ?, ?, ?)", (contractor_id, bank, acc, currency))
    con.commit()

    with open("report.txt", 'a+', encoding='utf-8') as report:
        report.truncate(0)
        report.seek(0)
        cursor.execute("SELECT Contractor.ContractorID, Contractor.Name, Contractor.GroupID, GroupInfo.Name, Contractor.RegionID, Region.Name, Contractor.UNN, Contractor.Adr "
                       "FROM Contractor "
                       "JOIN GroupInfo ON Contractor.GroupID = GroupInfo.GroupID "
                       "JOIN Region ON Contractor.RegionID = Region.RegionID")
        report.write("\t\tСекция таблицы подрядчиков Contractor:\n")
        for count, result in enumerate(cursor, start=1):
            report.write(f"\tПодрядчик №{count}\n")
            report.write(f"Идентификатор подрядчика: {result[0]}\n"
                         f"Наименование подрядчика: {result[1]}\n"
                         f"Идентификатор группы из справочника групп: {result[2]}\n"
                         f"Наименование группы из справочника групп: {result[3]}\n"
                         f"Идентификатор региона из справочника регионов: {result[4]}\n"
                         f"Наименование региона из справочника регионов: {result[5]}\n"
                         f"УНП: {result[6]}\n"
                         f"Адрес юрлица: {result[7]}\n")
        cursor.execute("SELECT Affiliate.AffiliateID, Affiliate.Name, Affiliate.ContractorID, Contractor.Name, Affiliate.Adr "
                       "FROM Affiliate JOIN Contractor ON Affiliate.ContractorID=Contractor.ContractorID")
        report.write("\t\tСекция таблицы филиалов Affiliate:\n")
        for count, result in enumerate(cursor, start=1):
            report.write(f"\tФилиал №{count}\n")
            report.write(f"Идентификатор филиала: {result[0]}\n"
                         f"Наименование филиала: {result[1]}\n"
                         f"Идентификатор подрядчика: {result[2]}\n"
                         f"Наименование подрядчика: {result[3]}\n"
                         f"Адрес филиала: {result[4]}\n")
        cursor.execute("SELECT Account.AccountID, Account.ContractorID, Contractor.Name, Account.Bank, Account.Account, Account.Currency "
                       "FROM Account JOIN Contractor ON Account.ContractorID=Contractor.ContractorID")
        report.write("\t\tСекция таблицы расчетных счетов Account:\n")
        for count, result in enumerate(cursor, start=1):
            report.write(f"\tРасчетный счет №{count}\n")
            report.write(f"Идентификатор счета: {result[0]}\n"
                         f"Идентификатор подрядчика: {result[1]}\n"
                         f"Наименование подрядчика: {result[2]}\n"
                         f"Банк: {result[3]}\n"
                         f"Расчетный счет: {result[4]}\n"
                         f"Валюта счета: {result[5]}\n")

        print("Удалить таблицу? (1 - Да, 0 - Нет) -> ", end="")
        if int(input()) == 1:
            con.execute("PRAGMA foreign_keys = OFF;")
            for table in NameTable:
                cursor.execute(f"DROP TABLE {table}")

except sq.Error:
    if con: con.rollback()
    print("\t***Ошибка выполнения запроса!***")
finally:
    if con: con.close()
