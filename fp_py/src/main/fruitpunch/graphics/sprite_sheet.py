from fruitpunch.native.elements.playable import Playable
from fruitpunch.graphics.frame import Frame

class SpriteSheet(Playable):
    '''
    Allows a single Sprite to contain multiple frames of an animation. The
    position of the frames within the sprite can be specified by adding Frame
    instances. 
    
    A spritesheet is usually defined in an XML file, such as follows:

    <spritesheet>
     <frame x="0" y="0" width="100" height="100" />
     <frame x="0" y="0" width="100" height="100" />
     <frame x="0" y="0" width="100" height="100" />
     <frame x="0" y="0" width="100" height="100" />
    </spritesheet>

    This spritesheet can then be played when added to a sprite. The final 
    python code should resemble:

    sonic = Sprite("sonic.png")
    sonic_sheet = sonic.add(SpriteSheet("sonic.xml"))
    sonic_sheet.start()
    '''
    
    def __init__(self, file_name=None):
        super(SpriteSheet, self).__init__()
        
        self.frames = []
        self.lock_width = False
        self.lock_height = False
        self.auto_fit = True
        self.listen({"add":self.on_add})
        
        if file_name is not None:
            self.import_from(file_name)
        
    # _________________________________________________________________________
    
    def add(self, element):
        super(SpriteSheet, self).add(element)
        
        if isinstance(element, Frame):
            self.frames += [element]
    # _________________________________________________________________________
    
    def on_add(self, ev):
        if len(self.frames):
            self.render_single(0)
    
    # _________________________________________________________________________
    
    def remove(self, element):
        super(SpriteSheet, self).remove(element)
        
        if isinstance(element, Frame):
            self.frames.remove(element)
    
    # _________________________________________________________________________
    
    def resize(self, frame_number):
        '''
        Resizes the parent Sprite to the width and height specified by the
        frame at the index specified.
        '''
        
        self.parent.width = self.frames[frame_number].width
        self.parent.height = self.frames[frame_number].height
        
    # _________________________________________________________________________
        
    def render_single(self, frame_number):
        '''
        Positions a single frame of the sprite sheet into the sprite
        '''
        
        frame = self.frames[frame_number]
        self.parent.crop(frame.x, frame.y, frame.width, frame.height)
        
        if self.lock_width:
            ratio = float(frame.height) / float(frame.width)
            self.parent.height = float(self.parent.width) * ratio
        elif self.lock_height:
            ratio = float(frame.width) / float(frame.height)
            self.parent.width = float(self.parent.height) * ratio
        elif self.auto_fit:
            self.resize(frame_number)
            
    # _________________________________________________________________________
            
    def calculate_duration(self):
        return (len(self.frames) - 1)
    
    def start(self, frameset=None):
        if frameset is None:
            return Playable.start(self)
        
        self.find_by("name", frameset).start()
        
    def stop(self, frameset=None):
        if frameset is None:
            return Playable.stop(self)
        
        self.find_by("name", frameset).stop()
            
        
        
    
    