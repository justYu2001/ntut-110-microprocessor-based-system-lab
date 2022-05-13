import random
import asyncio

class Device:
    def __init__(self):
        self.ledStateList = [False for i in range(2)]
        self.isChanged = False

    def getADCValue(self):       
        return random.randint(0, 1024)

    def setLedStateList(self, ledStateList):
        self.ledStateList = ledStateList
        self.isChanged = True

    def getLedStateList(self):
        return self.ledStateList

    async def shine(self, times):
        for i in range(times):
            self.setAllLedStatus([True, False])
            await asyncio.sleep(0.8)
            self.setAllLedStatus([False, True])
            await asyncio.sleep(0.8)