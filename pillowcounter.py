
from PIL import Image, ImageEnhance  #use pillow
        
im = Image.open('verticallinefried.jpg', 'r') #open test image
mode = im.mode  
height, width = im.size #get image size
pixelmap = im.load() #create a map of all pixels

x = 0
y = 0
g = 50 #green pixel values
b = 50 #blue pixel values
w = width/3
h = height/3

totalrows, topr_rows, topmrows, toplrows, midlrows, midmrows, midr_rows, botr_rows, botm_rows, botlrows, top, middle, bottom = [0]*13
rows = 0
print(width)
print(height)
firstpix = pixelmap[0,0] #get the first pixel
print(firstpix)

def gostraight():
    if midr_rows > 0 and midlrows > 0 and midmrows > 0:
        print("go in previous direction")
        return
  
    if midlrows > 0: # these are also switched (l and r)
        print("go right")
        return
    if midmrows > 0:
        print("go left")
        return

def godown2():
    print("STOP")
    if botm_rows > 0: # this is bottom, no clue why its switched
        print(" go down")
    if botm_rows == 0: 
        gostraight()

for y in range(0, height):        #total
    for x in range(0, width):
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            totalrows +=1
            break

for y in range(0, int(h)):        #top left 
    for x in range(0, int(w)):
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            toplrows +=1
            break
    for x in range(int(w), 2*int(w)): #top mid
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            topmrows +=1
            break
    for x in range(2*int(w), width): #top right
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            topr_rows +=1
            break

for y in range(int(h), 2*int(h)):        #mid left 
    for x in range(0, int(w)):
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            midlrows +=1
            break
    for x in range(int(w), 2*int(w)): #mid mid
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            midmrows +=1
            break
    for x in range(2*int(w), width): #mid right
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            midr_rows +=1
            break

for y in range(2*int(h), height):        #bottom left 
    for x in range(0, int(w)):
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            botlrows +=1
            break
    for x in range(int(w), 2*int(w)): #bottom mid
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            botm_rows +=1
            break
    for x in range(2*int(w), width): #bottom right
        pixel = pixelmap[y,x]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        if green < g and blue < b:  # need to adjust these parameters per image
            botr_rows +=1
            break
    
if totalrows < int(h):
    gostraight()



if totalrows > int(h):   #controls going down
    if botlrows > 0 or botr_rows > 0:
        print("slow down")
    else:
        godown2()
    
    
    #if topmrows > 10 and midlrows > 10:
      #  print('go left')


if topmrows > 20 and midmrows < (int(h) / 2):
    print('stop')
  
        
        
        
#for x in range(width/2):
   # for y in range(height/2):   
print(totalrows)





    
#pix_val = list(im.getdata())
#print(pix_val)
