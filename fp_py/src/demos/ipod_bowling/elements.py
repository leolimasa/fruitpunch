from fruitpunch import Sprite, Body, BodyDrag, BodyType

class Ball(Sprite):
    def __init__(self):
        Sprite.__init__(self)
        
        self.listen({"add": self.on_add})
    
    def on_add(self, ev):
        self.add(Body())
        self.add(BodyDrag())
        
class Pin(Sprite):
    def __init__(self):
        Sprite.__init__(self)
        
        self.listen({"add": self.on_add})
    
    def on_add(self, ev):
        print("Added pin!")
        self.add(Body())
        
class Ground(Sprite):
    
    def __init__(self):
        Sprite.__init__(self)
        
        self.listen({"add": self.on_add})
    
    def on_add(self, ev):
        self.add(Body(BodyType.static))