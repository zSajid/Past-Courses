import platform
import scrubber
import turret
import player
import pickup
import ogre.renderer.OGRE as ogre
import panel
import context
import label
import math
class GameMgr:
    def __init__(self, engine):
        self.engine = engine
        self.pickedUp = 0 #This is the number of items that have been picked up thus far
        self.deathCounter = 0
        self.origPlayer = ogre.Vector3(0, 100, 0)
        self.context = context.Context(self.engine)
        self.levelNum = 0 #Change this number to load a different level. 
        
        pass

    def init(self):
        self.ent = self.engine.gfxMgr.sceneManager.createEntity("Flag", "pCylinder1__Mt_Gold.mesh")
        self.flagNode = self.engine.gfxMgr.sceneManager.getRootSceneNode().createChildSceneNode("FlagNode", ogre.Vector3(10000,10000,10000))
        self.flagNode.attachObject(self.ent)
        self.flagNode.roll(math.radians(90))
        self.flagNode.yaw(math.radians(-90))
        self.flagNode.scale(2, 2, 2)     

        self.player = player.Player(self.engine, ogre.Vector3(10000, 10000, 10000))    

		#PickUp Creation
        for counter in range (0,5):
            self.engine.entityMgr.pickEntList.append(pickup.pickUp(counter, self.engine, pos = ogre.Vector3(10000, 10000, 10000)))

        #Load the levels
        self.loadNextLevel()
        pass

    def tick(self, dt):
        self.player.tick(dt)
        self.playerMoved()
    
        for platform in self.engine.entityMgr.platEntList:
            platform.tick(dt)

        for pickUp in self.engine.entityMgr.pickEntList:
            pickUp.tick(dt)

        for scruber in self.engine.entityMgr.scrubEntList:
            scruber.tick(dt)

        for turret in self.engine.entityMgr.turretEntList:
            turret.tick(dt)

        for i in range(0,5):
            num = self.engine.entityMgr.pickEntList[i].check(self.player.pos)
            self.pickedUp += num
            num = 0

        self.engine.controlMgr.updateCameras()

        self.diedCheck()
        #Pass in the Finish Platform Number
        self.levelCompleteCheck(self.curCompletPlat)

        pass

    def reset(self):
		#Platform Reset
        for platform in self.engine.entityMgr.platEntList:
            platform.reset()
		
		#Player Reset
        self.player.reset()
		
		#Pickup Reset
        for pickups in self.engine.entityMgr.pickEntList:
            pickups.reset()

		#Scruber Reset
        for scrubers in self.engine.entityMgr.scrubEntList:
            scrubers.reset()

		#Turret Reset
        for turrets in self.engine.entityMgr.turretEntList:
            turrets.reset()

        #Flag Reset
        self.flagNode.position = ogre.Vector3(10000, 10000, 10000)
	
        pass

