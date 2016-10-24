import ogre.io.OIS as OIS
import panel
import context
import label
import time
from timeit import default_timer

class UIMgrs:
    def __init__(self, engine):
        self.engine = engine
        self.splashbool = True
        self.totalStars = 0
        self.timer = 0
        self.time = 0
        self.oldTime = 0
        self.renderPanel = False
        self.start = ""
        self.soundBool = True
        self.starNum = 0
        self.instrucBool = False

        self.screenWidth = self.engine.gfxMgr.viewPort.getActualWidth()
        self.screenHeight = self.engine.gfxMgr.viewPort.getActualHeight()

		#Change when there is a joystick hooked up.
        self.joystickBool = False #self.engine.controlMgr.moveList.joystickBool

        self.buttonA = 0
        self.startButton = 0

        pass

    def startTimer(self):
        self.start = default_timer()

    def init(self):
        self.tempName = "Testing Panel"
        self.context = context.Context(self.engine)

        self.splashPanel = panel.Panel(self.context, "Splash", (0, 0), (self.screenWidth, self.screenHeight), "FinalProject/Splash")
        self.instrucPanel = panel.Panel(self.context, "Instructions", (0,0), (self.screenWidth, self.screenHeight), "FinalProject/Instructions")
        self.splashPanel.show()
        self.instrucPanel.hide()

    def initalize(self):
            self.levelPanelStartX = (self.screenWidth/2) - 250
            self.levelPanelStartY = (self.screenHeight/2) - 150

            self.deathLabel = label.Label(self.context, "deathLabel", (1.0, 1.0, 1.0), (100, 25), (100, 100))
            self.pickupLabel = label.Label(self.context, "pickupLabel", (1.0, 1.0, 1.0), (100, 25), (100, 100))
            self.timeLabel = label.Label(self.context, "timeLabel", (1.0, 1.0, 1.0), (100, 25), (100, 100))
            self.starLabel = label.Label(self.context, "starLabel", (1.0, 1.0, 1.0), (100, 25), (100, 100))

            self.deathPanel = panel.Panel(self.context, "deathPanel", (0, 0), (200, 25), "FinalProject/Panel")
            self.pickupPanel = panel.Panel(self.context, "pickupPanel", (0, self.screenHeight - 25), (200, 25), "FinalProject/Panel")
            self.timePanel = panel.Panel(self.context, "timePanel", (self.screenWidth - 200, 0), (200, 25), "FinalProject/Panel")
            self.starcountPanel = panel.Panel(self.context, "starPanel", (self.screenWidth - 200, self.screenHeight - 25), (200, 25), "FinalProject/Panel")
            self.levelPanel = panel.Panel(self.context, "levelPanel", (self.levelPanelStartX, self.levelPanelStartY), (500, 200), "FinalProject/Panel")
            self.starPanel1 = panel.Panel(self.context, "starPanel1", (self.levelPanelStartX + 50, self.levelPanelStartY + 45), (100,100), "FinalProject/FilledStar")
            self.starPanel2 = panel.Panel(self.context, "starPanel2", (self.levelPanelStartX + 200, self.levelPanelStartY + 45), (100,100), "FinalProject/FilledStar")
            self.starPanel3 = panel.Panel(self.context, "starPanel3", (self.levelPanelStartX + 350, self.levelPanelStartY + 45), (100,100), "FinalProject/FilledStar")
            self.starPanel4 = panel.Panel(self.context, "starPanel1", (self.levelPanelStartX + 200, self.levelPanelStartY + 45), (100,100), "FinalProject/EmptyStar")
            self.starPanel5 = panel.Panel(self.context, "starPanel1", (self.levelPanelStartX + 350, self.levelPanelStartY + 45), (100,100), "FinalProject/EmptyStar")
            self.creditPanel = panel.Panel(self.context, "credits", (0,0), (self.screenWidth, self.screenHeight), "FinalProject/Credits")

            self.deathPanel.addItem(self.deathLabel)
            self.pickupPanel.addItem(self.pickupLabel)
            self.timePanel.addItem(self.timeLabel)
            self.starcountPanel.addItem(self.starLabel)

            self.deathPanel.show()
            self.pickupPanel.show()
            self.timePanel.show()
            self.starcountPanel.show()
            self.levelPanel.hide()
            self.starPanel1.hide()
            self.starPanel2.hide()
            self.starPanel3.hide()
            self.starPanel4.hide()
            self.starPanel5.hide()

            self.deathLabel.show()
            self.pickupLabel.show()
            self.timeLabel.show()
            self.starLabel.show()

            self.creditPanel.hide()

            self.number = 0
            #self.time_start = time.time()
            self.seconds = 0
            self.minutes = 0

    def tick(self, dt):
        if self.joystickBool:
            self.buttonA = self.engine.controlMgr.moveList.buttonA
            self.startButton = self.engine.controlMgr.moveList.startButton

        if (self.engine.inputMgr.keyboard.isKeyDown (OIS.KC_RETURN) or self.startButton == 1) and self.splashbool == True:
            self.splashbool = False
            self.splashPanel.hide()
            self.instrucPanel.show()
            self.instrucBool = True
            
            
        if (self.engine.inputMgr.keyboard.isKeyDown (OIS.KC_SPACE) or self.buttonA == 1) and self.instrucBool == True:
            self.instrucPanel.hide()
            self.instrucBool = False
            if(self.soundBool == True):
                #self.engine.soundMgr.stop(1)
                self.soundBool = False
                
        self.duration = default_timer()-self.start
        self.duration = '%.2f' % self.duration

        if (self.splashbool == False and self.instrucBool == False):
            if(self.renderPanel == False):
                self.renderPanel = True
                self.initalize()
            self.deathLabel.setCaption("   Deaths: " + str(self.engine.gameMgr.deathCounter))
            self.pickupLabel.setCaption(" Picked Up: " + str(self.engine.gameMgr.pickedUp))
            self.timeLabel.setCaption("   Time: " + str(self.duration))
            self.starLabel.setCaption("    Stars: " + str(self.totalStars))            

    def levelEnd (self): #place before change of level code
        self.timer = 0
        self.starNum = 1
        self.levelBool = True

        if self.engine.gameMgr.deathCounter < 1:
            self.starNum += 1
        if self.engine.gameMgr.pickedUp == 5:
            self.starNum += 1

        self.levelPanel.show()
        self.engine.gfxMgr.root.renderOneFrame()
        while self.timer < 2:
            self.time = time.time()
            self.timer += self.time - self.oldTime
            self.oldTime = self.time

        self.timer = 0
        self.starPanel1.show()
        #play some happy music
        self.engine.gfxMgr.root.renderOneFrame()

        while self.timer < 1:
            self.time = time.time()
            self.timer += self.time - self.oldTime
            self.oldTime = self.time
        self.engine.gfxMgr.root.renderOneFrame()
        self.timer = 0

        if self.starNum == 2:
            self.starPanel2.show()
            self.engine.gfxMgr.root.renderOneFrame()
            #happy music
            while self.timer < 1:
                self.time = time.time()
                self.timer += self.time - self.oldTime
                self.oldTime = self.time
            self.engine.gfxMgr.root.renderOneFrame()
            self.timer = 0
            self.starPanel5.show()
            #sad music

        elif self.starNum == 3:
            self.starPanel2.show()
            #happy music
            self.engine.gfxMgr.root.renderOneFrame()
            while self.timer < 1:
                self.time = time.time()
                self.timer += self.time - self.oldTime
                self.oldTime = self.time
            self.engine.gfxMgr.root.renderOneFrame()
            self.timer = 0
            self.starPanel3.show()
            #happy music

        else:
            self.starPanel4.show()
            #sad music
            self.engine.gfxMgr.root.renderOneFrame()
            while self.timer < 1:
                self.time = time.time()
                self.timer += self.time - self.oldTime
                self.oldTime = self.time
            self.engine.gfxMgr.root.renderOneFrame()
            self.starPanel5.show()
            #sad music

        while self.levelBool == True:
			self.engine.gfxMgr.root.renderOneFrame()
			if self.engine.inputMgr.keyboard.isKeyDown (OIS.KC_RETURN):
				self.totalStars = self.totalStars + self.starNum
				self.levelPanel.hide()
				self.starPanel1.hide()
				self.starPanel2.hide()
				self.starPanel3.hide()
				self.starPanel4.hide()
				self.starPanel5.hide()
				self.levelBool = False


    def credits (self):
        self.creditPanel.show()
        self.starcountPanel.hide()
        self.timePanel.hide()
        self.pickupPanel.hide()
        self.deathPanel.hide()

    def stop(self):
        pass
