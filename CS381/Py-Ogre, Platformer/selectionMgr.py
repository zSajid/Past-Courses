import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS

class secLi(ogre.FrameListener):
 
	def __init__(self, keyboard, engine):
		ogre.FrameListener.__init__(self)
		self.Keyboard = keyboard
		self.engine = engine
		self.toggle = 0 

	def frameStarted(self, evt):
		'''
		import utils
		selectedEnt = self.gfx.entityMgr.selectedEnt

		if self.toggle >= 0:
			self.toggle -= evt.timeSinceLastFrame
 
		if self.toggle < 0 and self.Keyboard.isKeyDown(OIS.KC_TAB):
			# Update the toggle timer.
			self.toggle = 0.1
			ent = self.gfx.entityMgr.selectedEnt
			ent.node.showBoundingBox(False)
			ent = self.gfx.entityMgr.selectNextEnt()

			print "FrameListener: Selected: ", str(ent)
			ent.node.showBoundingBox(True)


		'''
		return True
		pass


class SelectionMgr:
	def __init__(self, engine):
		self.engine = engine

	def init(self):
		pass


	def reset(self):
		pass

	def tick(self, dtime):
		pass

