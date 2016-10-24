import sys, pygame, pygame.mixer
from pygame.locals import *
 
class SoundMgr:
    def __init__(self, engine):
        self.engine = engine    #Connects the engine 
        self.soundsQueue = [] #This will add a list of sounds to play in the game
 
        self.playPickUpSong = False
        self.currentSound = ""
 
    def init(self):
        pygame.mixer.init() #This initializes the pygame mixer and it's files
        pygame.mixer.pre_init(44100,-16,2,2048)
        pygame.init() #This initializes pygame itself

    def tick(self, dt):
        pass
 
    #This function just stops the song
    def stop(self, checkValue):
        if(checkValue == 1):
            pygame.mixer.Sound.stop(self.soundsQueue.pop()) #This stops the first song that entered the queue

        if(checkValue == 0):
            pass
 
        if(checkValue == 3):
            for i in range(len(self.soundsQueue)):
				pygame.mixer.Sound.stop(self.soundsQueue.pop())
		
     
    #This function basically plays the song that is needed
    #Name is a string that takes in what song needs to be played
    #numberOfTimes is the number of times a song will be played, and it can range from 1 to 50 or 5,000.
    def playSound(self, name, numberOfTimes): 
        self.currentSound = pygame.mixer.Sound(name)    
        self.soundsQueue.append(self.currentSound)
        pygame.mixer.Sound.play(self.currentSound, numberOfTimes)
     

'''
class SoundMgr:
    def __init__(self, engine):
        self.engine = engine	#Connects the engine  
	self.soundName = "Y.wav" #Is the string of the file to play
	self.queue = ["R.wav", "Chiptune_Downtempo_Funk_Party.wav"] #This is the list of songs to play
	self.index = 1

    def init(self):
        pygame.init() #This initializes the pygame 
	pygame.display.set_mode((2,2)) #This sets the window size

	pygame.mixer.music.load(self.queue[self.index]) #This loads the first song
	pygame.mixer.music.play(10000) #It plays it 10,000 times, basically loops it 10,0000 times

    def tick(self, dt):
	#This line of code will play anything after the initial 10000 Y.wav play
	pygame.mixer.music.queue(self.queue[self.index]) #This loops to whatever the queue has next
 

    def stop(self):
        pass
'''