#--------------------------------------------------Tutorial Level----------------------------------------------------------------------
    def tutorialLevel(self):
        #14 platforms total
        self.platCheck(14)
        self.turretCheck(1)
        self.platCounter = 0
        self.origPlayer = ogre.Vector3(0, 100, 0)       
        self.player.pos = ogre.Vector3(0, 100, 0)
        self.pickedUp = 0
        self.deathCounter = 0
        self.engine.uiMgr.startTimer()

        self.engine.entityMgr.turretEntList[0].position = ogre.Vector3(-500, 0, -300)
        self.engine.entityMgr.turretEntList[0].targetPoint = ogre.Vector3(200, 0, 0)

        #Start Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-100, 0, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-200, 0, -300)
        self.engine.entityMgr.pickEntList[0].pos = ogre.Vector3(-200, 30, -300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-150, 0, 300)
        self.engine.entityMgr.pickEntList[1].pos = ogre.Vector3(-150, 30, 300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, 0)
        self.engine.entityMgr.pickEntList[2].pos = ogre.Vector3(100, 30, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(200, 0, 0)
        self.platCounter += 1       
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 0, -300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 0, -300)
        self.engine.entityMgr.pickEntList[3].pos = ogre.Vector3(300, 30, -300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(200, 0, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 0, 300)
        self.engine.entityMgr.pickEntList[4].pos = ogre.Vector3(300, 30, 300)
        self.platCounter += 1
        #Finish Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(400, 0, 000)
        self.flagNode.position = ogre.Vector3(400, 0, 000)
        self.curCompletPlat = self.platCounter
        pass


#--------------------------------------------------Level One----------------------------------------------------------------------
    def levelOne(self):
        self.platCheck(26) #Update the Number
        self.scrubCheck(1)
        #self.turretCheck(1)
        self.platCounter = 0
        self.origPlayer = ogre.Vector3(0, 100, 0)       
        self.player.pos = ogre.Vector3(0, 100, 0)
        self.pickedUp = 0
        self.deathCounter = 0
        self.engine.uiMgr.startTimer()


        for tempVal in self.engine.entityMgr.scrubEntList:
            tempVal.playerMoved = False

        #Start Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 0)
        self.platCounter += 1

        self.engine.entityMgr.scrubEntList[0].position = ogre.Vector3(500, 0, 0)
        self.engine.entityMgr.scrubEntList[0].stopPosOne = ogre.Vector3(0, 0, 0)
        self.engine.entityMgr.scrubEntList[0].stopPosTwo = ogre.Vector3(300, 0, 0)
        #self.engine.entityMgr.scrubEntList[0].move = True

        #self.engine.entityMgr.turretEntList[0].position = ogre.Vector3(700, 50, 700)

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-100, 0, 0)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'X'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-200, 0, 0)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'X'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(-450, 0, 0)
        self.engine.entityMgr.pickEntList[0].pos = ogre.Vector3(-450, 30, 0)
        self.platCounter += 1

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'X'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, -450)
        self.engine.entityMgr.pickEntList[1].pos = ogre.Vector3(100, 30, -450)
        self.platCounter += 1

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 0, 325)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 475)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, 675)
        self.engine.entityMgr.pickEntList[2].pos = ogre.Vector3(100, 30, 675)
        self.platCounter += 1

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(200, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(400, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(500, 0, 0)
        self.platCounter += 1

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(400, 0, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(400, 0, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(500, 100, -300)
        self.engine.entityMgr.pickEntList[3].pos = ogre.Vector3(500, 130, -300)
        self.platCounter += 1

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(500, 0, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(500, 0, 300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 0, 300)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(700, 0, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Z'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(700, 0, 600)
        self.platCounter += 1
        self.engine.entityMgr.pickEntList[4].pos = ogre.Vector3(700, 30, 600)

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(700, 0, 0)
        self.flagNode.position = ogre.Vector3(700, 0, 000)
        self.curCompletPlat = self.platCounter
        pass

#--------------------------------------------------Level Two----------------------------------------------------------------------
    def levelTwo(self):
        self.platCheck(38) #Update the Number
        #self.scrubCheck(1)
        #self.turretCheck(1)
        self.platCounter = 0
        self.origPlayer = ogre.Vector3(0, 100, 0)       
        self.player.pos = ogre.Vector3(0, 100, 0)
        self.pickedUp = 0
        self.deathCounter = 0
        self.engine.uiMgr.startTimer()

        for tempVal in self.engine.entityMgr.scrubEntList:
            tempVal.playerMoved = False
        
        self.engine.entityMgr.turretEntList[0].position = ogre.Vector3(-500, 0, -300)
        self.engine.entityMgr.turretEntList[0].targetPoint = ogre.Vector3(300, 0, 0)

        #Start Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 0)
        self.platCounter += 1

        #self.engine.entityMgr.scrubEntList[0].position = ogre.Vector3(500, 10, 0)
        #self.engine.entityMgr.scrubEntList[0].heading = math.radians(180)
        #self.engine.entityMgr.turretEntList[0].position = ogre.Vector3(700, 50, 700)

        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(100, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(200, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 0, -75)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 0, 75)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 0, 150)
        self.engine.entityMgr.pickEntList[0].pos = ogre.Vector3(600, 30, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 0, -150)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'X'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 0, -75)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 0, 75)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(900, 0, 0)
        self.platCounter += 1

        #Right Split
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(800, 0, 225)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(800, 0, 375)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(700, 0, 525)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 0, 675)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(700, 0, 750)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(800, 0, 825)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(950, 0, 825)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1100, 0, 825)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1100, 0, 675)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1100, 0, 525)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1100, 0, 375)
        self.engine.entityMgr.pickEntList[1].pos = ogre.Vector3(1100, 30, 375)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1000, 0, 975)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Z'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1000, 0, 1125)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Z'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1000, 0, 1275)
        self.engine.entityMgr.pickEntList[2].pos = ogre.Vector3(1000, 30, 1275)
        self.platCounter += 1

        #Left Split
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 50, -350)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 100, -500)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 100, -650)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'X'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 100, -650)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 100, -650)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 100, -650)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 100, -500)
        self.engine.entityMgr.pickEntList[3].pos = ogre.Vector3(150, 130, -500)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 0, -350)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 0, -200)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 100, -650)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(900, 100, -650)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1050, 100, -650)
        self.engine.entityMgr.pickEntList[4].pos = ogre.Vector3(1050, 130, -650)
        self.platCounter += 1

        #Final Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(1100, 0, 0)
        self.flagNode.position = ogre.Vector3(1100, 0, 000)
        self.curCompletPlat = self.platCounter
        pass

