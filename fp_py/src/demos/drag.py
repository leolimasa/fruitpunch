'''
Created on 2012-08-19

@author: leo
'''

import os
from runner import runner

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))   
    exit()


from fruitpunch import Scene, Sprite, App, event
from fruitpunch.behaviors.drag import Drag

class DragScene(Scene):
    def on_init(self, event):
        print("Init called!")
        s = Sprite("tuqui.png")
        print("Sprite initialized.")
        self.add(s)
        print("Sprite added.")
        s.top = 0
        s.left = 0
        d = s.add(Drag())

def init(runtime):
    runner.run_scene(DragScene())