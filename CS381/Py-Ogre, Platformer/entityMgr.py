import ogre.renderer.OGRE as ogre

class EntityMgr:

	def __init__(self, gfx):
		#print "Creating the Entity Manager Class \n"
		self.gfx = gfx
		self.defualtVal = ogre.Vector3(10000, 10000, 10000)
		
		#Platform Variables
		self.platEntList = []

		#Scruber Variables
		self.scrubEntList = []

		#Pickup Variables
		self.pickEntList = []

		#Turret Variables
		self.turretEntList = []

		#Player Vairables
		self.player = ''
	
	def init(self):
		pass

	def tick(self, dtime):
		pass
