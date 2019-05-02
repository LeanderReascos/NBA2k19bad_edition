from moviepy.editor import *
import pygame
import os
path = "libs\\VIDEOS\\"

def playVideo(video):
	pygame.display.set_caption('NBA2K19_BadEdition')

	clip = VideoFileClip(video)
	clip.preview()

	pygame.quit()

f = open(path+".videos","r")
lin = f.readlines()
for x in lin:
	try:
		playVideo(path+x+".mp4")
	except Exception as e:
		playVideo(path+"exellent.mp4")
	
f.close()