#--------------------------------------------------Level Three----------------------------------------------------------------------
    def levelThree(self):
        self.platCheck(44) #Update the Number
        #self.scrubCheck(1)
        #self.turretCheck(1)
        self.platCounter = 0
        self.origPlayer = ogre.Vector3(0, 100, 0)       
        self.player.pos = ogre.Vector3(0, 100, 0)
        self.pickedUp = 0
        self.deathCounter = 0
        self.engine.uiMgr.startTimer()

        for tempVal in self.engine.entityMgr.scrubEntList:
            tempVal.playerMoved = False
	
        #Start Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 0, 0)
        self.platCounter += 1

        #Start of the Spiral
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 0, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 25, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 50, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 75, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 100, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 125, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 150, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 175, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 200, 0)
        self.platCounter += 1

        #Second Spiral
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 225, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 250, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 275, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 300, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 325, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 350, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 375, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 400, 0)
        self.platCounter += 1

        #Thrid Spiral
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 425, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 450, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 475, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 500, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 525, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 550, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 575, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 600, 0)
        self.platCounter += 1

        #Forth Spiral
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 625, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 650, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 675, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 700, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 725, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 750, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 775, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 800, 0)
        self.platCounter += 1

        #Fifth Spiral
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 825, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 850, 300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 875, 150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(750, 900, 0)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(600, 925, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(450, 950, -300)
        self.engine.entityMgr.platEntList[self.platCounter].direction = 'Y'
        self.engine.entityMgr.platEntList[self.platCounter].movement = True
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(300, 975, -150)
        self.platCounter += 1
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(150, 1000, 0)
        self.platCounter += 1

        #Final Platform
        self.engine.entityMgr.platEntList[self.platCounter].position = ogre.Vector3(0, 1000, 0)
        self.flagNode.position = ogre.Vector3(0, 1000, 000)
        self.curCompletPlat = self.platCounter
        pass

    def platCheck(self, platNum):
        self.size = len(self.engine.entityMgr.platEntList)
        self.tempInt = int(math.fabs(self.size - platNum))
        for counter in range(self.size, self.tempInt + self.size):
            self.ent = platform.Platform(counter, self.engine, ogre.Vector3(1000, 1000, 1000))
            self.engine.entityMgr.platEntList.append(self.ent)

    def scrubCheck(self, scrubNum):
        self.size = len(self.engine.entityMgr.scrubEntList)
        self.tempInt = int(math.fabs(self.size - scrubNum))
        for counter in range(self.size, self.tempInt + self.size):
            self.ent = scrubber.Scrubber(counter, self.engine, ogre.Vector3(1000, 1000, 1000))
            self.engine.entityMgr.scrubEntList.append(self.ent)

    def turretCheck(self, turNum):
        self.size = len(self.engine.entityMgr.turretEntList)
        self.tempInt = int(math.fabs(self.size - turNum))
        for counter in range(self.size, self.tempInt + self.size):
            self.ent = turret.Turret(counter, self.engine, ogre.Vector3(1000, 1000, 1000))
            self.engine.entityMgr.turretEntList.append(self.ent)

    def levelCompleteCheck(self, platNum):         
        if self.pickedUp >= 3:
            if (self.player.oneCollideCheck(platNum) == True):
                #Do stuff for level completion
                self.engine.uiMgr.levelEnd()
                self.engine.soundMgr.stop(3)
                self.reset()
                self.loadNextLevel()
        pass

    def loadNextLevel(self):
        if(self.levelNum == 0):
            self.engine.soundMgr.stop(3)
            self.engine.soundMgr.playSound("8_Bit_Weapon_-_Chip_On_Your_Shoulder.wav", 50)
            self.tutorialLevel()
            self.levelNum += 1
        elif(self.levelNum == 1):
            self.engine.soundMgr.playSound("Lazerhawk_-_Overdrive.wav", 50)
            self.levelOne()
            self.levelNum += 1
        elif(self.levelNum == 2):
            self.engine.soundMgr.playSound("SeaNanners_Ending_Music_-_Daniel_Holter_Matt_Smith.wav", 50)
            self.levelTwo()
            self.levelNum += 1
        elif(self.levelNum == 3):
            self.engine.soundMgr.playSound("TeknoAXE_39_s_Royalty_Free_Music_-_Loop_14-B_Digit.wav", 50)
            self.levelThree()
            self.levelNum += 1
        elif(self.levelNum == 4):
            self.engine.soundMgr.playSound("TeknoAXE_39_s_Royalty_Free_Music_-_Royalty_Free_Mu (1)", 50)
            self.engine.uiMgr.credits()
            self.levelNum = 0        
            
    def diedCheck(self):
        if(self. player.pos.y < -100):
            self.engine.soundMgr.playSound("0477.wav", 0)
            self.deathCounter += 1
            self.player.pos =  self.origPlayer
            self.player.node.position = self.player.pos

    def playerMoved(self):
        if(self.player.pos.x != self.origPlayer.x or self.player.pos.z != self.origPlayer.z):
            for tempVal in self.engine.entityMgr.scrubEntList:
                tempVal.playerMoved = True

    def stop(self):
        pass

