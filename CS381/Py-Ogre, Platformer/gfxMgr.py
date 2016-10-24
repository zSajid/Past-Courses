
import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS
import math

class ExitListener(ogre.FrameListener):
 
    def __init__(self, keyboard,gfx):
        ogre.FrameListener.__init__(self)
        self.keyboard = keyboard
        self.gfx = gfx
 
    def frameStarted(self, evt):

        self.keyboard.capture()

        if(self.keyboard.isKeyDown(OIS.KC_ESCAPE)):
            self.gfx.keepRunning = False
            return False

        return not self.keyboard.isKeyDown(OIS.KC_ESCAPE)

    def __del__(self):
        del self.renderer
        del self.system
        #del self.exitListener
        #del self.root

class GfxMgr:
    def __init__(self, gfx):
        self.gfx = gfx


    def init(self):
        self.go()
        #self.addEntities()


    def tick(self, dtime):
        self.root.renderOneFrame()

    def initBackground(self):
        self.sceneManager.setAmbientLight = 1.0,1.0,1.0
        surfaceHeight = -100
        self.sceneManager.setSkyBox (True, "FinalProject/Spacebox")

    def go(self):
        self.createRoot()
        self.defineResources()
        self.setupRenderSystem()
        self.createRenderWindow()
        self.initializeResourceGroups()
        self.setupScene()
        self.setupInputSystem()
        self.createFrameListener()
        self.initBackground()
        self.cleanUp()
 
    # The Root constructor for the ogre
    def createRoot(self):
        self.root = ogre.Root()
 
    # Here the resources are read from the resources.cfg
    def defineResources(self):
        cf = ogre.ConfigFile()
        cf.load("resources.cfg")
 
        seci = cf.getSectionIterator()
        while seci.hasMoreElements():
            secName = seci.peekNextKey()
            settings = seci.getNext()
 
            for item in settings:
                typeName = item.key
                archName = item.value
                ogre.ResourceGroupManager.getSingleton().addResourceLocation(archName, typeName, secName)
 
    # Create and configure the rendering system (either DirectX or OpenGL) here
    def setupRenderSystem(self):
        if not self.root.restoreConfig() and not self.root.showConfigDialog():
            raise Exception("User canceled the config dialog -> Application.setupRenderSystem()")
 
 
    # Create the render window
    def createRenderWindow(self):
        self.root.initialise(True, "Tutorial Render Window")
 
    # Initialize the resources here (which were read from resources.cfg in defineResources()
    def initializeResourceGroups(self):
        ogre.TextureManager.getSingleton().setDefaultNumMipmaps(5)
        ogre.ResourceGroupManager.getSingleton().initialiseAllResourceGroups()
 
    # Now, create a scene here. Three things that MUST BE done are sceneManager, camera and
    # viewport initializations
    def setupScene(self):
        self.sceneManager = self.root.createSceneManager(ogre.ST_GENERIC, "Default SceneManager")

        self.node = self.sceneManager.getRootSceneNode().createChildSceneNode('CamNode1', (400, 300, 400))
        self.node.yaw(0)

        #Debug Camera
        self.camera = self.sceneManager.createCamera("Camera")
        self.Camnode = self.node.createChildSceneNode('PitchNode1', (400, 300, 400))
        self.Camnode.attachObject(self.camera)
        self.camera.nearClipDistance = 1
        self.Camnode.yaw(0)
        self.Camnode.pitch(0)

        #Player Camera Creation
        self.playerCamera = self.sceneManager.createCamera("PlayerCamera")
        self.playerCam = self.sceneManager.getRootSceneNode().createChildSceneNode("PlayCam",(100, 100, 100))
        self.playerCam.attachObject(self.playerCamera)
        self.playerCamera.nearClipDistance = 6
        self.playerCamera.pitch(math.radians(-20))

        #OverheadCamera
        self.overheadCamera = self.sceneManager.createCamera("overHeadCamera")
        self.overHeadCam = self.sceneManager.getRootSceneNode().createChildSceneNode("OverHeadCam",(400, 300, 400))
        self.overHeadCam.attachObject(self.overheadCamera)
        self.overheadCamera.nearClipDistance = 1

        #ViewPort
        self.viewPort = self.root.getAutoCreatedWindow().addViewport(self.camera) #Change to PlayerCam


    # here setup the input system (OIS is the one preferred with Ogre3D)
    def setupInputSystem(self):
        self.renderWindow = self.root.getAutoCreatedWindow()
        windowHnd = self.renderWindow.getCustomAttributeUnsignedLong("WINDOW")

        paramList = [("WINDOW", str(windowHnd))]
        t = [("x11_mouse_grab", "false"), ("x11_mouse_hide", "false")]
        paramList.extend(t)

        self.inputManager = OIS.createPythonInputSystem(paramList)
 
        # Now InputManager is initialized for use. Keyboard and Mouse objects
        # must still be initialized separately
        try:
            self.keyboard = self.inputManager.createInputObjectKeyboard(OIS.OISKeyboard, True)
            self.mouse = self.inputManager.createInputObjectMouse(OIS.OISMouse, True)
        except Exception, e:
            raise e
 
    # Create the frame listeners
    def createFrameListener(self):
        self.exitListener = ExitListener(self.keyboard,self.gfx)
        self.root.addFrameListener(self.exitListener)
        pass

 
    # In the end, clean everything up (= delete)
    def cleanUp(self):
        pass
        #self.inputManager.destroyInputObjectKeyboard(self.keyboard)
        #self.inputManager.destroyInputObjectMouse(self.mouse)
        #OIS.InputManager.destroyInputSystem(self.inputManager)
        #self.inputManager = None
'''
    def addEntities(self):

        from vector import MyVector

        x = 0;
        i = 0;
        for entType in self.gfx.entityMgr.entTypes:
            ent = self.gfx.entityMgr.createEnt(entType, pos = MyVector(x, 0, 0))
            gfxNode = self.createGent(ent.uiname + str(i), ent.mesh, ent.pos, ent.heading)
            ent.node = gfxNode
            x += 300
            i += 1


    def createGent(self, mid, mmesh, mpos, myaw):
        e = self.sceneManager.createEntity(mid, mmesh)
        fileRoot = mmesh.split('.')
        materialName = fileRoot[0]+".material"
        node = self.sceneManager.getRootSceneNode().createChildSceneNode(mid + 'node', mpos)
        node.attachObject(e)
        return node
'''








