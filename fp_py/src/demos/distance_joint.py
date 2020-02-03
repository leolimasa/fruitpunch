'''
Created on 2012-10-28

@author: Steven
'''

import os
from runner import runner

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))   
    exit()

from fruitpunch import Scene, Sprite, PhysicsWorld, Body, BodyType,\
    DistanceJoint
import os

import random
from fruitpunch.behaviors.drag import Drag

class PhysicsJointScene(Scene):
    def on_init(self, ev):
        world = PhysicsWorld()
        self.add(world)
 
        pedoA = Sprite("tuqui.png")
        pedoA.top = -100
        pedoA.left = 0
        pedoA.scale(0.5, 0.5)
        pedoA.add(Body(BodyType.static))
        
        pedoB = Sprite("tuqui.png")
        pedoB.top = -300
        pedoB.left = 300
        pedoB.scale(0.5, 0.5)
        pedoB_body = Body()
        pedoB.add(pedoB_body)
        pedoB_body.linear_damping = .02
        
        dj = DistanceJoint(pedoA, pedoB)
        print("created distance Joint")
        
        self.add(pedoA)
        print('added pedoA to scene')
        self.add(pedoB)
        print('added pedoB to scene')
        world.add(dj)
        
        #print('added distanceJoint to world')
        
        #event(self, "post_render", self.on_frame)
def init(runtime):
    runner.run_scene(PhysicsJointScene())  
    