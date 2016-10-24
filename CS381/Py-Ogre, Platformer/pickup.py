import ogre.renderer.OGRE as ogre
import sys, pygame, pygame.mixer
from pygame.locals import *

#This class does not need physics 
class pickUp:
	#This class will just have a position along with id
	def __init__(self, id, engine, pos = ogre.Vector3(0,0,0), mesh = "cube.mesh"):
		self.id = id
		self.engine = engine
		self.sceneManager = engine.gfxMgr.sceneManager
		self.pos = pos
		self.mesh = mesh
		self.pickEnt = "Pick" + str(self.id) #Need a number passed in to create the right entity.
		self.defualtPos = ogre.Vector3(1000, 1000, 1000)
		self.ent = self.sceneManager.createEntity(self.pickEnt, self.mesh)
		node = self.sceneManager.getRootSceneNode().createChildSceneNode(self.pickEnt + 'node', self.pos)
		node.attachObject(self.ent)
		self.node = node
		self.node.scale(5, 5, 5)

	def  move(self, pos = ogre.Vector3(0,-10000,0)):
		self.pos = pos		

	def check(self, pos):#This class will detect if the player position matches with the pickup Item
		if((self.pos.x+15> pos.x) and (self.pos.x-15 < pos.x)):
			if((self.pos.y + 30 > pos.y) and (self.pos.y-30 < pos.y)):
				if((self.pos.z + 15 > pos.z) and (self.pos.z -15 < pos.z)):
					self.engine.soundMgr.playSound("sfx_pick.wav", 1) 
					self.move(ogre.Vector3(-100000,-10000,0))
					self.node.position =  self.pos
					return 1 #This will return the item as been collected to the file
		return 0
		
	def tick(self, dt):
		self.node.position = self.pos
		pass

	def reset(self):
		self.pos = self.defualtPos

