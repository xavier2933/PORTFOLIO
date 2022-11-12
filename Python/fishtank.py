import random, sys, time

try:
    import bext
except:
    print("bext not here")
    sys.exit()

width, height = bext.size()
width -= 1
fps = 8
num_kelp = 3
num_fish = 50
num_bubblers = 6

fishtypes = [
{'right': ['><???>'],
'left': ['<???><']},
{'right': ['>||>'], 'left': ['<||<']},
{'right': ['>))>'], 'left': ['<((<']},
{'right': ['>||o', '>||.'], 'left': ['o||<', '.||<']},
{'right': ['>))o', '>)).'], 'left': ['o((<', '.((<']},
{'right': ['>-==>'], 'left': ['<==-<']},
{'right': ['><>'], 'left': ['<><']},
{'right': ['><)))*>'], 'left': ['<*(((><']},
{'right': ['}-(()>'], 'left': ['<())-{']},
{'right': [']-<)))b>'], 'left': ['<d(((>-[']},
{'right': ['><===>'], 'left': ['<===><']},
{'right': ['><XXX>'], 'left': ['<XXX><']},
{'right': ['><++>'], 'left': ['<++><']},
]

longestfish = 15

leftedge = 0
rightedge = width - 1 - longestfish
topedge = 0
bottomedge = height - 2

def main():
    global fishes, bubblers, bubbles, kelp, step

    bext.bg('blue')
    bext.clear()

    fishes = []
    for i in range (num_fish):
        fishes.append(generatefish())

    bubblers = []
    for i in range (num_bubblers):
        bubblers.append(random.randint(leftedge, rightedge))

    bubbles = []

    kelps = []
    for i in range (num_kelp):
        kelpx = random.randint(leftedge, rightedge)
        kelp = {'x': kelpx, 'segments': []}

        for i in range(random.randint(6, height - 1)):
            kelp['segments'].append(random.choice(['(', ')']))
        kelps.append(kelp)

    step = 1
    while True:

        simulateAquarium()
        drawAquarium()
        time.sleep(1/fps)
        clearAquarium()
        step += 1

def getRandomColor():
    return random.choice(( 'red', 'green', 'yellow', 'cyan', 'white'))

def generatefish():
    fishType = random.choice(fishtypes)
    fishLength = len(fishType['right'][0])
    colorPattern = random.choice(('random', 'head-tail', 'single'))
    if colorPattern == 'random':
        colors = []
        for i in range (fishLength):
            colors.append(getRandomColor())
    if colorPattern == 'single' or colorPattern == 'head-tail':
        colors = [getRandomColor()] * fishLength
    if colorPattern == 'head-tail':
        headTailColor = getRandomColor()
        colors[0] = headTailColor
        colors[-1] = headTailColor

    fish = {'right':            fishType['right'],
            'left':             fishType['left'],
            'colors':           colors,
            'hSpeed':           random.randint(1,6),
            'vspeed':           random.randint(5,15),
            'timeToHDirChange':  random.randint(40,100),
            'timeToVDirChange':  random.randint(2,20),
            'goingRight':       random.choice([True, False]),
            'goingDown':        random.choice([True, False])}

    fish['x'] = random.randint(0, width - 1 - longestfish)
    fish['y'] = random.randint(0, height - 2)
    return fish

def simulateAquarium():
    global fishes, bubblers, bubbles, kelp, step, kelps
    for fish in fishes:

        if step % fish['hSpeed'] == 0:
            if fish['goingRight']:
                if fish['x'] != rightedge:
                    fish['x'] += 1
                else:
                    fish['goingRight'] = False
                    fish['colors'].reverse()
            else:
                if fish['x'] != leftedge:
                    fish['x'] -= 1
                else:
                    fish['goingRight'] = True
                    fish['colors'].reverse()

        fish['timeToHDirChange'] -= 1
        if fish['timeToHDirChange'] == 0:
            fish['timeToHDirChange'] = random.randint(10,60)
            fish['goingRight'] = not fish['goingRight']

        if step % fish['vspeed'] == 0:
            if fish['goingDown']:
                if fish['y'] != bottomedge:
                    fish['y'] += 1
                else:
                    fish['goingDown'] = False

            else:
                if fish['y'] != topedge:
                    fish['y'] -= 1
                else:
                    fish['goingDown'] = True

        fish['timeToVDirChange'] -= 1
        if fish['timeToVDirChange'] == 0:
            fish['timeToVDirChange']  = random.randint(2,20)
            fish['goingDown'] = not fish['goingDown']

    for bubbler in bubblers:
        if random.randint(1,5) == 1:
            bubbles.append({'x': bubbler, 'y': height -2})

    for bubble in bubbles:
        diceRoll = random.randint(1,6)
        if (diceRoll == 1) and (bubble['x'] != leftedge):
            bubble['x'] -= 1
        elif (diceRoll == 2) and (bubble['x'] != rightedge):
            bubble['x'] += 1

        bubble['y'] -= 1

    for i in range(len(bubbles) -1, -1, -1):
        if bubbles[i]['y'] == topedge:
            del bubbles[i]

#    for kelp in kelp:
#        for i, kelpSegment in enumerate(kelp['segments']):
##            if random.randint(1,20) == 1:
#                if kelpSegment == '(':
#                   kelp['segments'][i] = ')'
#                elif kelpSegment == ')':
#                    kelp['segments'][i] = '('

def drawAquarium():

    global fishes, bubblers, bubbles, kelp, step

    bext.fg('white')
    bext.goto(0,0)
    print('Fish Tank, ctrl-c to quit', end='')

    bext.fg('white')
    for bubble in bubbles:
        bext.goto(bubble['x'], bubble['y'])
        print(random.choice(('o', '0')), end='')

    for fish in fishes:
        bext.goto(fish['x'], fish['y'])

        if fish['goingRight']:
            fishText = fish['right'][step %len(fish['right'])]
        else:
            fishText = fish['left'][step % len(fish['left'])]

        for i, fishPart in enumerate(fishText):
            bext.fg(fish['colors'][i])
            print(fishPart, end='')

    #bext.fg('green')
#    for kelp in kelps:
    #    for i, kelpSegment in enumerate(kelp['segments']):
    #        if kelpSegment == '(':
    #            bext.goto(kelp['x'], bottomedge - i)
    #        elif kelpSegment == ')':
    #            bext.goto(kelp['x'] + 1, bottomedge - i)
    #        print(kelpSegment, end='')

    bext.fg('yellow')
    bext.goto(0, height - 1)
    print(chr(9617), end='')

    sys.stdout.flush()

def clearAquarium():
    global fishes, bubblers, bubbles, kelps
    for bubble in bubbles:
        bext.goto(bubble['x'], bubble['y'])
        print(' ', end='')

    for fish in fishes:
        bext.goto(fish['x'], fish['y'])
        print(' ' * len(fish['left'][0]), end='')

#    for kelp in kelps:
    #    for i, kelpSegment in enumerate(kelp['segments']):
    #        bext.goto(kelp['x'], height -2 -i)
    #        print(' ', end='')

    sys.stdout.flush()

main()
