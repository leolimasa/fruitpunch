from fruitpunch import Scene, Sprite, SpriteSheet, Node, Frame, Animation
from runner import runner
from fruitpunch.graphics import frame, frame_set

class ExplosionScene(Scene):
    def on_init(self, ev):
       
        exp1 = self.make_explosion()
        exp2 = self.make_explosion()
        exp3 = self.make_explosion()
        
        exp2.left = 100
        exp2.sheet.start_frame = 10
        exp3.left = 300 
        exp3.sheet.start_frame = 20
        
        anim = Animation()
        anim.add(exp1.sheet)
        anim.add(exp2.sheet)
        anim.add(exp3.sheet)
        
        self.add(anim)
        anim.loop = True
        anim.start()
        
        
    
    def make_explosion(self):
        explosion = Sprite("explosion.png")
        sheet = SpriteSheet("explosion.xml")
        explosion.add(sheet)
        sheet.loop = True
        self.add(explosion)
        
        explosion.width = 60
        explosion.height = 60
        explosion.left = 20
        explosion.top = 20
        
        sheet.start()
        sheet.loop = True
        explosion.sheet = sheet
        
        return explosion
    
    
    def make_sonic(self):
        sonic = Sprite("sonic.png")
        sheet = SpriteSheet("sonic.xml")
        sonic.add(sheet)
        
        jump_set = sheet.find_by("name","idle")
        jump_set.loop = True
        jump_set.frame_duration = 15
        jump_set.start()
        sonic.left=150
        sonic.top=20
        self.add(sonic)

def init(runtime):
    Node.default_module_paths = [frame, frame_set]
    runner.run_scene(ExplosionScene())