'''
Created on Aug 15, 2012

@author: leo
'''
from fruitpunch import Scene, Text, Color
#from libfp_core import Align
from fruitpunch.behaviors.drag import Drag

class ResultsScene(Scene):
    def on_init(self, event):
        increment = 40
        self.pen_y = 0
        
        title = Text("Unit Testing Results")
        self.add(title)
        title.top = 0
        title.left = 0
        title.font.color = Color(0xFF0000FF)
        self.pen_y += increment
        
        if self.results.wasSuccessful():
            pass_txt = Text("All tests pass!")
            self.add(pass_txt)
            pass_txt.add(Drag())
            
            pass_txt.font.color = Color(0x00FF00FF)
            pass_txt.top = self.pen_y
            pass_txt.left = 0
            self.pen_y += increment
        else:
            for fail in self.results.failures:
                for res in fail:
                    self.add_fail(res)
            
    def add_fail(self, result):
        res = Text(str(result))
        res.top = self.pen_y
        res.font.size = 12
        
        res.left = 0
        res.font.color = Color(0xFF0000FF)
        self.add(res)
        
        self.pen_y += res.height
        
        
    