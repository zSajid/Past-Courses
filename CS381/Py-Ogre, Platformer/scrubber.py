import ogre.renderer.OGRE as ogre
import math

class Scrubber:
    def __init__(self, scrubberNum, engine, pos = ogre.Vector3(0, 0, 0)):
        self.default = ogre.Vector3(10000, 10000, 10000) #Vector
        self.position = pos
        self.sceneManager = engine.gfxMgr.sceneManager
        self.engine = engine
        self.velocity = ogre.Vector3(0, 0, 0)
        self.node = ''
        self.area = 0
        self.playerMoved = False
        self.move = False
        self.heading = 0
        self.scrubVelFactor = 40
        self.scrubEntity = "Scrubber" + str(scrubberNum) #Need a number passed in to create the right entity.
        self.mesh = "scrubberFinalOriented.mesh"
        self.scaleFactor = 5
        self.velocity = ogre.Vector3(0,0,0)
        self.stopPosOne = ogre.Vector3(0, 0, 0)
        self.stopPosTwo = ogre.Vector3(0, 0, 0)
        self.oneTwoDirection = False
        self.inProgressMovement = False
        self.tempPos = ogre.Vector3(0, 0, 0)
        self.playerCollideCounter = 0

        #Bounding Box Points
        self.point1 = ogre.Vector3(0, 0, 0)
        self.point2 = ogre.Vector3(0, 0, 0)
        self.point3 = ogre.Vector3(0, 0, 0)
        self.point4 = ogre.Vector3(0, 0, 0)
        self.defualtHeight = 3
        self.init()
        pass

    def init(self):
        self.ent = self.sceneManager.createEntity(self.scrubEntity, self.mesh)
        node = self.sceneManager.getRootSceneNode().createChildSceneNode(self.scrubEntity + 'node', self.position)
        node.attachObject(self.ent)
        self.node = node
        self.node.scale(self.scaleFactor, self.scaleFactor, self.scaleFactor)
        #print "Generated a scrubber at:" + str(self.position)
        pass

    def reset(self):
        self.position = self.default
        self.move = False
        pass
    
    def playerCollideCheck(self):
        self.boolPoint1 = self.inAreaScruber(self.engine.gameMgr.player.point1)
        self.boolPoint2 = self.inAreaScruber(self.engine.gameMgr.player.point2)
        self.boolPoint3 = self.inAreaScruber(self.engine.gameMgr.player.point3)
        self.boolPoint4 = self.inAreaScruber(self.engine.gameMgr.player.point4)

        if self.boolPoint1 or self.boolPoint2 or self.boolPoint3 or self.boolPoint4:
            return True
        else:
            return False

    def moveSet(self, pos = ogre.Vector3(0, 0, 0)):
        self.velocityTemp = ogre.Vector3(0, 0, 0)
        #print "Printing TempPos: " + str(self.tempPos)

        if (self.playerMoved == True and self.move == False): 
            if(self.collide(ogre.Vector3(self.position.x + 50, self.position.y, self.position.z)) == True):
                self.tempPos = ogre.Vector3(self.position.x + 50, self.position.y, self.position.z)
                self.heading = math.radians(0)
                self.move = True
            elif(self.collide(ogre.Vector3(self.position.x - 50, self.position.y, self.position.z)) == True):
                self.tempPos = ogre.Vector3(self.position.x - 50, self.position.y, self.position.z)
                self.heading = math.radians(180)
                self.move = True
            elif(self.collide(ogre.Vector3(self.position.x, self.position.y, self.position.z + 50)) == True):
                self.tempPos = ogre.Vector3(self.position.x, self.position.y, self.position.z + 50)
                self.heading = math.radians(270)
                self.move = True
            elif(self.collide(ogre.Vector3(self.position.x, self.position.y, self.position.z - 50)) == True):
                self.tempPos = ogre.Vector3(self.position.x, self.position.y, self.position.z - 50)
                self.heading = math.radians(90)
                self.move = True                      
        elif(self.playerMoved == True and self.move == True):
            self.node.resetOrientation()
            self.node.yaw(self.heading)
            self.speed = self.scrubVelFactor	
            self.velocityTemp.x = math.cos(-self.heading) * self.speed
            self.velocityTemp.z = math.sin(-self.heading) * self.speed
            self.velocity = ogre.Vector3(self.velocityTemp.x, 0, self.velocityTemp.z)
            self.testPosx = math.fabs(self.position.x - self.tempPos.x)
            self.testPosz = math.fabs(self.position.z - self.tempPos.z)
            if(self.collide(self.position) == False):
                self.move = False
        pass
         
    def tick(self, dt):
        self.scrubCalcBound()
        self.moveSet()
        self.position = self.position + self.velocity * dt
        self.node.position = self.position
    
        self.projectDistance = math.sqrt(pow((self.engine.gameMgr.player.pos.x - self.position.x),2) + pow((self.engine.gameMgr.player.pos.z - self.position.z), 2))

        #pow((self.engine.gameMgr.player.pos.y - self.projectilePos.y),2)

        if(self.playerCollideCheck() == True or self.projectDistance <= 10):
            self.velocityTemp = ogre.Vector3(0, 0, 0)
            self.velocityTemp.x = math.cos(-self.engine.gameMgr.player.heading) * -3000
            self.velocityTemp.z = math.sin(-self.engine.gameMgr.player.heading) * -3000
            self.engine.gameMgr.player.vel = ogre.Vector3(self.velocityTemp.x, self.engine.gameMgr.player.vel.y, self.velocityTemp.z)
            self.playerCollideCounter = 10

        if(self.playerCollideCounter > 0):
            self.playerCollideCounter -= 1

    def scrubCalcBound(self):
        self.depth = 40
        self.width = 40
        self.point1 = ogre.Vector3(self.position.x + self.width, self.position.y + 30, self.position.z) 
        self.point2 = ogre.Vector3(self.position.x, self.position.y + 30, self.position.z - self.depth)
        self.point3 = ogre.Vector3(self.position.x - self.width, self.position.y + 30, self.position.z)
        self.point4 = ogre.Vector3(self.position.x, self.position.y + 30, self.position.z + self.depth)

    def inAreaScruber(self, checkVect = ogre.Vector3(0, 0, 0)): #checkVect can be the position of the player.
        if(checkVect.x >= self.point3.x):
            if(checkVect.x <= self.point1.x):
                if(checkVect.z <= self.point4.z):
                    if(checkVect.z >= self.point2.z):
                        return True
        return False

    def collide(self, checkPos):
        self.index = len(self.engine.entityMgr.platEntList)
        for self.counter in range(0, self.index):
            self.boolPos = self.engine.entityMgr.platEntList[self.counter].inAreaPlatScrub(checkPos)
            self.bool1 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatScrub(checkPos)
            self.bool2 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatScrub(checkPos)
            self.bool3 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatScrub(checkPos)
            self.bool4 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatScrub(checkPos)

            if self.boolPos and self.bool1 and self.bool2 and self.bool3 and self.bool4:
                return True
        return False






