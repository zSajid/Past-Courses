import ogre.renderer.OGRE as ogre
import math

class Player:
	def __init__(self, engine, pos = ogre.Vector3(-100, 0, -100), vel = ogre.Vector3(0,0,0), mesh = "Player.mesh"):
		self.pos = pos
		self.mesh = mesh
		self.vel = vel
		self.sceneManager = engine.gfxMgr.sceneManager
		self.node = ''
		self.playEntity = "Player"
		self.engine = engine
		self.scaleFactor = 30
		self.heading = 0
		self.playerVelFactor = 50
		self.counter = 0
		self.jumpCount = 0
		self.defualtPos = ogre.Vector3(10000, 10100, 10000)

		#Points of the bounding box.
		self.point1 = ogre.Vector3(0, 0, 0)
		self.point2 = ogre.Vector3(0, 0, 0)
		self.point3 = ogre.Vector3(0, 0, 0)
		self.point4 = ogre.Vector3(0, 0, 0)
		self.point5 = ogre.Vector3(0, 0, 0)
		self.point6 = ogre.Vector3(0, 0, 0)
		self.defualtHeight = 3

		#Funtion Initialization Calls
		self.calcAreaPlayer(self.pos)

		#Entity Creation 
		self.ent = self.sceneManager.createEntity(self.playEntity, self.mesh)
		node = self.sceneManager.getRootSceneNode().createChildSceneNode(self.playEntity + 'node', self.pos)
		node.attachObject(self.ent)
		self.node = node
		self.node.scale(self.scaleFactor, self.scaleFactor, self.scaleFactor)

	def tick(self, dtime):
		if(self.collide() == False or self.jumpCount > 0):
			self.vel.y -= 1
		else:
			self.vel.y = 0
	
		self.pos = self.pos + self.vel * dtime
		self.node.position = self.pos	
				
		self.vel = ogre.Vector3(0, self.vel.y, 0)

		if(self.jumpCount > 0):
			self.jumpCount -= 1

		self.calcAreaPlayer(self.pos)

		self.node.resetOrientation()
		self.node.yaw(self.heading)

	#The jump mechanic for the player
	def jump(self):
		if(self.collide() == True and self.jumpCount == 0):
			self.vel.y = 400
			self.jumpCount = 100

	#This will be the q1
	def collide(self):
		self.index = len(self.engine.entityMgr.platEntList)
		for self.counter in range(0, self.index):
			self.boolPoint6 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatform(self.point6)
			self.boolPoint1 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatform(self.point1)
			self.boolPoint2 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatform(self.point2)
			self.boolPoint3 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatform(self.point3)
			self.boolPoint4 = self.engine.entityMgr.platEntList[self.counter].inAreaPlatform(self.point4)

			if self.boolPoint1 and self.boolPoint2 and self.boolPoint3 and self.boolPoint4 and self.boolPoint6:
				self.testVal = math.fabs(self.engine.entityMgr.platEntList[self.counter].position.y - self.point6.y)
				if self.testVal <= 3:				
					if(self.engine.entityMgr.platEntList[self.counter].direction == 'Y'):
						self.pos.y += 1
					return True
			
		return False

	def oneCollideCheck(self, platNum):
		self.boolPoint6 = self.engine.entityMgr.platEntList[platNum].inAreaPlatform(self.point6)
		self.boolPoint1 = self.engine.entityMgr.platEntList[platNum].inAreaPlatform(self.point1)
		self.boolPoint2 = self.engine.entityMgr.platEntList[platNum].inAreaPlatform(self.point2)
		self.boolPoint3 = self.engine.entityMgr.platEntList[platNum].inAreaPlatform(self.point3)
		self.boolPoint4 = self.engine.entityMgr.platEntList[platNum].inAreaPlatform(self.point4)

		if self.boolPoint1 and self.boolPoint2 and self.boolPoint3 and self.boolPoint4 and self.boolPoint6:
			self.testVal = math.fabs(self.engine.entityMgr.platEntList[platNum].position.y - self.point6.y)
			if self.testVal <= 3:
				return True
		
		return False
		pass

	def reset(self):
		self.pos = self.defualtPos
		self.vel = ogre.Vector3(0, 0, 0)

	def calcAreaPlayer(self, position): #leftBound and rightBound are both vectors.
		self.depth = 4    
		self.width = 2
		self.point1 = ogre.Vector3(position.x + self.depth, position.y, position.z - self.width)
		self.point2 = ogre.Vector3(position.x - self.depth, position.y, position.z - self.width)
		self.point3 = ogre.Vector3(position.x + self.depth, position.y, position.z + self.width)
		self.point4 = ogre.Vector3(position.x - self.depth, position.y, position.z + self.width)
		self.point5 = ogre.Vector3(position.x, position.y + self.defualtHeight, position.z)
		self.point6 = ogre.Vector3(position.x, position.y - self.defualtHeight, position.z)
		pass

	def inAreaPlayer(self, checkVect):
		if(checkVect.z >= self.point1.z):
			if(checkVect.z <= self.point4.z):
				if(checkVect.x >= self.point2.x):
					if(checkVect.x <= self.point3.x):
						return True
		return False
















	

