import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS
import player
import math
import pygame

class movLi(ogre.FrameListener):
	def __init__(self, keyboard, engine):
		ogre.FrameListener.__init__(self)
		self.Keyboard = keyboard
		self.engine = engine
		self.toggle = 0 
		self.leftCounter = 0
		self.rightCounter = 0
		self.playerVelFactor = 50
		self.velocityTemp = ogre.Vector3(0,0,0)
		self.cameraCounter = 0
		self.playerCamHeading = 0

		self.camChanged = 0 # This is to switch the cameras around and base code around it
		#0 means free camera, 1 means first person, and 2 means overhead

		self.xAxis = 0
		self.yAxis = 0

		self.buttonY = 0
		self.buttonA = 0
		self.startButton = 0
		self.backButton = 0

        '''
		pygame.joystick.init()
		if pygame.joystick.get_count > 0:
			self.joystick = pygame.joystick.Joystick(0)
			self.joystick.init()
			self.joystickBool = True
        '''

	def frameStarted(self, evt):
		self.Keyboard.capture()	

		'''
		pygame.event.get()

		if self.joystickBool:
			self.xAxis = self.joystick.get_axis(0)
			self.yAxis = self.joystick.get_axis(1)
			self.buttonA = self.joystick.get_button(0)
			self.buttonY = self.joystick.get_button(3)
			self.startButton = self.joystick.get_button(7)
			self.backButton = self.joystick.get_button(6)

		#quit
		if self.backButton == 1:
			self.engine.keepRunning = False
		'''

		# Speed Up
		if self.Keyboard.isKeyDown(OIS.KC_W):
			self.speed = self.playerVelFactor		
			self.velocityTemp.x = math.cos(-self.engine.gameMgr.player.heading) * self.speed
			self.velocityTemp.z = math.sin(-self.engine.gameMgr.player.heading) * self.speed
			self.engine.gameMgr.player.vel = ogre.Vector3(self.velocityTemp.x, self.engine.gameMgr.player.vel.y, self.velocityTemp.z)

		# Slow down
		if self.Keyboard.isKeyDown(OIS.KC_S):
			self.speed = self.playerVelFactor		
			self.velocityTemp.x = math.cos(-self.engine.gameMgr.player.heading) * -self.speed
			self.velocityTemp.z = math.sin(-self.engine.gameMgr.player.heading) * -self.speed
			self.engine.gameMgr.player.vel = ogre.Vector3(self.velocityTemp.x, self.engine.gameMgr.player.vel.y, self.velocityTemp.z)

		# Turn Left.
		if self.Keyboard.isKeyDown(OIS.KC_A):
			if self.leftCounter == 0:
				self.engine.gameMgr.player.heading += math.radians(5)
				if(self.engine.gameMgr.player.heading == math.radians(360)):
					self.engine.gameMgr.player.heading == math.radians(0)

				self.leftCounter = 3
			pass

		# Turn Right.
		if self.Keyboard.isKeyDown(OIS.KC_D):
			if self.rightCounter == 0:
				self.engine.gameMgr.player.heading -= math.radians(5)
				if(self.engine.gameMgr.player.heading == math.radians(0)):
					self.engine.gameMgr.player.heading == math.radians(360)

				self.rightCounter = 3
			pass

		if self.Keyboard.isKeyDown(OIS.KC_SPACE):
			self.engine.gameMgr.player.jump()
			pass

		if self.Keyboard.isKeyDown(OIS.KC_NUMPAD0):
			self.engine.gfxMgr.camera.pitch = 0
			self.engine.gfxMgr.camera.lookAt(self.engine.gameMgr.player.pos)
			pass		
			

		#This is to change the second camera position and overall attach a different camera
		if self.Keyboard.isKeyDown(OIS.KC_TAB):
			if (self.cameraCounter == 0):
				#Overhead Camera
				if(self.camChanged == 0):
					self.engine.gfxMgr.viewPort.setCamera(self.engine.gfxMgr.overheadCamera)
					
					self.engine.gfxMgr.overHeadCam.position = ogre.Vector3(self.engine.gameMgr.player.pos.x - 500, self.engine.gameMgr.player.pos.y + 400, self.engine.gameMgr.player.pos.z + 500)

					self.engine.gfxMgr.overheadCamera.lookAt(float(self.engine.gameMgr.player.pos.x), float(self.engine.gameMgr.player.pos.y), float(self.engine.gameMgr.player.pos.z))

					self.cameraCounter = 10
					self.camChanged = 1

				elif(self.camChanged == 1):
					#Player Camera
					self.engine.gfxMgr.viewPort.setCamera(self.engine.gfxMgr.playerCamera)

					self.engine.gfxMgr.playerCam.position = ogre.Vector3(self.engine.gameMgr.player.pos.x, self.engine.gameMgr.player.pos.y + 40, self.engine.gameMgr.player.pos.z)

					self.engine.gfxMgr.playerCam.resetOrientation()
					self.engine.gfxMgr.playerCam.yaw(ogre.Degree(math.degrees(self.engine.gameMgr.player.heading)-90))

					self.camChanged = 0
					self.cameraCounter = 10

				'''
				#Debug Camera
				elif(self.camChanged == 100):
					self.engine.gfxMgr.viewPort.setCamera(self.engine.gfxMgr.camera)

					self.engine.gfxMgr.camera.lookAt(float(self.engine.gameMgr.player.pos.x), float(self.engine.gameMgr.player.pos.y), float(self.engine.gameMgr.player.pos.z))

					self.camChanged += 1
					self.cameraCounter = 10
				'''
				
		if self.leftCounter > 0:
			self.leftCounter -= 1

		if self.rightCounter > 0:
			self.rightCounter -= 1

		if self.cameraCounter > 0:
			self.cameraCounter -= 1

		return True
		pass


class ControlMgr:

	def __init__(self, engine):
		self.engine = engine
	
	def init(self):		
		self.keyboard = self.engine.gfxMgr.keyboard
		self.camera = self.engine.gfxMgr.camera

		self.moveList = movLi(self.keyboard, self.engine)
		self.engine.gfxMgr.root.addFrameListener(self.moveList)

	def updateCameras(self):
		self.engine.gfxMgr.playerCam.position = ogre.Vector3(self.engine.gameMgr.player.pos.x, self.engine.gameMgr.player.pos.y + 40, self.engine.gameMgr.player.pos.z)  

		self.engine.gfxMgr.overHeadCam.position = ogre.Vector3(self.engine.gameMgr.player.pos.x - 500, self.engine.gameMgr.player.pos.y + 400, self.engine.gameMgr.player.pos.z + 500)

		self.engine.gfxMgr.playerCam.resetOrientation()
		self.engine.gfxMgr.playerCam.yaw(ogre.Degree(math.degrees(self.engine.gameMgr.player.heading)-90))	

	def tick(self, dtime):
		pass

