'''
Created on 2012-08-19

@author: leo
'''
from runner import runner
import os
import pydevd

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))
    exit()

from fruitpunch import Scene, Sprite, PhysicsWorld, Body, Point,\
    Text, Color, BodyType
import random
from fruitpunch.behaviors.drag import Drag

class PhysicsScene(Scene):
    def on_init(self, e):
        #pydevd.settrace()
        
        world = PhysicsWorld()
        world.pixel_size = 20
        self.add(world)
        
        ground = Sprite("ground.png")
        ground.top = 400
        ground.left = 0
        ground.name = "GROUND";
        self.add(ground)
        ground.add(Body(BodyType.static))
        
        ipod = Sprite("orange.png")
        ipod.top = 300
        ipod.left = 100
        ipod.name = "ORANGE"
        self.ipod_body = Body()
        self.add(ipod)
        ipod.add(self.ipod_body)
        
        target = Sprite("blue.png")
        target.top = 100
        target.left = 0
        target.name = "BLUE"
        self.target_body = Body(BodyType.kinematic)
        self.target = self.add(target)
        target.add(self.target_body)
        
        self.text = Text("Try to hit the blue ipod")
        self.add(self.text)
        self.text.left = 60.0
        self.text.top = 0.0
        self.text.font.color = Color(0x00FFCCFF)
        
        ipod.listen({"pointer_up": self.on_ipod_click})
        
        world.listen({"pre_solve": self.on_collide})
        
    def on_render(self, e):
        if self.target.left < 10:
            self.target_body.linear_velocity = Point(10.0, 0.0)
        
        if self.target.left > 400:
            self.target_body.linear_velocity = Point(-10.0,0.0)
    
    def on_ipod_click(self, e):
        self.ipod_body.linear_velocity = Point(0.0, 40.0)
    
    def on_collide(self, e):
        self.text.text = "Collision! with " + e.element_a.name

def init(runtime):
    runner.run_scene(PhysicsScene())
