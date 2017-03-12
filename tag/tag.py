#!/usr/bin/env python

# Source code distributed under the Copyright (c) 2008, John David Funge
# Original author: John David Funge (www.jfunge.com)
#
# Licensed under the Academic Free License version 3.0 
# (for details see LICENSE.txt in this directory).

from game_state import GameState
from simulator import Simulator
from gui import Gui, Keyboard
from renderer import *
from brain import *
from percepts import Percepts
from character import *

import pygame

class Constants:
    pass

def setupNPCBrain(which, percepts):
    if which == "wander":
        return BrainPeriodic(percepts, BrainWander(percepts), 1.0)
    else:
        # Define what counts as the tagged character being "near"
        near = 2.0 * Constants.radius

        # Define what counts as the tagged character being "far"
        far = 10.0 * near

        # What's the minimum time (in seconds) allowed between decisions
        minPeriod = 0.2

        # What's the maximum time (in seconds) allowed between decisions
        maxPeriod = 0.4

        return BrainConditional(
            percepts,
            Percepts.tagged,
            BrainAvoid(
                percepts,
                BrainPursue(percepts, Percepts.myNearestCharacterPosition)),
            BrainAvoid(
                percepts,
                BrainPeriodicRamp(
                    percepts,
                    Percepts.myDistanceToTagged,
                    BrainRandomize(
                        percepts,
                        BrainEvade(percepts, Percepts.taggedPosition),
                        Percepts.myDistanceToTagged,
                        near,
                        far),
                    near,
                    far,
                    minPeriod,
                    maxPeriod)))

def setupCharacters(gs, gui, kb):
    rendererNPC = RendererCharacter(Constants.npcColorName, Constants.flashColorName)
    rendererPC = RendererCharacter(Constants.pcColorName, Constants.flashColorName)

    percepts = Percepts(gs)

    tmp = zeros((util.numDim,), float)

    for i in range(Constants.numCharacters):
        brain = None
        if i == 0:
            brain = BrainPC(percepts, kb)
        else:
            brain = setupNPCBrain("default", percepts)
        c = Character(Circle(Constants.radius), brain)
        c.setPosition(vec.randomVec1(gs.worldDim, c.getPosition(), tmp))
        if i == 0:
            c.setRenderer(rendererPC)
        else:
            c.setRenderer(rendererNPC)
        gs.addCharacter(c)

def setupObstacles(gs, gui):
    r = RendererCircle(Constants.obstacleColorName, Constants.obstacleColorName)

    tmp = zeros((util.numDim,), float)

    for i in range(Constants.numObstacles):
        o = Obstacle(Circle(Constants.radius))
        o.setPosition(vec.randomVec1(gs.worldDim, o.getPosition(), tmp))
        o.setRenderer(r)
        gs.addObstacle(o)

def main(numFrames = -1):
    Constants.radius = 10.0
    Constants.numObstacles = 7
    Constants.numCharacters = 5
    Constants.worldDim = (512, 512)
    Constants.npcColorName = "green"
    Constants.pcColorName = "blue"
    Constants.flashColorName = "red"
    Constants.backgroundName = "black"
    Constants.obstacleColorName = "white"

    gs = GameState(Constants.worldDim)
    gui = Gui(gs, Constants.backgroundName)

    sim = Simulator(gs)

    kb = Keyboard()

    setupCharacters(gs, gui, kb)

    setupObstacles(gs, gui)

    clock = pygame.time.Clock()

    while True:
        gui.render(gs)
        gs.incFrame()
        kb.processEvents()
        if kb.quit:
            break
        if 0 <= numFrames and numFrames <= gs.frame:
            break
        deltaT = clock.tick(30)/1000.0
        sim.forward(deltaT)

    gui.destroyWindow()

if __name__ == "__main__":
    main()

# TODO:
# - more argument checking, especially for numbers that are supposed to be reals
# - minimize run-time object construction
# - port collisions with sides
# - enforce non-interpenetration constraint on starting position

