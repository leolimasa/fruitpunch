# This was designed to test the performance of the engine. It doesn't use
# fp_py because we want to test the core and the python interpreter by themselves.
# It will render a bunch of bears and rotate them, while removing and adding
# new bears every few frames to test for memory leaks


from libfp_core import ObserverWrap, Sprite, Image
import random

numsprites = 100
remove_and_add = 10
img = Image("pedoBear.png")

# executed every frame
class OnFrame(ObserverWrap):
    def action(self):
        for primitive in self.sprites:
            primitive.rotate(1)
        self.curframe += 1
        
        if self.curframe == 10:
            removed = 0
            self.curframe = 0
            for primitive in self.sprites:
                if removed > remove_and_add:
                    break
                
                self.runtime.get_window().remove_primitive(primitive)
                self.sprites.remove(primitive)
                self.sprites.append(newbear(self.runtime))
                removed += 1
                
def newbear(runtime):
    sprite = Sprite(img)
    runtime.get_window().add_primitive(sprite)   
    sprite.set_x(random.randint(0,500))
    sprite.set_y(random.randint(0,500))
    return sprite    
        
        
def init(runtime):
    renderevent = OnFrame()
    renderevent.runtime = runtime
    renderevent.sprites = []
    renderevent.curframe = 0
    
    
    for i in range(numsprites):
       renderevent.sprites.append(newbear(runtime))
     
    runtime.get_window().attach_observer("pre_render",renderevent)
    