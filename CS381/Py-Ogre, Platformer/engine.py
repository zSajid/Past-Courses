# 381 main engine
import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS
import math
import time


class Engine(object):
	def __init__(self):
		#print "Starting the Engine!"
		self.splashbool = True
		pass

	def init(self):

		import entityMgr
		self.entityMgr = entityMgr.EntityMgr(self)
		self.entityMgr.init()
		self.keepRunning = True;
	
		import gfxMgr
		self.gfxMgr = gfxMgr.GfxMgr(self)
		self.gfxMgr.init()

		import netMgr
		self.netMgr = netMgr.NetMgr(self)
		self.netMgr.init()

		import inputMgr
		self.inputMgr = inputMgr.InputMgr(self)
		self.inputMgr.init()

		import selectionMgr
		self.selectionMgr = selectionMgr.SelectionMgr(self)
		self.selectionMgr.init()

		import controlMgr
		self.controlMgr = controlMgr.ControlMgr(self)
		self.controlMgr.init()

		import soundMgr
		self.soundMgr = soundMgr.SoundMgr(self)
		self.soundMgr.init()

		import uiMgr
		self.uiMgr = uiMgr.UIMgrs(self)
		self.uiMgr.init()

		import gameMgr
		self.gameMgr = gameMgr.GameMgr(self)
		self.gameMgr.init()

	def stop(self):
		self.gfxMgr.stop()
		self.inputMgr.stop()
		self.selectionMgr.stop()
		self.gameMgr.stop()
		self.controlMgr.stop()
		self.netMgr.stop()
		self.keepRunning = False

	def run(self):
		weu = ogre.WindowEventUtilities() # Needed for linux/mac
		weu.messagePump()                 # Needed for linux/mac

		self.oldTime = time.time()
		self.runTime = 0

		quitTime = 0

		while (self.keepRunning):
			now = time.time() # Change to time.clock() for windows
			dtime = now - self.oldTime
			self.oldTime = now

			self.entityMgr.tick(dtime)
			self.gfxMgr.tick(dtime)
			self.netMgr.tick(dtime)
			self.inputMgr.tick(dtime)
			self.selectionMgr.tick(dtime)
			self.controlMgr.tick(dtime)
			self.gameMgr.tick(dtime)
			self.soundMgr.tick(dtime)
			self.uiMgr.tick(dtime)

			self.runTime += dtime
		
			weu.messagePump()             # Needed for linux/mac
			time.sleep(0.001)
	
		#print "381 Engine exiting..."

