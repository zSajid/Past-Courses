import ogre.renderer.OGRE as ogre

class Platform:
    def __init__(self, platformNum, engine, pos = ogre.Vector3(0, 0, 0)):
        #Platform Basic Variables
        self.default = ogre.Vector3(10000, 10000, 10000) #Vector
        self.position = pos
        self.sceneManager = engine.gfxMgr.sceneManager
        self.engine = engine
        self.node = ''
        self.platformNum = platformNum
        self.platEntity = "Platform" + str(self.platformNum) #Need a number passed in to create the right entity.
        self.mesh = "Platform.mesh"
        self.scaleFactor = 30

        #Points of the bounding box.
        self.point1 = ogre.Vector3(0, 0, 0)
        self.point2 = ogre.Vector3(0, 0, 0)
        self.point3 = ogre.Vector3(0, 0, 0)
        self.point4 = ogre.Vector3(0, 0, 0)
        self.point5 = ogre.Vector3(0, 0, 0)
        self.point6 = ogre.Vector3(0, 0, 0)
        self.defualtHeight = 12

        #Movement Variables
        self.platVelFactor = 20
        self.movementCounter = 100
        self.velocity = ogre.Vector3(0, 0, 0)
        self.movement = False
        self.directionBool = False
        self.direction = 'Z' # Takes either Z, Y, X

        #Initialization Function Calls
        self.calcAreaPlatform(self.position)
        self.init()
        pass

    def init(self):
        self.ent = self.sceneManager.createEntity(self.platEntity, self.mesh)
        self.ent.setMaterialName("Examples/TextureEffect1")
        node = self.sceneManager.getRootSceneNode().createChildSceneNode(self.platEntity + 'node', self.position)
        node.attachObject(self.ent)
        self.node = node
        self.node.scale(self.scaleFactor, self.scaleFactor, self.scaleFactor)
        pass

    def reset(self):
        self.position = self.default
        self.movement = False
        self.velocity = ogre.Vector3(0, 0, 0)
    
    def moveSet(self):
        # ------------------ Z Direction Movement
        if(self.direction == 'Z'):
            if(self.directionBool == False):
                self.velocity = ogre.Vector3(0, 0, -(self.platVelFactor))
                self.movementCounter = self.movementCounter - 1
                if(self.movementCounter == -100):
                    self.directionBool = True
            
            if(self.directionBool == True):
                self.velocity = ogre.Vector3(0, 0, self.platVelFactor)
                self.movementCounter = self.movementCounter + 1
                if(self.movementCounter == 100):
                    self.directionBool = False
                
        # ------------------ Y Direction Movement
        if(self.direction == 'Y'):
            if(self.directionBool == False):
                self.velocity = ogre.Vector3(0, -(self.platVelFactor), 0)
                self.movementCounter = self.movementCounter - 1
                if(self.movementCounter == -100):
                    self.directionBool = True
            
            if(self.directionBool == True):
                self.velocity = ogre.Vector3(0, self.platVelFactor, 0)
                self.movementCounter = self.movementCounter + 1
                if(self.movementCounter == 100):
                    self.directionBool = False

        # ------------------ X Direction Movement
        if(self.direction == 'X'):
            if(self.directionBool == False):
                self.velocity = ogre.Vector3(-(self.platVelFactor), 0, 0)
                self.movementCounter = self.movementCounter - 1
                if(self.movementCounter == -100):
                    self.directionBool = True
            
            if(self.directionBool == True):
                self.velocity = ogre.Vector3(self.platVelFactor, 0, 0)
                self.movementCounter = self.movementCounter + 1
                if(self.movementCounter == 100):
                    self.directionBool = False
  
    def tick(self, dt):
        if self.movement == True:
            self.moveSet()
            self.position = self.position + self.velocity * dt
        else:
            self.velocity = ogre.Vector3(0, 0, 0)

    	self.node.position = self.position
        self.calcAreaPlatform(self.position)
        pass

    def calcAreaPlatform(self, position): #leftBound and rightBound are both vectors.
        self.depth = 50    
        self.width = 65
        self.point1 = ogre.Vector3(position.x + self.depth, position.y, position.z - self.width)
        self.point2 = ogre.Vector3(position.x - self.depth, position.y, position.z - self.width)
        self.point3 = ogre.Vector3(position.x + self.depth, position.y, position.z + self.width)
        self.point4 = ogre.Vector3(position.x - self.depth, position.y, position.z + self.width)
        self.point5 = ogre.Vector3(position.x, position.y + self.defualtHeight, position.z)
        self.point6 = ogre.Vector3(position.x, position.y - self.defualtHeight, position.z)
        pass

    def inAreaPlatform(self, checkVect = ogre.Vector3(0, 0, 0)): #checkVect can be the position of the player.
        #print "Checking Point5.y" + str(self.point5)
        #print "Checking checkVect.y" + str(checkVect.y) 
        if (checkVect.y <= self.point5.y):
            #print "Checking Point6.y" + str(self.point6)
            if(checkVect.y >= self.point6.y):
                #print "Checking Point1.z" + str(self.point1) #Changed from >=
                if(checkVect.z >= self.point1.z):
                    #print "Checking Point4.z" + str(self.point4) #Changed from <=
                    if(checkVect.z <= self.point4.z):
                        #print "Checking Point2.x" + str(self.point2)
                        if(checkVect.x >= self.point2.x):
                            #print "Checking Point3.x" + str(self.point3)
                            if(checkVect.x <= self.point3.x):
                                #print "Point is in the Area"
                                return True

        #print "Point is not in the Area"                        
        return False
        pass


    def inAreaPlatScrub(self, checkVect = ogre.Vector3(0, 0, 0)): #checkVect can be the position of the player.
        #print "Checking Point5.y" + str(self.point5)
        #print "Checking checkVect.y" + str(checkVect.y) 
	if(checkVect.z >= self.point1.z):
	    #print "Checking Point4.z" + str(self.point4) #Changed from <=
	    if(checkVect.z <= self.point4.z):
		#print "Checking Point2.x" + str(self.point2)
		if(checkVect.x >= self.point2.x):
		    #print "Checking Point3.x" + str(self.point3)
		    if(checkVect.x <= self.point3.x):
		        #print "Point is in the Area"
		        return True

        #print "Point is not in the Area"                        
        return False
        




