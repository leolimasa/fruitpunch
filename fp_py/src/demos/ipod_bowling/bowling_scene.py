from fruitpunch import Scene, PhysicsWorld
from ipod_bowling.elements import Pin

class Bowling(Scene):
    def on_init(self, ev):
        
        world = PhysicsWorld()
        self.add(world)

        self.import_from("bowling.xml")
        
        self.pin = self.find_by_class(Pin)