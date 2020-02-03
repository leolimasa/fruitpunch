

import os
from runner import runner

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))   
    exit()


import random
from fruitpunch import Property, Animation, Tween, Scene, Sprite, Image,\
    App, Text
import os
import pydevd

    
class Left(Property):
    def set(self, value):
        self.obj.left = value
    def get(self):
        return self.obj.left
    
class SideToSide(Animation):
    def setup(self, pedobear):
        leftprop = Left()
        leftprop.obj = pedobear
        
        t1 = Tween()
        t1.start_frame = 0
        t1.start_value = pedobear.left
        t1.end_value = pedobear.left + 450
        t1.duration = 1600
        t1.prop = leftprop
        
        t2 = Tween()
        t2.start_frame = 1601
        t2.start_value = pedobear.left + 450
        t2.end_value = pedobear.left
        t2.duration = 1600
        t2.prop = leftprop
        
        self.add(t1)
        self.add(t2)
              
class KillPedoBear1(Scene):    
    def on_init(self, ev):
        self.counter = 0
        self.background = Sprite("bedroom.png")
        self.pedobear = Sprite("pedoBear.png") 
        self.add(self.background)
        self.background.scale(1.33, 1.50)
        self.background.left = 0
        self.background.top = 0
        self.add(self.pedobear)
        self.pedobear.scale(0.5, 0.5)
        self.pedobear.left = 0
        self.pedobear.top = 230
        self.pedobear.listen({"pointer_down":self.on_pedobear_click})
        self.background.listen({"pointer_down": self.on_background_click})

        self.start_animation()
    
    def on_pedobear_click(self, ev):
        print("pedo bear has exploded")
        self.pedobear.image = Image("boom-hi.png")
        
    
    def on_background_click(self, ev):
        print("background clicked")
    
    def start_animation(self):
        anim = SideToSide()
        anim.loop = True
        anim.setup(self.pedobear)
        self.add(anim)
        anim.start()
        
class KillPedoBear2(Scene):
    def on_init(self, ev):
        self.background = Sprite("background-winter.png")
        self.add(self.background)
        self.background.left = 0
        self.background.top = 0
        # actually we will probably want to do something really creepy
        # and have a real event that triggers this, 
        # but for now, lets just load the winter image...
        # to test the scene switcher...

    
class MyPedoBearApp(App):
    def on_init(self, ev):
        self.counter = 0
        self.scene = KillPedoBear1()
        self.go_to_scene(self.scene)
        
    def on_render(self, ev):
        self.counter = self.counter + 1
        if (self.counter == 100):
            # switch to winter scene...
            self.scene = KillPedoBear2()
            self.go_to_scene(self.scene)

def init(runtime):
    #pydevd.settrace()
    app = MyPedoBearApp()
    app.init()
