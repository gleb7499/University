import random


class Game:
    def __init__(self):
        self.sheriff = Sheriff()
        self.trader = Trader()
        self.sheriffsList = list()
        self.tradersList = list()

    def start(self, quantity):
        print("Итерация\t\tШериф\t\tТорговец")

        for i in range(quantity):
            sheriffsAction = self.sheriff.check()
            tradersAction = self.trader.cheat()
            sheriffsScore = 0
            tradersScore = 0

            if sheriffsAction == "проверить" and tradersAction == "не обмануть":
                self.sheriff.setIsTraderCaught(False)
                self.trader.setIsSheriffChecked(True)
                sheriffsScore = -2
                tradersScore = 0
                self.sheriffsList.append(sheriffsScore)
            if sheriffsAction == "проверить" and tradersAction == "обмануть":
                self.sheriff.setIsTraderCaught(True)
                self.trader.setIsSheriffChecked(True)
                sheriffsScore = 3
                tradersScore = -3
                self.sheriffsList.append(sheriffsScore)
                self.tradersList.append(tradersScore)
            if sheriffsAction == "не проверять" and tradersAction == "обмануть":
                self.sheriff.setIsTraderCaught(False)
                self.trader.setIsSheriffChecked(False)
                sheriffsScore = -2
                tradersScore = 1
                self.sheriffsList.append(sheriffsScore)
                self.tradersList.append(tradersScore)
            if sheriffsAction == "не проверять" and tradersAction == "не обмануть":
                self.sheriff.setIsTraderCaught(False)
                self.trader.setIsSheriffChecked(False)
                sheriffsScore = 0
                tradersScore = 0

            print(str(i) + "\t\t" + sheriffsAction + " = " + str(sheriffsScore) + "\t\t" + tradersAction + " = " + str(tradersScore))

    def printResults(self):
        print("\nШериф:")
        print(sum(self.sheriffsList))
        print("Торговец:")
        print(sum(self.tradersList))

        print("\nВыиграл " + "Шериф" if sum(self.sheriffsList) > sum(self.tradersList) else "Торговец")


class Sheriff:
    def __init__(self):
        self.__isTraderCaught = False
        self.__list = ["проверить", "не проверять"]

    def check(self) -> str:
        return random.choices(self.__list, weights=[0.7, 0.3] if self.__isTraderCaught else [0.5, 0.5])[0]

    def setIsTraderCaught(self, isTraderCaught: bool):
        self.__isTraderCaught = isTraderCaught


class Trader:
    def __init__(self):
        self.__isSheriffChecked = False
        self.__list = ["обмануть", "не обмануть"]

    def cheat(self) -> str:
        return random.choices(self.__list, weights=[0.3, 0.7] if self.__isSheriffChecked else [0.5, 0.5])[0]

    def setIsSheriffChecked(self, isSheriffChecked: bool):
        self.__isSheriffChecked = isSheriffChecked


if __name__ == '__main__':
    game = Game()
    game.start(10)
    game.printResults()
