import ogre.renderer.OGRE as ogre
import math
 
class Turret:
    def __init__(self, turretNum, engine, pos = ogre.Vector3(0, 0, 0)):
        self.engine = engine
        self.default = ogre.Vector3(10000, 10000, 10000) #Vector
        self.position = self.default
        self.player = self.engine.gameMgr.player
        self.sceneManager = engine.gfxMgr.sceneManager
        self.node = ''
        self.defualtHeight = 100
        self.movement = False
        self.mesh = "sentryTurret1.mesh"
        self.turretEntity = "Turret" + str(turretNum) #Need a number passed in to create the right entity.
        self.pitch = 0
        self.yaw = 0
        self.heading = 0
        self.bulletSpeed = 300
        self.targetPoint = ogre.Vector3(0, 0, 0)
 
        #Projectile Variables
        self.projectileMesh = "cube.mesh"
        self.projectilePos = self.position
        self.projectileNode = ''
        self.projectEntity = "Projectile" + str(turretNum)
        self.inDesignatedArea = False
        self.projectileVelocity = ogre.Vector3(0,0,80)
        self.scaleFactor = 20
        self.fired = False
        self.projInArea = False
        self.checkVect = ogre.Vector3(300, 0, 300)
        self.projectDistancePlayer = 41
        self.init()
 
        #Points of the area to fire at.
        self.point1 = ogre.Vector3(0, 0, 0)
        self.point2 = ogre.Vector3(0, 0, 0)
        self.point3 = ogre.Vector3(0, 0, 0)
        self.point4 = ogre.Vector3(0, 0, 0)
        self.point5 = ogre.Vector3(0, 0, 0)
        self.point6 = ogre.Vector3(0, 0, 0)
        self.calcArea(self.targetPoint)
        
        self.projectileDistance()
        self.calcIntercept()
        self.projectileVelocity.z = math.sin(float(self.yaw)) * self.bulletSpeed
        self.projectileVelocity.x = math.cos(float(self.yaw)) * self.bulletSpeed
        self.projectileVelocity.y = math.sin(float(self.pitch)) * self.bulletSpeed
        pass
 
    def init(self):
        self.temp = self.sceneManager.createEntity(self.turretEntity, self.mesh)
        self.node = self.sceneManager.getRootSceneNode().createChildSceneNode(self.turretEntity + 'node', self.position)
        self.node.attachObject(self.temp)
        self.node.scale(self.scaleFactor, self.scaleFactor, self.scaleFactor)
         
        self.temp = self.sceneManager.createEntity(self.projectEntity, self.projectileMesh)
        self.temp.setMaterialName("Examples/Flare")
        self.projectileNode = self.sceneManager.getRootSceneNode().createChildSceneNode(self.projectEntity + 'node', self.position)
        self.projectileNode.attachObject(self.temp)
        self.projectileNode.scale(5, 5, 5)
 
    def reset(self):
        self.postion = self.default
        self.resetProjectile()
        pass

    def resetProjectile(self):
        self.projectilePos = ogre.Vector3(self.position.x, self.position.y + 50, self.position.z)
        self.projectileNode.position = self.position
        self.projectileNode.setVisible(False)
        self.projectileVelocity.z = 0
        self.projectileVelocity.x = 0
        self.projectileVelocity.y = 0
        self.fired = False
        pass

    def calcDistPlayer(self):
        self.projectDistancePlayer = math.sqrt(pow((self.engine.gameMgr.player.pos.x - self.projectilePos.x),2) + pow((self.engine.gameMgr.player.pos.z - self.projectilePos.z), 2))
     
    def fireProjectile(self):
        if(self.fired == False and self.inArea(self.player.pos) == True):
            self.projectileNode.setVisible(True)
            self.projectileVelocity.z = math.sin(float(self.yaw)) * self.bulletSpeed
            self.projectileVelocity.x = math.cos(float(self.yaw)) * self.bulletSpeed
            self.projectileVelocity.y = math.sin(float(self.pitch)) * self.bulletSpeed
            self.engine.soundMgr.playSound("customturbolaser.wav", 1)
            self.fired = True

        if(self.fired == True):
            if(self.projInArea == True and self.inArea(self.projectilePos) == False):
                self.resetProjectile()
                self.fired = False
                self.projInArea = False
        pass

    def projectileDistance(self):
        self.projectDistance = math.sqrt(pow((self.position.x - self.projectilePos.x),2) + pow((self.position.y - self.projectilePos.y),2)+ pow((self.position.z - self.projectilePos.z), 2))
 
    def tick(self, dt):        
        if(self.inArea(self.projectilePos) == True):
            self.projInArea = True

        if(self.projectDistance > 1000):
            self.resetProjectile()

        if(self.projectDistancePlayer < 40):
            self.velocityTemp = ogre.Vector3(0, 0, 0)
            self.velocityTemp.x = math.cos(-self.engine.gameMgr.player.heading) * 500
            self.velocityTemp.z = math.sin(-self.engine.gameMgr.player.heading) * 500
            self.engine.gameMgr.player.vel = ogre.Vector3(self.velocityTemp.x, self.engine.gameMgr.player.vel.y, self.velocityTemp.z)

        self.calcDistPlayer()
        self.calcArea(self.targetPoint)
        self.calcIntercept()
        self.projectileDistance()
        self.fireProjectile()
        self.node.position = self.position
        self.node.resetOrientation()
        self.node.yaw(self.heading)

        #Projectile Movement
        #self.projectilePos.y = 30 + self.position.y
        self.projectilePos = self.projectilePos + self.projectileVelocity * dt
        self.projectileNode.position = self.projectilePos
        pass
 
    def inArea(self, checkVect = ogre.Vector3(0, 0, 0)): #checkVect can be the position of the player.
        if (checkVect.y <= self.point5.y):
            if(checkVect.y >= self.point6.y):
                if(checkVect.z >= self.point1.z):
                    if(checkVect.z <= self.point4.z):
                        if(checkVect.x >= self.point2.x):
                            if(checkVect.x <= self.point3.x):                               
                                return True
 
        #print "Point is not in the Area"                       
        return False
        pass

    def calcArea(self, position): #leftBound and rightBound are both vectors.
        self.depth = 100   
        self.width = 100
        self.point1 = ogre.Vector3(position.x + self.depth, position.y, position.z - self.width)
        self.point2 = ogre.Vector3(position.x - self.depth, position.y, position.z - self.width)
        self.point3 = ogre.Vector3(position.x + self.depth, position.y, position.z + self.width)
        self.point4 = ogre.Vector3(position.x - self.depth, position.y, position.z + self.width)
        self.point5 = ogre.Vector3(position.x, self.defualtHeight, position.z)
        self.point6 = ogre.Vector3(position.x, -self.defualtHeight, position.z)
        pass
 
    def calcIntercept(self):
        self.attackPoint = self.engine.gameMgr.player.pos
        self.distance = math.sqrt(pow((self.position.x - self.attackPoint.x),2) + pow((self.position.y - self.attackPoint.y),2)+ pow((self.position.z - self.attackPoint.z), 2))
        self.attackTime = self.distance / self.bulletSpeed
        self.intX = self.engine.gameMgr.player.pos.x + (self.engine.gameMgr.player.vel.x * self.attackTime)
        self.intZ = self.engine.gameMgr.player.pos.z + (self.engine.gameMgr.player.vel.z * self.attackTime)
        self.intY = self.engine.gameMgr.player.pos.y + (self.engine.gameMgr.player.vel.y * self.attackTime)
        self.interceptPoint = ogre.Vector3(self.intX, self.intY, self.intZ)
        self.getDegrees(self.position, self.player.pos)
 
    def getDegrees(self, posA = ogre.Vector3 (0,0,0), posB = ogre.Vector3(0, 0, 0)):
        self.deltaX = posB.x - posA.x
        self.deltaZ = posB.z - posA.z
        self.deltaY = posB.y - posA.y

        if self.deltaX == 0:
            self.deltaX = 0.0001

        #yaw math
        self.yawangle = math.atan(float(self.deltaZ)/ float(self.deltaX))
        self.yawdegree = math.degrees(self.yawangle)
        self.heading = self.yawdegree

        if self.deltaX >= 0:
            if self.deltaZ >=0:
                self.degree = math.degrees(3*math.pi/2) + self.heading
            if self.deltaZ <0:
                self.degree = math.degrees(math.pi/2) + self.heading
 
        if self.deltaX < 0:
            if self.deltaZ >= 0:
                self.degree = math.degrees(3*math.pi/2) + self.heading
            if self.deltaZ < 0:
                self.degree = math.degrees(math.pi/2) + self.heading

        self.yaw = math.radians(self.yawdegree)
        self.heading = math.radians(self.degree) 








