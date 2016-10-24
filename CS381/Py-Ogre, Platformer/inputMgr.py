import ogre.io.OIS as OIS
import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS

class CamListener(ogre.FrameListener, OIS.MouseListener):
	def __init__(self, camera, keyboard, mouse, engine):
		ogre.FrameListener.__init__(self)
		OIS.MouseListener.__init__(self)

		camera.lookAt(0,0,0)
		self.cam = camera.parentSceneNode.parentSceneNode
		self.cam.rotate = 0.01
		self.move = 650
		self.keyboard = keyboard
		self.rotate = 0.10
		self.mouse = mouse 
		self.mouseDown = False
		self.engine = engine

	def frameStarted(self, evt):
		self.keyboard.capture()
		self.mouse.capture()

		transVector = ogre.Vector3(0, 0, 0)
		# Move Forward.
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD8):
		   transVector.z -= self.move
		# Move Backward.
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD2):
			transVector.z += self.move
		# Strafe Left.
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD4):
			transVector.x -= self.move
		# Strafe Right.
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD6):
		   transVector.x += self.move
		# Move Up.
		if self.keyboard.isKeyDown(OIS.KC_PGUP):
			transVector.y += self.move
		# Move Down.
		if self.keyboard.isKeyDown(OIS.KC_PGDOWN):
			transVector.y -= self.move

		#change the yaw based on these two buttons
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD7):
			self.cam.yaw(ogre.Degree(-self.rotate * -30).valueRadians())

		if self.keyboard.isKeyDown(OIS.KC_NUMPAD9):
			self.cam.yaw(ogre.Degree(-self.rotate * 30).valueRadians())

		#Change pitch based on these buttons
		if self.keyboard.isKeyDown(OIS.KC_NUMPAD1):
			self.cam.pitch(ogre.Degree(-self.rotate * 20).valueRadians())

		if self.keyboard.isKeyDown(OIS.KC_NUMPAD3):
			self.cam.pitch(ogre.Degree(-self.rotate * -20).valueRadians())

		self.cam.translate(self.cam.orientation * transVector * evt.timeSinceLastFrame)

		self.mouseDragged(evt)

		return True


	def mouseDragged(self, frameEvent):
		# Rotate the camera.
		ms = self.mouse.getMouseState()
		if ms.buttonDown(OIS.MB_Right):
			self.cam.yaw(ogre.Degree(-self.rotate
				* ms.X.rel).valueRadians())
			self.cam.getChild(0).pitch(ogre.Degree(-self.rotate
				* ms.Y.rel).valueRadians())

	def __del__(self):
		del self.renderer
		del self.system
		del self.CamListener
		del self.root


class InputMgr:
	def __init__(self, engine):
		self.engine = engine
		pass

	def init(self):
		#print "Creating the Inpput Manager Class \n"
		self.keyboard = self.engine.gfxMgr.keyboard
		self.camera = self.engine.gfxMgr.camera
		self.mouse = self.engine.gfxMgr.mouse


		self.camListener = CamListener(self.camera,self.keyboard, self.mouse, self.engine)
		self.engine.gfxMgr.root.addFrameListener(self.camListener)

	def tick(self, dtime):
		pass

 
 
