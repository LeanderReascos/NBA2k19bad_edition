import pygame
import sys
import random

path = "libs\\MUSICAS\\"

def pmusic(pos,nmusics,files):
    pygame.init()
    pygame.mixer.init()
    clock = pygame.time.Clock()
    pygame.mixer.music.load(path+files[pos])
    pygame.mixer.music.play()
    aux = 0;
    while pygame.mixer.music.get_busy():
       #print("Playing...")
        #if aux % 2 == 0:
        readkey(path+".commands",pos,nmusics,files)
        clock.tick(1)
        #aux+=1
    nextMusic(pos,nmusics,files)

def readkey(keys,pos,nmusics,files):
     f = open(keys,"r")
     lin = f.readlines()
     for x in lin:
         if x == "pause":
               pygame.mixer.music.pause()
         elif x == "play":
              pygame.mixer.music.unpause()
         elif x == "stop":
              stopmusic()
         elif x == "next":
              nextMusic(pos,nmusics,files)
         elif x == "before":
              beforeMusic(pos,nmusics,files)
     f.close()
def stopmusic():
    pygame.mixer.music.stop()
    sys.exit()

def psound(file):
    pygame.init()
    pygame.mixer.init()
    clock = pygame.time.Clock()
    crash_sound = pygame.mixer.Sound(file)
    crash_sound.play()
    pygame.mixer.music.stop()
    pygame.event.wait()

def nextMusic(pos,nmusics,files):
    if pos == nmusics:
        pos = 0
    else:
        pos +=  1
    f = open(path+".commands","w")
    f.write("play")
    f.close()
    randomPlay(pos,nmusics,files)

def beforeMusic(pos,nmusics,files):
    if pos == 0:
        pos = nmusics
    else:
        pos -=  1
    f = open(path+".commands","w")
    f.write("play")
    f.close()
    randomPlay(pos,nmusics,files)

def randomPlay(pos,nmusics,files):
    pmusic(pos,nmusics,files)

def getmixerargs():
    pygame.mixer.init()
    freq, size, chan = pygame.mixer.get_init()
    return freq, size, chan


def initMixer():
    BUFFER = 3072  # audio buffer size, number of samples since pygame 1.8.
    FREQ, SIZE, CHAN = getmixerargs()
    pygame.mixer.init(FREQ, SIZE, CHAN, BUFFER)


initMixer()
files = ["m.mp3","m1.mp3","m2.mp3","m3.mp3","m4.mp3","m5.mp3"]
random.shuffle(files)
pos = 0
nmusics = 5
randomPlay(pos,nmusics,files)

   
    
