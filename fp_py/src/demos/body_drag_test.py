'''
Created on 2012-11-14

@author: Steven
'''
import os
from runner import runner

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))   
    exit()

from fruitpunch import Scene, Sprite, PhysicsWorld, Body, BodyType,\
     Point

import random
#from fruitpunch.behaviors.drag import Drag
from fruitpunch.behaviors.body_drag import BodyDrag

class PhysicsJointScene(Scene):
    def on_init(self, ev):
        self.world = PhysicsWorld()
        self.add(self.world)
         
        self.tuqui = Sprite("tuqui.png")
        self.tuqui.top = 0
        self.tuqui.left = 300
        self.tuqui.scale(0.5, 0.5)
        self.tuqui_body = Body()
        self.tuqui_body.type = BodyType.kinematic
        
        self.tuqui.add(self.tuqui_body)
        self.add(self.tuqui)
        bd = BodyDrag(self.tuqui_body)
        bd.always_drag = False
        self.tuqui.add(bd)
        print('added tuqui to scene')
        #self.dragging = False
        
def init(runtime):
    runner.run_scene(PhysicsJointScene())
    
