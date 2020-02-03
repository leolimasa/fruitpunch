'''
Created on 2012-08-19

@author: leo
'''
import os
from runner import runner
import pydevd

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))   
    exit()


from fruitpunch import Scene, Sprite, event, PhysicsWorld, Body,\
    BodyType, Image, Interval
import random
from fruitpunch.behaviors.collector import Collector
#from guppy import hpy

class PhysicsScene(Scene):
    images = {
              "orange": Image("orange.png"),
              "green": Image("green.png"),
              "pink": Image("pink.png")
    }
    
    def on_init(self, e):
        world = PhysicsWorld()
        world.pixel_size = 50
        self.add(world)
        
        #self.hp = hpy()
        
        self.counter = 0
        
        ground = Sprite("ground.png")
        ground.top = 400
        ground.left = 0
        #self.add(ground)
        #ground.add(Body(BodyType.static))
        
        self.listen({"post_render": self.on_frame})
    
    def on_frame(self, event):
        if self.counter < 40:
            self.counter += 1
            return 
        
        self.counter = 0
        colors = ["orange","green", "pink"]
        
        # pick a color
        color = colors[random.randint(0,2)]
        ipod = Sprite(self.images[color])
        ipod.top = random.random() * 100
        ipod.left = random.random() * 500
        self.add(ipod)
        ipod_body = Body()
        ipod_body.shape_scale = 0.89
        ipod.add(ipod_body)
        ipod.add(Collector())
        

def init(runtime):
    #pydevd.settrace()
    runner.run_scene(PhysicsScene())