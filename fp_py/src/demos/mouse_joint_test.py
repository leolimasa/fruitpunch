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
    MouseJoint, Point
import os

import random
from fruitpunch.behaviors.drag import Drag

class PhysicsJointScene(Scene):
    def on_init(self, ev):
        self.world = PhysicsWorld()
        self.add(self.world)
 
        self.ground = Sprite("ground.png")
        self.ground.top = 500
        self.ground.left = 20
        self.ground.scale(1.5, 0.5)
        self.ground.add(Body(BodyType.static))
        
        self.tuqui = Sprite("tuqui.png")
        self.tuqui.top = -300
        self.tuqui.left = 300
        self.tuqui.scale(0.5, 0.5)
        self.tuqui_body = Body()
        self.tuqui.add(self.tuqui_body)
        
        self.add(self.ground)
        print('added ground to scene')
        self.add(self.tuqui)
        print('added tuqui to scene')
    
        self.dragging = False
        
        self.tuqui.listen({"pointer_up": self.on_tuqui_up})
        self.tuqui.listen({"pointer_down": self.on_tuqui_down})
        
    def on_tuqui_up(self, e):
        self.world.remove(self.mj)
        self.dragging = False
        print("up")
    
    def on_tuqui_down(self, e):
        # construct this bitch and add to the world
        self.mj = MouseJoint(self.ground, self.tuqui)
        self.world.add(self.mj)
        self.dragging = True
        print("down")
        
    def on_render(self, e):
        if not self.dragging:
            return
        
        self.mj.update(self.scene.pointer)
        
def init(runtime):
    runner.run_scene(PhysicsJointScene())