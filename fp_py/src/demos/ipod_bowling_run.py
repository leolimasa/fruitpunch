# Stuff to make it run inside eclipse "Run As"

from runner import runner
import os

if __name__ == "__main__":
    runner.run(os.path.abspath(__file__))
    exit()

# -----------------------------------------------------------------------------

from fruitpunch import Node, App
from ipod_bowling.bowling_scene import Bowling
from ipod_bowling import elements

class IpodBowling(App):
    def on_init(self, ev):
        Node.default_module_paths = elements
        self.go_to_scene(Bowling())
        
def init(runtime):
    app = IpodBowling()
    app.init()
    
    