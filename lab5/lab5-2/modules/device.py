import random
import asyncio

class Device:
    def __init__(self):
        self.ledStateList = [False for i in range(4)]
        self.isChanged = False

    def getADCValue(self):       
        return random.randint(0, 1024)

    def setAllLedStatus(self, statusList):
        self.ledStateList = statusList
        self.isChanged = True

    async def shine(self, times):
        for i in range(times):
            self.setAllLedStatus([True, True, False, False])
            await asyncio.sleep(0.8)
            self.setAllLedStatus([False, False, True, True])
            await asyncio.sleep(0.8)

    async def onLedStateChange(self, callback):
        if self.isChanged:
            self.isChanged = False
            await callback(self.ledStateList)
        else:
            await asyncio.sleep(0)